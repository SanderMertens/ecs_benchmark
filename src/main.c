#include <ecs_benchmark.h>
#include <stdio.h>
#include <stdlib.h>

#define MEASURE_INTERVAL (25)
#define MEASURE_TIME (0.5)

#define PRETTY_TIME_FMT

typedef struct bench_t {
    const char *lbl;
    ecs_time_t t;
    double dt;
    int32_t interval;
    int32_t intervals;
    int32_t count;
} bench_t;

#define THOUSAND (1000.0)
#define MILLION (1000.0 * 1000.0)
#define BILLION (1000.0 * MILLION)

#define FRAC_THOUSAND (1.0 / THOUSAND)
#define FRAC_MILLION (1.0 / MILLION)
#define FRAC_BILLION (1.0 / BILLION)

#define NUM_LEN(v)\
    ((v > THOUSAND) ? 4 : ((v > 100) ? 3 : ((v > 10) ? 2 : 1)))

#define SYM(v)\
    (v < FRAC_MILLION) ? "ns" : ((v < FRAC_THOUSAND) ? "us" : "ms")

#define NUM(v)\
    ((v < FRAC_MILLION) ? (v * BILLION) : ((v < FRAC_THOUSAND) ? (v * MILLION) : (v * THOUSAND)))

#define COLOR(v)\
    ((v < FRAC_MILLION) ? ECS_GREEN : (v < FRAC_THOUSAND) ? ECS_YELLOW : ECS_RED)

bool flip_coin(void) {
    int r = rand();
    return r >= ((float)RAND_MAX / 2.0f);
}

const char* spacing(float v) {
    if (v > 1000000) {
        return "";
    } else if (v > 100000) {
        return " ";
    } else if (v > 10000) {
        return "  ";
    } else if (v > 1000) {
        return "   ";
    } else if (v > 100) {
        return "    ";
    } else if (v > 10) {
        return "     ";
    } else {
        return "      ";
    }
}

char* bench_vasprintf(
    const char *fmt,
    va_list args)
{
    ecs_size_t size = 0;
    char *result  = NULL;
    va_list tmpa;

    va_copy(tmpa, args);

    size = vsnprintf(result, 0, fmt, tmpa);

    va_end(tmpa);

    if ((int32_t)size < 0) { 
        return NULL; 
    }

    result = (char *) ecs_os_malloc(size + 1);

    if (!result) { 
        return NULL; 
    }

    ecs_os_vsprintf(result, fmt, args);

    return result;
}

char* bench_asprintf(
    const char *fmt,
    ...)
{
    va_list args;
    va_start(args, fmt);
    char *result = bench_vasprintf(fmt, args);
    va_end(args);
    return result;
}

#ifdef PRETTY_TIME_FMT
void header_print(void) {
    printf("| Benchmark                             | Measurement  |\n");
    printf("|---------------------------------------|--------------|\n");
}

void bench_print(const char *label, float v) {
    printf("| %s %*s | %s%.2f%s%s%s |\n", 
        label, (int)(36 - strlen(label)), "", COLOR(v), NUM(v), SYM(v), spacing(NUM(v)), ECS_NORMAL);
}
#else
void header_print(void) {
    printf("Benchmark                              Measurement\n");
}

void bench_print(const char *label, float v) {
    printf("%s %*s  %s%.2f%s%s\n", 
        label, (int)(36 - strlen(label)), "", COLOR(v), v * BILLION, spacing(v * BILLION), ECS_NORMAL);
}
#endif

bench_t bench_begin(const char *lbl, int32_t count) {
    bench_t b = {0};
    b.lbl = lbl;
    b.interval = MEASURE_INTERVAL;
    b.intervals = 0;
    b.count = count;
    ecs_time_measure(&b.t);
    return b;
}

bool bench_next(bench_t *b) {
    if (!--b->interval) {
        b->intervals ++;
        ecs_time_t t = b->t;
        double dt = ecs_time_measure(&t);
        if (dt > MEASURE_TIME) {
            b->dt = dt;
            return false;
        }
        b->interval = MEASURE_INTERVAL;
    }
    return true;
}

void bench_end(bench_t *b) {
    bench_print(b->lbl, b->dt / (b->intervals * MEASURE_INTERVAL * b->count));
}

/* -- benchmark code -- */

/* Number of entities created for most benchmarks */
#define ENTITY_COUNT (1000)

/* Number of entities used for query benchmark */
#define QUERY_ENTITY_COUNT (65536)

ecs_entity_t* create_ids(ecs_world_t *world, int32_t count, ecs_size_t size, bool low) {
    if (count) {
        ecs_entity_t *ids = ecs_os_calloc_n(ecs_entity_t, count);
        for (int i = 0; i < count; i ++) {
            if (low) {
                ids[i] = ecs_new_low_id(world);
            } else {
                ids[i] = ecs_new_id(world);
            }
            if (size) {
                ecs_set(world, ids[i], EcsComponent, {size, 4});
            }
        }
        return ids;
    } else {
        return NULL;
    }
}

void world_mini_fini(void) {
    ecs_os_set_api_defaults();
    bench_t b = bench_begin("world_mini_fini", 1);
    do {
        ecs_world_t *world = ecs_mini();
        ecs_fini(world);
    } while (bench_next(&b));
    bench_end(&b);
}

void world_init_fini(void) {
    ecs_os_set_api_defaults();
    bench_t b = bench_begin("world_init_fini", 1);
    do {
        ecs_world_t *world = ecs_init();
        ecs_fini(world);
    } while (bench_next(&b));
    bench_end(&b);
}

void System(ecs_iter_t *it) { }

void world_progress(char *label, int system_count) {
    ecs_world_t *world = ecs_init();

    for (int i = 0; i < system_count; i ++) {
        ecs_system(world, {
            .entity = ecs_entity(world, { .add = { ecs_dependson(EcsOnUpdate) }}),
            .callback = System
        });
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_progress(world, 0);
    } while (bench_next(&b));
    bench_end(&b);
    ecs_fini(world);
}

void create_delete_table(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count - 1, 0, true);

    ecs_table_t *table = NULL;
    for (int i = 0; i < id_count - 1; i ++) {
        table = ecs_table_add_id(world, table, ids[i]);
    }

    bench_t b = bench_begin(label, 2);
    do {
        ecs_entity_t id = ecs_new_low_id(world);
        ecs_table_add_id(world, table, id);
        ecs_delete(world, id);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void match_table_w_query(const char *label, int32_t match_count, int32_t total_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, 0, true);

    ecs_table_t *table = ecs_table_add_id(world, NULL, ids[0]);

    for (int i = 0; i < match_count; i ++) {
        ecs_query(world, {
            .filter.terms[0].id = ids[0] /* matches table */
        });
    }

    for (int i = 0; i < total_count - match_count; i ++) {
        ecs_query(world, {
            .filter.terms[0].id = ids[1] /* doesn't match table */
        });
    }

    bench_t b = bench_begin(label, 2);
    do {
        ecs_entity_t id = ecs_new_low_id(world);
        ecs_table_add_id(world, table, id);
        ecs_delete(world, id);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void rematch_tables(const char *label, int32_t rematch_count, int32_t total_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, 0, true);

    ecs_entity_t base_1 = ecs_new_w_id(world, ids[0]);
    ecs_entity_t base_2 = ecs_new_w_id(world, ids[0]);

    for (int i = 0; i < rematch_count; i ++) {
        ecs_table_t *table = ecs_table_add_id(world, NULL, ecs_pair(EcsIsA, base_1));
        ecs_table_add_id(world, table, ecs_new_low_id(world));
    }
    for (int i = 0; i < (total_count - rematch_count); i ++) {
        ecs_table_t *table = ecs_table_add_id(world, NULL, ecs_pair(EcsIsA, base_2));
        ecs_table_add_id(world, table, ecs_new_low_id(world));
    }

    ecs_query(world, {
        .filter.terms[0].id = ids[0] /* matches table */
    });

    bench_t b = bench_begin(label, 2);
    do {
        ecs_remove_id(world, base_1, ids[0]);
        ecs_run_aperiodic(world, 0);

        ecs_add_id(world, base_1, ids[0]);
        ecs_run_aperiodic(world, 0);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void fill_empty_table_w_query(const char *label, int32_t query_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, 0, true);

    for (int i = 0; i < query_count; i ++) {
        ecs_query(world, {
            .filter.terms[0].id = ids[0]
        });
    }

    bench_t b = bench_begin(label, 2);
    do {
        ecs_entity_t e = ecs_new_w_id(world, ids[0]);
        ecs_run_aperiodic(world, 0);
        ecs_delete(world, e);
        ecs_run_aperiodic(world, 0);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void table_add_remove(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    bench_t b = bench_begin(label, id_count * 2);
    do {
        ecs_table_t *table = NULL;
        for (int i = 0; i < id_count; i ++) {
            table = ecs_table_add_id(world, table, ids[i]);
        }

        for (int i = id_count - 1; i >= 0; i --) {
            table = ecs_table_remove_id(world, table, ids[i]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void has_empty_entity(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, 1, 0, true);
    
    bench_t b = bench_begin("has_empty_entity", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_has_id(world, entities[e], ids[0]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void has_id_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, 2, 0, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }

    bench_t b = bench_begin("has_id_not_found", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_has_id(world, entities[e], ids[1]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void has_id(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_has_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_empty_entity(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, 1, 4, true);
    
    bench_t b = bench_begin("get_empty_entity", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_id(world, entities[e], ids[0]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_id_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, 2, 4, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }
    
    bench_t b = bench_begin("get_id_not_found", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_id(world, entities[e], ids[1]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_id(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_get_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_mut_id(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_get_mut_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_mut_remove(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_get_mut_id(world, entities[e], ids[i]);
            }
            for (int i = 0; i < id_count; i ++) {
                ecs_remove_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void set_id(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    int32_t v = 0;

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_set_id(world, entities[e], ids[i], 4, &v);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_pair(const char *label, int32_t target_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *rel = create_ids(world, 1, 4, true);
    ecs_entity_t *tgt = create_ids(world, target_count, 0, false);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < target_count; i ++) {
            ecs_add_pair(world, entities[e], rel[0], tgt[i]);
        }
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * target_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < target_count; i ++) {
                ecs_get_id(world, entities[e], ecs_pair(rel[0], tgt[i]));
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(rel);
    ecs_os_free(tgt);
}

void get_inherited(const char *label, int32_t depth) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t id = ecs_set(world, 0, EcsComponent, {4, 4});

    ecs_entity_t base = ecs_new_w_id(world, id);
    for (int i = 0; i < depth; i ++) {
        base = ecs_new_w_pair(world, EcsIsA, base);
    }

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_pair(world, entities[e], EcsIsA, base);
    }

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_id(world, entities[e], id);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void ref_init(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, 1, 4, true);
    
    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }

    bench_t b = bench_begin("ref_init", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_ref_init_id(world, entities[e], ids[0]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void ref_get(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, 1, 4, true);
    ecs_ref_t *refs = ecs_os_calloc_n(ecs_ref_t, ENTITY_COUNT);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
        refs[e] = ecs_ref_init_id(world, entities[e], ids[0]);
    }
    
    bench_t b = bench_begin("ref_get", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_ref_get_id(world, &refs[e], ids[0]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
    ecs_os_free(refs);
}

void add_remove(const char* label, int32_t id_count, bool component) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true);

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, entities[e], ids[i]);
            }
            for (int i = 0; i < id_count; i ++) {
                ecs_remove_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void add_existing(const char* label, int32_t id_count, bool component) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void add_remove_tag_to_components(const char *label, int32_t component_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, component_count, 4, true);
    ecs_entity_t tag = ecs_new_id(world);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < component_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_add_id(world, entities[e], tag);
        }
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_remove_id(world, entities[e], tag);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
}

void add_remove_override(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    ecs_entity_t base = ecs_new_id(world);
    for (int i = 0; i < id_count; i ++) {
        ecs_add_id(world, base, ids[i]);
    }

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_pair(world, entities[e], EcsIsA, base);
    }

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, entities[e], ids[i]);
            }
            for (int i = 0; i < id_count; i ++) {
                ecs_remove_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void dummy_xtor(void *ptr, int32_t count, const ecs_type_info_t *ti) {
    (void)ptr;
    (void)count;
    (void)ti;
}

void add_remove_hooks(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    for (int i = 0; i < id_count; i ++) {
        ecs_set_hooks_id(world, ids[i], &(ecs_type_hooks_t){
            .ctor = dummy_xtor,
            .dtor = dummy_xtor,
        });
    }

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, entities[e], ids[i]);
            }
            for (int i = 0; i < id_count; i ++) {
                ecs_remove_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

static void AddId(ecs_iter_t *it) {
    ecs_entity_t add_id = *(ecs_entity_t*)it->ctx;
    for (int i = 0; i < it->count; i ++) {
        ecs_add_id(it->world, it->entities[i], add_id);
    }
}

void create_w_add_in_observer(const char *label, int32_t entity_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, entity_count, 0, false);

    ecs_entity_t id = ecs_new_id(world);
    ecs_entity_t add_id = ecs_new_id(world);

    ecs_observer(world, {
        .filter.terms = {{ id }},
        .events = { EcsOnAdd },
        .callback = AddId,
        .ctx = &add_id
    });

    bench_t b = bench_begin(label, entity_count);
    do {
        for (int i = 0; i < entity_count; i ++) {
            ecs_add_id(world, entities[i], id);
            ecs_remove_id(world, entities[i], id);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void add_remove_cmd(const char* label, int32_t id_count, bool component) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true);

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, entities[e], ids[i]);
            }
        }
        ecs_defer_end(world);
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_remove_id(world, entities[e], ids[i]);
            }
        }
        ecs_defer_end(world);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_mut_remove_cmd(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_get_mut_id(world, entities[e], ids[i]);
            }
        }
        ecs_defer_end(world);
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_remove_id(world, entities[e], ids[i]);
            }
        }
        ecs_defer_end(world);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_mut_cmd(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_get_mut_id(world, entities[e], ids[i]);
            }
        }
        ecs_defer_end(world);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void set_cmd(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true);

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    int v = 0;
    do {
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_set_id(world, entities[e], ids[i], 4, &v);
            }
        }
        ecs_defer_end(world);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void create_delete(const char *label, int32_t id_count, bool component) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true);

    bench_t b = bench_begin(label, ENTITY_COUNT * (2 + id_count));
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_entity_t e = ecs_new_id(world);
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, e, ids[i]);
            }
            ecs_delete(world, e);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(ids);
}

void entity_init_delete(const char *label) {
    ecs_world_t *world = ecs_mini();

    bench_t b = bench_begin(label, 2);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_entity_t e = ecs_entity_init(world, &(ecs_entity_desc_t){
                .use_low_id = false /* default */
            });

            ecs_delete(world, e);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void entity_init_w_name_delete(const char *label) {
    ecs_world_t *world = ecs_mini();

    bench_t b = bench_begin(label, 2);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_entity_t e = ecs_entity_init(world, &(ecs_entity_desc_t){
                .name = "foo"
            });

            ecs_delete(world, e);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void create_delete_tree(const char *label, int32_t width, int32_t depth) {
    ecs_world_t *world = ecs_mini();

    bench_t b = bench_begin(label, width); /* calculate overhead per child */
    do {
        ecs_entity_t root = ecs_new_id(world), cur = root;
        for (int i = 0; i < depth; i ++) {
            for (int w = 0; w < width - 1; w ++) {
                ecs_entity_t e = ecs_new_id(world);
                ecs_add_pair(world, e, EcsChildOf, cur);
            }
            ecs_entity_t e = ecs_new_id(world);
            ecs_add_pair(world, e, EcsChildOf, cur);
            cur = e;
        }

        ecs_delete(world, root);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void change_parent(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t p1 = ecs_new_id(world);
    ecs_entity_t p2 = ecs_new_id(world);

    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_pair(world, entities[e], EcsChildOf, p2);
    }

    bench_t b = bench_begin("change_parent", 2 * ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_add_pair(world, entities[e], EcsChildOf, p1);
        }
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_add_pair(world, entities[e], EcsChildOf, p2);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void change_parent_root(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t p = ecs_new_id(world);
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);

    bench_t b = bench_begin("change_parent_root", 2 * ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_add_pair(world, entities[e], EcsChildOf, p);
        }
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_remove_pair(world, entities[e], EcsChildOf, p);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void change_parent_w_name(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t p1 = ecs_new_entity(world, "parent_1");
    ecs_entity_t p2 = ecs_new_entity(world, "parent_2");
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        char name[256];
        sprintf(name, "child_%d", e);
        ecs_set_name(world, entities[e], name);
        ecs_add_pair(world, entities[e], EcsChildOf, p2);
    }

    bench_t b = bench_begin("change_parent_w_name", 2);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_add_pair(world, entities[e], EcsChildOf, p1);
        }
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_add_pair(world, entities[e], EcsChildOf, p2);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void lookup(const char *label, int32_t depth) {
    ecs_world_t *world = ecs_mini();

    char *lookup_str = ecs_os_strdup("foo");
    for (int i = 0; i < depth; i ++) {
        char *tmp = bench_asprintf("%s.foo", lookup_str);
        ecs_os_free(lookup_str);
        lookup_str = tmp;
    }

    ecs_entity_t e = ecs_new_entity(world, "foo");
    for (int i = 0; i < depth; i ++) {
        ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, e);
        ecs_set_name(world, child, "foo");
        e = child;
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_lookup_fullpath(world, lookup_str);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_os_free(lookup_str);

    ecs_fini(world);
}

void set_name(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t e = ecs_new_id(world);

    bench_t b = bench_begin("set_name", 2);
    do {
        ecs_set_name(world, e, "foo");
        ecs_set_name(world, e, NULL);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

static void Dummy(ecs_iter_t *it) { }

void emit(const char *label, int32_t observer_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, 0, true);
    ecs_entity_t e = ecs_new_w_id(world, ids[0]);
    ecs_table_t *table = ecs_get_table(world, e);
    ecs_entity_t evt = ecs_new_id(world);

    for (int i = 0; i < observer_count; i ++) {
        ecs_observer(world, {
            .filter.terms = {{ ids[0], .src.flags = EcsSelf }},
            .callback = Dummy,
            .events = { evt }
        });
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_emit(world, &(ecs_event_desc_t) {
            .event = evt,
            .ids = &(ecs_type_t){ .array = ids, .count = 1 },
            .table = table,
            .observable = world
        });
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void modified(const char *label, int32_t observer_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, 4, true);
    ecs_entity_t e = ecs_new_w_id(world, ids[0]);

    for (int i = 0; i < observer_count; i ++) {
        ecs_observer(world, {
            .filter.terms = {{ ids[0], .src.flags = EcsSelf }},
            .callback = Dummy,
            .events = { EcsOnSet }
        });
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_modified_id(world, e, ids[0]);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void emit_propagate(const char *label, int32_t depth) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, 0, true);
    ecs_entity_t root = ecs_new_w_id(world, ids[0]), cur = root;
    ecs_table_t *root_table = ecs_get_table(world, root);
    ecs_entity_t evt = ecs_new_id(world);

    ecs_observer(world, {
        .filter.terms = {{ ids[0], .src.flags = EcsUp, .src.trav = EcsChildOf }},
        .callback = Dummy,
        .events = { evt }
    });

    for (int i = 0; i < depth; i ++) {
        cur = ecs_new_w_pair(world, EcsChildOf, cur);
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_emit(world, &(ecs_event_desc_t) {
            .event = evt,
            .ids = &(ecs_type_t){ .array = ids, .count = 1 },
            .table = root_table,
            .observable = world
        });
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void emit_forward(const char *label, int32_t id_count, int32_t depth) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);
    ecs_entity_t root = ecs_new_id(world), cur = root;

    for (int i = 0; i < id_count; i ++) {
        ecs_observer(world, {
            .filter.terms = {{ ids[i], .src.flags = EcsUp, .src.trav = EcsChildOf }},
            .callback = Dummy,
            .events = { EcsOnAdd, EcsOnRemove }
        });
    }

    for (int i = 0; i < id_count; i ++) {
        ecs_add_id(world, root, ids[i]);
    }
    for (int i = 0; i < depth; i ++) {
        cur = ecs_new_w_pair(world, EcsChildOf, cur);
    }

    ecs_entity_t e = ecs_new_id(world);
    bench_t b = bench_begin(label, 1);
    do {
        ecs_add_pair(world, e, EcsChildOf, cur);
        ecs_remove_pair(world, e, EcsChildOf, cur);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void filter_init_fini(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_filter_desc_t desc = {0};
        for (int i = 0; i < id_count; i ++) {
            desc.terms[i].id = ids[i];
            desc.terms[i].src.flags = EcsSelf;
        }

        ecs_filter_t *f = ecs_filter_init(world, &desc);
        ecs_filter_fini(f);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(ids);
}

void filter_init_fini_inline(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_filter_desc_t desc = {0};
        ecs_filter_t f = ECS_FILTER_INIT;
        desc.storage = &f;
        for (int i = 0; i < id_count; i ++) {
            desc.terms[i].id = ids[i];
            desc.terms[i].src.flags = EcsSelf;
        }

        ecs_filter_init(world, &desc);
        ecs_filter_fini(&f);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(ids);
}

void filter_simple_iter(const char *label, int32_t query_count, bool component, ecs_flags32_t flags) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, query_count, component ? 4 : 0, true);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new_id(world);
        for (int c = 0; c < query_count; c ++) {
            ecs_add_id(world, e, ids[c]);
        }
    }

    ecs_filter_desc_t desc = {0};
    for (int i = 0; i < query_count; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].src.flags = flags;
    }
    ecs_filter_t *q = ecs_filter_init(world, &desc);
    ecs_entity_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, q);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_filter_fini(q);
    ecs_fini(world);
    ecs_os_free(ids);
}

void filter_iter(const char *label, int32_t id_count, bool component, int32_t query_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new_id(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    ecs_filter_desc_t desc = {0};
    for (int i = 0; i < query_count; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].src.flags = EcsSelf;
    }
    ecs_filter_t *f = ecs_filter_init(world, &desc);
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, f);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_filter_fini(f);
    ecs_fini(world);
    ecs_os_free(ids);
}

void filter_iter_up(const char *label, bool component, bool query_self) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, component ? 4 : 0, true);

    ecs_entity_t parent_with = ecs_new_id(world);
    ecs_add_id(world, parent_with, ids[0]);
    ecs_entity_t parent_without = ecs_new_id(world);
    ecs_add_id(world, parent_without, ids[1]);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t parent;
        if (i < (QUERY_ENTITY_COUNT / 2)) {
            parent = ecs_new_w_pair(world, EcsChildOf, parent_with);
        } else {
            parent = ecs_new_w_pair(world, EcsChildOf, parent_without);
        }

        ecs_new_w_pair(world, EcsChildOf, parent);
    }

    ecs_filter_desc_t desc = {0};
    desc.terms[0].id = ids[0];
    desc.terms[0].src.flags = EcsUp;
    desc.terms[0].src.trav = EcsChildOf;
    if (query_self) {
        desc.terms[1].id = ids[0];
        desc.terms[1].src.flags = EcsSelf;
    }
    ecs_filter_t *f = ecs_filter_init(world, &desc);
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, f);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_filter_fini(f);
    ecs_fini(world);
    ecs_os_free(ids);
}

void filter_iter_up_w_mut(const char *label, bool component, bool query_self) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, component ? 4 : 0, true);

    ecs_entity_t parent_with = ecs_new_id(world);
    ecs_add_id(world, parent_with, ids[0]);
    ecs_entity_t parent_without = ecs_new_id(world);
    ecs_add_id(world, parent_without, ids[1]);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t parent;
        if (i < (QUERY_ENTITY_COUNT / 2)) {
            parent = ecs_new_w_pair(world, EcsChildOf, parent_with);
        } else {
            parent = ecs_new_w_pair(world, EcsChildOf, parent_without);
        }

        ecs_new_w_pair(world, EcsChildOf, parent);
    }

    ecs_filter_desc_t desc = {0};
    desc.terms[0].id = ids[0];
    desc.terms[0].src.flags = EcsUp;
    desc.terms[0].src.trav = EcsChildOf;
    if (query_self) {
        desc.terms[1].id = ids[0];
        desc.terms[1].src.flags = EcsSelf;
    }
    ecs_filter_t *f = ecs_filter_init(world, &desc);
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, f);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }

        ecs_remove_id(world, parent_with, ids[0]);
        ecs_add_id(world, parent_with, ids[0]);
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_filter_fini(f);
    ecs_fini(world);
    ecs_os_free(ids);
}

void rule_init_fini(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_filter_desc_t desc = {0};
        for (int i = 0; i < id_count; i ++) {
            desc.terms[i].id = ids[i];
            desc.terms[i].src.flags = EcsSelf;
        }

        ecs_rule_t *f = ecs_rule_init(world, &desc);
        ecs_rule_fini(f);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(ids);
}

void rule_simple_iter(const char *label, int32_t query_count, bool component, ecs_flags32_t flags) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, query_count, component ? 4 : 0, true);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new_id(world);
        for (int c = 0; c < query_count; c ++) {
            ecs_add_id(world, e, ids[c]);
        }
    }

    ecs_filter_desc_t desc = {0};
    for (int i = 0; i < query_count; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].src.flags = flags;
    }
    ecs_rule_t *q = ecs_rule_init(world, &desc);
    ecs_entity_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_rule_iter(world, q);
        while (ecs_rule_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_rule_fini(q);
    ecs_fini(world);
    ecs_os_free(ids);
}

void rule_iter(const char *label, int32_t id_count, bool component, int32_t query_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new_id(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    ecs_filter_desc_t desc = {0};
    for (int i = 0; i < query_count; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].src.flags = EcsSelf;
    }
    ecs_rule_t *f = ecs_rule_init(world, &desc);
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_rule_iter(world, f);
        while (ecs_rule_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_rule_fini(f);
    ecs_fini(world);
    ecs_os_free(ids);
}

void rule_inheritance(const char *label, int32_t depth, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    ecs_entity_t id = ecs_new_id(world);
    ecs_entity_t cur = id;
    for (int i = 0; i < depth; i ++) {
        cur = ecs_new_w_pair(world, EcsIsA, cur);
    }

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new_id(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
        ecs_add_id(world, e, cur); /* derived id */
    }

    ecs_rule_t *f = ecs_rule(world, {
        .terms = {{ id, .src.flags = EcsSelf }}
    });
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_rule_iter(world, f);
        while (ecs_rule_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_rule_fini(f);
    ecs_fini(world);
}

void query_init_fini(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_query_desc_t desc = {0};
        for (int i = 0; i < id_count; i ++) {
            desc.filter.terms[i].id = ids[i];
            desc.filter.terms[i].src.flags = EcsSelf;
        }

        ecs_query_t *q = ecs_query_init(world, &desc);
        ecs_query_fini(q);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(ids);
}

void query_iter(const char *label, int32_t table_count, int32_t term_count, bool component) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *term_ids = create_ids(world, term_count, component ? 4 : 0, true);
    ecs_entity_t *table_ids = create_ids(world, table_count, 0, true);

    for (int i = 0; i < table_count; i ++) {
        for (int j = 0; j < QUERY_ENTITY_COUNT / table_count; j ++) {
            ecs_entity_t e = ecs_new_id(world);

            /* Make sure entities have all queried for components */
            for (int c = 0; c < term_count; c ++) {
                ecs_add_id(world, e, term_ids[c]);
            }

            /* Make sure entities are spread over different tables */
            ecs_add_id(world, e, table_ids[i]);
        }
    }

    ecs_query_desc_t desc = {0};
    for (int i = 0; i < term_count; i ++) {
        desc.filter.terms[i].id = term_ids[i];
        desc.filter.terms[i].src.flags = EcsSelf;
    }
    ecs_query_t *q = ecs_query_init(world, &desc);
    ecs_entity_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_query_fini(q);
    ecs_fini(world);
    ecs_os_free(term_ids);
    ecs_os_free(table_ids);
}

void query_iter_empty(const char *label, int32_t table_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *table_ids = create_ids(world, table_count + 1, 0, true);

    for (int i = 0; i < table_count; i ++) {
        for (int j = 0; j < QUERY_ENTITY_COUNT / table_count; j ++) {
            ecs_entity_t e = ecs_new_id(world);

            /* Make sure entities have all queried for components */
            ecs_add_id(world, e, table_ids[i]);

            /* Make sure entities are spread over different tables */
            ecs_add_id(world, e, table_ids[i]);

            if (i != 0) {
                ecs_delete(world, e);
            }
        }
    }

    ecs_query_t *q = ecs_query(world, {
        .filter.terms = {{ table_ids[table_count], .src.flags = EcsSelf }}
    });
    ecs_entity_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_query_fini(q);
    ecs_fini(world);
    ecs_os_free(table_ids);
}

void query_iter_rnd(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count + 1, 0, true);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new_id(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }

        ecs_add_id(world, e, ids[id_count]);
    }

    ecs_query_t *q = ecs_query(world, {
        .filter.terms = {{ ids[id_count], .src.flags = EcsSelf }}
    });
    ecs_entity_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_query_fini(q);
    ecs_fini(world);
    ecs_os_free(ids);
}

void query_count(const char *label, int32_t table_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, table_count + 1, 0, true);

    for (int i = 0; i < table_count; i ++) {
        for (int j = 0; j < QUERY_ENTITY_COUNT / table_count; j ++) {
            ecs_entity_t e = ecs_new_id(world);

            /* Make sure entities have queried for component */
            ecs_add_id(world, e, ids[table_count]);

            /* Make sure entities are spread over different tables */
            ecs_add_id(world, e, ids[i]);
        }
    }

    ecs_query_t *q = ecs_query(world, {
        .filter.terms = {{ ids[table_count], .src.flags = EcsSelf }}
    });
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        result += ecs_query_entity_count(q);
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_query_fini(q);
    ecs_fini(world);
    ecs_os_free(ids);
}

int main(int argc, char *argv[]) {
    header_print();

    // World init fini
    world_mini_fini();
    world_init_fini();

    // Has
    has_empty_entity();
    has_id_not_found();
    has_id("has_id", 1);
    has_id("has_16_ids", 16);

    // Get
    get_empty_entity();
    get_id_not_found();
    get_id("get_id", 1);
    get_id("get_16_ids", 16);
    get_pair("get_pair", 1);
    get_pair("get_pair_16_targets", 16);

    // Get inherited
    get_inherited("get_inherited_depth_1", 1);
    get_inherited("get_inherited_depth_2", 2);
    get_inherited("get_inherited_depth_16", 16);
    get_inherited("get_inherited_depth_32", 32);

    // Get mut
    get_mut_id("get_mut_id", 1);
    get_mut_id("get_mut_16_ids", 16);

    // Set mut
    set_id("set_id", 1);
    set_id("set_16_ids", 16);

    // Get mut remove
    get_mut_remove("get_mut_remove_id", 1);
    get_mut_remove("get_mut_remove_16_ids", 16);
    get_mut_remove("get_mut_remove_32_ids", 32);

    // Ref
    ref_init();
    ref_get();

    // Add remove
    add_remove("add_remove_1_tag", 1, false);
    add_remove("add_remove_2_tags", 2, false);
    add_remove("add_remove_16_tags", 16, false);
    add_remove("add_remove_32_tags", 32, false);
    add_remove("add_remove_1_component", 1, true);
    add_remove("add_remove_2_components", 2, true);
    add_remove("add_remove_16_components", 16, true);
    add_remove("add_remove_32_components", 32, true);

    // Add existing
    add_existing("add_existing_1_tag", 1, false);
    add_existing("add_existing_16_tags", 16, false);
    add_existing("add_existing_1_component", 1, true);
    add_existing("add_existing_16_components", 16, true);

    // Add remove tag to components
    add_remove_tag_to_components("add_remove_tag_to_1_component", 1);
    add_remove_tag_to_components("add_remove_tag_to_4_components", 4);
    add_remove_tag_to_components("add_remove_tag_to_8_components", 8);
    add_remove_tag_to_components("add_remove_tag_to_16_components", 16);
    add_remove_tag_to_components("add_remove_tag_to_64_components", 64);

    // Add override
    add_remove_override("add_remove_override_1", 1);
    add_remove_override("add_remove_override_2", 2);
    add_remove_override("add_remove_override_4", 4);
    add_remove_override("add_remove_override_16", 16);

    // Add cmd
    add_remove_cmd("add_remove_cmd_1_tag", 1, false);
    add_remove_cmd("add_remove_cmd_2_tags", 2, false);
    add_remove_cmd("add_remove_cmd_16_tags", 16, false);
    add_remove_cmd("add_remove_cmd_32_tags", 32, false);
    add_remove_cmd("add_remove_cmd_1_components", 1, true);
    add_remove_cmd("add_remove_cmd_2_components", 2, true);
    add_remove_cmd("add_remove_cmd_16_components", 16, true);
    add_remove_cmd("add_remove_cmd_32_components", 32, true);

    // Get mut cmd
    get_mut_cmd("get_mut_cmd_1", 1);
    get_mut_cmd("get_mut_cmd_2", 2);
    get_mut_cmd("get_mut_cmd_16", 16);
    get_mut_cmd("get_mut_cmd_32", 32);

    // Set cmd
    set_cmd("set_cmd_1", 1);
    set_cmd("set_cmd_2", 2);
    set_cmd("set_cmd_16", 16);
    set_cmd("set_cmd_32", 32);

    // Get mut remove cmd
    get_mut_remove_cmd("get_mut_remove_cmd_1", 1);
    get_mut_remove_cmd("get_mut_remove_cmd_2", 2);
    get_mut_remove_cmd("get_mut_remove_cmd_16", 16);
    get_mut_remove_cmd("get_mut_remove_cmd_32", 32);

    // Add remove hooks
    add_remove_hooks("add_remove_hooks_1", 1);
    add_remove_hooks("add_remove_hooks_2", 2);
    add_remove_hooks("add_remove_hooks_16", 16);
    add_remove_hooks("add_remove_hooks_32", 32);

    // Create with add in observer
    create_w_add_in_observer("create_100_w_add_in_observer", 100);
    create_w_add_in_observer("create_1k_w_add_in_observer", 1000);
    create_w_add_in_observer("create_10k_w_add_in_observer", 10 * 1000);
    create_w_add_in_observer("create_50k_w_add_in_observer", 50 * 1000);

    // Create delete
    create_delete("create_delete_empty", 0, false);
    create_delete("create_delete_1_tag", 1, false);
    create_delete("create_delete_2_tags", 2, false);
    create_delete("create_delete_16_tags", 16, false);
    create_delete("create_delete_1_component", 1, true);
    create_delete("create_delete_2_components", 2, true);
    create_delete("create_delete_16_components", 16, true);

    // Entity init delete
    entity_init_delete("entity_init_delete");
    entity_init_delete("entity_init_w_name_delete");

    // Create delete tree
    create_delete_tree("create_delete_tree_w1_d1", 1, 1);
    create_delete_tree("create_delete_tree_w1_d10", 1, 10);
    create_delete_tree("create_delete_tree_w1_d100", 1, 100);
    create_delete_tree("create_delete_tree_w1_d1000", 1, 1000);

    create_delete_tree("create_delete_tree_w10_d1", 10, 1);
    create_delete_tree("create_delete_tree_w10_d10", 10, 10);
    create_delete_tree("create_delete_tree_w10_d100", 10, 100);
    create_delete_tree("create_delete_tree_w10_d1000", 10, 1000);

    create_delete_tree("create_delete_tree_w100_d1", 100, 1);
    create_delete_tree("create_delete_tree_w100_d10", 100, 10);
    create_delete_tree("create_delete_tree_w100_d100", 100, 100);
    create_delete_tree("create_delete_tree_w100_d1000", 100, 1000);

    create_delete_tree("create_delete_tree_w1000_d1", 1000, 1);
    create_delete_tree("create_delete_tree_w1000_d10", 1000, 10);
    create_delete_tree("create_delete_tree_w1000_d100", 1000, 100);
    create_delete_tree("create_delete_tree_w1000_d1000", 1000, 1000);

    // Change parent
    change_parent();
    change_parent_root();
    change_parent_w_name();

    // Lookup
    lookup("lookup_depth_0", 0);
    lookup("lookup_depth_1", 1);
    lookup("lookup_depth_10", 10);
    lookup("lookup_depth_100", 100);

    // Set name
    set_name();

    // Emit
    emit("emit_0_observers", 0);
    emit("emit_1_observer", 1);
    emit("emit_10_observers", 10);
    emit("emit_100_observers", 100);

    // Emit propagate
    emit_propagate("emit_propagate_depth_1", 0);
    emit_propagate("emit_propagate_depth_10", 10);
    emit_propagate("emit_propagate_depth_100", 100);
    emit_propagate("emit_propagate_depth_1000", 1000);

    // Emit forward
    emit_forward("emit_forward_1_ids_depth_1", 1, 1);
    emit_forward("emit_forward_1_ids_depth_1000", 1, 1000);
    emit_forward("emit_forward_16_ids_depth_1", 16, 1);
    emit_forward("emit_forward_16_ids_depth_1000", 16, 1000);

    // Modified
    modified("modified_0_observers", 0);
    modified("modified_1_observer", 1);
    modified("modified_10_observers", 10);
    modified("modified_100_observers", 100);

    // Filter simple iter self
    filter_simple_iter("filter_simple_iter_self_1_tags", 1, false, EcsSelf);
    filter_simple_iter("filter_simple_iter_self_8_tags", 8, false, EcsSelf);
    filter_simple_iter("filter_simple_iter_self_1_component", 1, true, EcsSelf);
    filter_simple_iter("filter_simple_iter_self_8_components", 8, true, EcsSelf);

    // Filter simple iter
    filter_simple_iter("filter_simple_iter_1_tags", 1, false, 0);
    filter_simple_iter("filter_simple_iter_8_tags", 8, false, 0);
    filter_simple_iter("filter_simple_iter_1_component", 1, true, 0);
    filter_simple_iter("filter_simple_iter_8_components", 8, true, 0);

    // Filter init fini
    filter_init_fini("filter_init_fini_1_ids", 1);
    filter_init_fini("filter_init_fini_8_ids", 8);
    filter_init_fini("filter_init_fini_16_ids", 16);
    filter_init_fini_inline("filter_init_fini_inline_1_ids", 1);
    filter_init_fini_inline("filter_init_fini_inline_8_ids", 8);
    filter_init_fini_inline("filter_init_fini_inline_16_ids", 16);

    // Filter iter
    filter_iter("filter_iter_8_tags_1_term", 8, false, 1);
    filter_iter("filter_iter_8_tags_4_terms", 8, false, 4);
    filter_iter("filter_iter_16_tags_1_term", 16, false, 1);
    filter_iter("filter_iter_16_tags_4_terms", 16, false, 4);
    filter_iter("filter_iter_8_components_1_term", 8, true, 1);
    filter_iter("filter_iter_8_components_4_terms", 8, true, 4);
    filter_iter("filter_iter_16_components_1_term", 16, true, 1);
    filter_iter("filter_iter_16_components_4_terms", 16, true, 4);

    // Filter iter up
    filter_iter_up("filter_iter_up_8_tags", false, false);
    filter_iter_up("filter_iter_up_8_tags_w_self", false, true);

    // Filter iter up w mut
    filter_iter_up_w_mut("filter_iter_up_w_mut_8_tags", false, false);
    filter_iter_up_w_mut("filter_iter_up_w_mut_8_tags_w_self", false, true);

    // Rule init fini
    rule_init_fini("rule_init_fini_1_ids", 1);
    rule_init_fini("rule_init_fini_8_ids", 8);
    rule_init_fini("rule_init_fini_16_ids", 16);

    // Rule simple iter w/Self flags
    rule_simple_iter("rule_simple_iter_self_1_tags", 1, false, EcsSelf);
    rule_simple_iter("rule_simple_iter_self_8_tags", 8, false, EcsSelf);
    rule_simple_iter("rule_simple_iter_self_1_component", 1, true, EcsSelf);
    rule_simple_iter("rule_simple_iter_self_8_component", 8, true, EcsSelf);

    // Rule simple iter
    rule_simple_iter("rule_simple_iter_1_tags", 1, false, 0);
    rule_simple_iter("rule_simple_iter_8_tags", 8, false, 0);
    rule_simple_iter("rule_simple_iter_1_component", 1, true, 0);
    rule_simple_iter("rule_simple_iter_8_component", 8, true, 0);

    // Rule iter
    rule_iter("rule_iter_8_tags_1_term", 8, false, 1);
    rule_iter("rule_iter_8_tags_4_terms", 8, false, 4);
    rule_iter("rule_iter_16_tags_1_term", 16, false, 1);
    rule_iter("rule_iter_16_tags_4_terms", 16, false, 4);
    rule_iter("rule_iter_8_components_1_term", 8, true, 1);
    rule_iter("rule_iter_8_components_4_terms", 8, true, 4);
    rule_iter("rule_iter_16_components_1_term", 16, true, 1);
    rule_iter("rule_iter_16_components_4_terms", 16, true, 4);

    // Rule inheritance
    rule_inheritance("rule_inherit_depth_1_tables_1", 1, 0);
    rule_inheritance("rule_inherit_depth_1_tables_1024", 1, 10);
    rule_inheritance("rule_inherit_depth_2_tables_1", 2, 0);
    rule_inheritance("rule_inherit_depth_2_tables_1024", 2, 10);
    rule_inheritance("rule_inherit_depth_8_tables_1", 8, 0);
    rule_inheritance("rule_inherit_depth_8_tables_1024", 8, 10);
    rule_inheritance("rule_inherit_depth_16_tables_1", 16, 0);
    rule_inheritance("rule_inherit_depth_16_tables_1024", 16, 10);

    // Query init fini
    query_init_fini("query_init_fini_1_ids", 1);
    query_init_fini("query_init_fini_8_ids", 8);
    query_init_fini("query_init_fini_16_ids", 16);

    // Query iter
    query_iter("query_iter_1_table_1_tag", 1, 1, false);
    query_iter("query_iter_2_tables_1_tag", 2, 1, false);
    query_iter("query_iter_4_tables_1_tag", 4, 1, false);
    query_iter("query_iter_8_tables_1_tag", 8, 1, false);
    query_iter("query_iter_16_tables_1_tag", 16, 1, false);
    query_iter("query_iter_32_tables_1_tag", 32, 1, false);
    query_iter("query_iter_64_tables_1_tag", 64, 1, false);
    query_iter("query_iter_128_tables_1_tag", 128, 1, false);
    query_iter("query_iter_256_tables_1_tag", 256, 1, false);
    query_iter("query_iter_512_tables_1_tag", 512, 1, false);
    query_iter("query_iter_1024_tables_1_tag", 1024, 1, false);
    query_iter("query_iter_4096_tables_1_tag", 4096, 1, false);
    query_iter("query_iter_4096_tables_4_tags", 4096, 8, false);
    query_iter("query_iter_4096_tables_4_comps", 4096, 8, true);
    query_iter("query_iter_4096_tables_8_tags", 4096, 8, false);
    query_iter("query_iter_4096_tables_8_comps", 4096, 8, true);
    query_iter("query_iter_65536_tables_4_tags", 65536, 8, false);
    query_iter("query_iter_65536_tables_4_comps", 65536, 8, true);
    query_iter("query_iter_65536_tables_8_tags", 65536, 8, false);
    query_iter("query_iter_65536_tables_8_comps", 65536, 8, true);

    // Query empty iter
    query_iter_empty("query_iter_255_empty_1_fill", 256);
    query_iter_empty("query_iter_1023_empty_1_fill", 1024);

    // Query iter w/random component distribution
    query_iter_rnd("query_iter_rnd_8_tags", 8);
    query_iter_rnd("query_iter_rnd_16_tags", 16);

    // Query count
    query_count("query_count_1_table", 1);
    query_count("query_count_2_tables", 2);
    query_count("query_count_4_tables", 4);
    query_count("query_count_8_tables", 8);
    query_count("query_count_16_tables", 16);
    query_count("query_count_32_tables", 32);
    query_count("query_count_64_tables", 64);
    query_count("query_count_128_tables", 128);
    query_count("query_count_256_tables", 256);
    query_count("query_count_512_tables", 512);
    query_count("query_count_1024_tables", 1024);
    query_count("query_count_4096_tables", 4096);
    query_count("query_count_65536_tables", 65536);

    // Progress
    world_progress("progress_0_systems", 0);
    world_progress("progress_1_system", 1);
    world_progress("progress_10_systems", 10);
    world_progress("progress_100_systems", 100);

    // Create delete table
    create_delete_table("create_delete_table_1_id", 1);
    create_delete_table("create_delete_table_10_ids", 10);
    create_delete_table("create_delete_table_100_ids", 100);
    create_delete_table("create_delete_table_1000_ids", 1000);

    // Match table w query
    match_table_w_query("match_table_1_of_10_queries", 1, 10);
    match_table_w_query("match_table_5_of_10_queries", 5, 10);
    match_table_w_query("match_table_10_of_10_queries", 10, 10);

    match_table_w_query("match_table_1_of_100_queries", 1, 100);
    match_table_w_query("match_table_10_of_100_queries", 10, 100);
    match_table_w_query("match_table_50_of_100_queries", 50, 100);
    match_table_w_query("match_table_100_of_100_queries", 100, 100);

    match_table_w_query("match_table_1_of_1000_queries", 1, 1000);
    match_table_w_query("match_table_10_of_1000_queries", 10, 1000);
    match_table_w_query("match_table_100_of_1000_queries", 100, 1000);
    match_table_w_query("match_table_1000_of_1000_queries", 1000, 1000);

    // Rematch tables
    rematch_tables("rematch_1_of_1000_tables", 1, 1000);
    rematch_tables("rematch_10_of_1000_tables", 10, 1000);
    rematch_tables("rematch_100_of_1000_tables", 100, 1000);
    rematch_tables("rematch_1000_of_1000_tables", 1000, 1000);

    // Fill empty table w query
    fill_empty_table_w_query("fill_empty_table_0_queries", 0);
    fill_empty_table_w_query("fill_empty_table_1_query", 1);
    fill_empty_table_w_query("fill_empty_table_10_queries", 10);
    fill_empty_table_w_query("fill_empty_table_100_queries", 100);
    fill_empty_table_w_query("fill_empty_table_1000_queries", 1000);

    // Table add remove
    table_add_remove("table_add_remove_1_id", 1);
    table_add_remove("table_add_remove_4_ids", 4);
    table_add_remove("table_add_remove_16_ids", 16);
    table_add_remove("table_add_remove_32_ids", 32);
    table_add_remove("table_add_remove_64_ids", 64);

    return 0;
}
