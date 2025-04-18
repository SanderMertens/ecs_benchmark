#include <ecs_benchmark.h>
#include <stdio.h>
#include <stdlib.h>

#define FLECS_VERSION_NUMBER (FLECS_VERSION_MAJOR * 10000 + FLECS_VERSION_MINOR * 100 + FLECS_VERSION_PATCH)

// v3 compatibility
#if FLECS_VERSION_NUMBER < 40000
    #define ecs_os_vsnprintf(ptr, len, fmt, args) vsnprintf(ptr, ECS_CAST(size_t, len), fmt, args)

    #undef ecs_new
    #define ecs_new(world) ecs_new_id(world)

    typedef enum ecs_query_cache_kind_t {
        EcsQueryCacheDefault,
        EcsQueryCacheAuto,
    } ecs_query_cache_kind_t;

    #define query_terms filter.terms
    #define observer_terms filter.terms
    #define term_trav src.trav
    #define term_trav_flags src.flags
    #define make_inheritable(world, component)
    #define query_get_count(query) ecs_query_entity_count(query)

    #define ecs_field_w_size(it, size, field) ecs_field_w_size(it, size, field + 1)

    #if FLECS_VERSION_NUMBER < 30212
        #define ecs_ensure_id ecs_get_mut_id
    #endif

    #if FLECS_VERSION_NUMBER < 30205
        ecs_entity_t ecs_new_w_table(ecs_world_t *world, ecs_table_t *table) {
            const ecs_entity_t *r = ecs_bulk_init(world, &(ecs_bulk_desc_t) {
                .table = table,
                .count = 1
            });
            return r[0];
        }

        #define ecs_get_parent(world, entity) ecs_get_target(world, entity, EcsChildOf, 0)
    #endif
#else
    #define query_terms terms
    #define observer_terms query.terms
    #define term_trav trav
    #define term_trav_flags src.id
    #define make_inheritable(world, component) ecs_add_pair(world, component, EcsOnInstantiate, EcsInherit)
    #define query_get_count(query) ecs_query_count(query).entities

    #define ecs_filter_t ecs_query_t
    #define ecs_filter_desc_t ecs_query_desc_t
    #define ecs_filter_init ecs_query_init
    #define ecs_filter_fini ecs_query_fini
    #define ecs_filter_iter ecs_query_iter
    #define ecs_filter_next ecs_query_next
    #define ecs_filter ecs_query
#endif

#ifdef NDEBUG
// accurate measurement in release mode
#define WARMUP_INTERVALS (5)
#define MEASURE_INTERVAL (50)
#define MEASURE_TIME (0.5)
#else
// run to verify tests don't assert in debug mode
#define WARMUP_INTERVALS (1)
#define MEASURE_INTERVAL (1)
#define MEASURE_TIME (0.05)
#endif

// #define PRETTY_TIME_FMT

typedef struct bench_t {
    // Benchmark state
    // The number of times a benchmark is run before taking a measurement.
    uint32_t interval;
    // The total number of intervals that have been run.
    uint32_t intervals;
    // The time at which the benchmark was started.
    ecs_time_t t;
    // The time it took to run the benchmark.
    double dt;

    // Benchmark settings
    // The label of the benchmark.
    const char *lbl;
    // The number of times the operation is run per interval.
    uint32_t count;
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

    ecs_os_vsnprintf(result, size + 1, fmt, args);

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
    return b;
}

double time_measure(
    ecs_time_t *start)
{
    ecs_time_t stop;
    ecs_os_get_time(&stop);
    return ecs_time_to_double(ecs_time_sub(stop, *start));
}

bool bench_next(bench_t *b) {
    if (!--b->interval) {
        b->intervals ++;
        if (b->intervals > WARMUP_INTERVALS) {
            double dt = time_measure(&b->t);
            if (dt > MEASURE_TIME) {
                b->dt = dt;
                return false;
            }
        } else if (b->intervals == WARMUP_INTERVALS) {
            ecs_os_get_time(&b->t);
        }
        b->interval = MEASURE_INTERVAL;
    }
    return true;
}

void bench_end(bench_t *b) {
    bench_print(b->lbl, b->dt / ((b->intervals - WARMUP_INTERVALS) * MEASURE_INTERVAL * b->count));
}

/* -- benchmark code -- */

/* Number of entities created for most benchmarks */
#define ENTITY_COUNT (1000)

/* Number of entities used for query benchmark */
#define QUERY_ENTITY_COUNT (65536)

ecs_entity_t* create_ids(
    ecs_world_t *world, int32_t count, ecs_size_t size, bool low, bool sparse, bool fragment) 
{
    if (count) {
        ecs_entity_t *ids = ecs_os_calloc_n(ecs_entity_t, count);
        for (int i = 0; i < count; i ++) {
            if (low) {
                ids[i] = ecs_new_low_id(world);
            } else {
                ids[i] = ecs_new(world);
            }
            if (size) {
                ecs_set(world, ids[i], EcsComponent, {size, 4});
            }
            #if FLECS_VERSION_NUMBER >= 40000
            if (sparse) {
                ecs_add_id(world, ids[i], EcsSparse);
            }
            #endif
            #if FLECS_VERSION_NUMBER > 40005
            if (!fragment) {
                ecs_add_id(world, ids[i], EcsDontFragment);
            }
            #endif
        }
        return ids;
    } else {
        return NULL;
    }
}

void baseline(void) {
    bench_t b = bench_begin("baseline", 1);
    do {
    } while (bench_next(&b));
    bench_end(&b);
}

void world_mini_fini(void) {
    bench_t b = bench_begin("world_mini_fini", 1);
    do {
        ecs_world_t *world = ecs_mini();
        ecs_fini(world);
    } while (bench_next(&b));
    bench_end(&b);
}

void world_init_fini(void) {
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
        ecs_entity_t s = ecs_system(world, {
            .callback = System
        });

        ecs_add_pair(world, s, EcsDependsOn, EcsOnUpdate);
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
    ecs_entity_t *ids = create_ids(world, id_count - 1, 0, true, false, true);

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

    ecs_os_free(ids);
}

void match_table_w_query(const char *label, int32_t term_count, int32_t match_count, int32_t total_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, term_count + 1, 0, true, false, true);

    for (int i = 0; i < match_count; i ++) {
        ecs_query_desc_t desc = {
            #if FLECS_VERSION_NUMBER >= 40000
                .cache_kind = EcsQueryCacheAuto
            #else
                0
            #endif
        };

        for (int t = 0; t < term_count; t ++) {
            desc.query_terms[t].id = ids[t];
            desc.query_terms[t].term_trav_flags = EcsSelf;
        }

        ecs_query_init(world, &desc);
    }

    for (int i = 0; i < total_count - match_count; i ++) {
        ecs_query_desc_t desc = {
            #if FLECS_VERSION_NUMBER >= 40000
                .cache_kind = EcsQueryCacheAuto
            #else
                0
            #endif
        };

        for (int t = 0; t < term_count; t ++) {
            desc.query_terms[t].id = ids[t];
            desc.query_terms[t].term_trav_flags = EcsSelf;
        }

        desc.query_terms[term_count].id = ids[term_count]; /* doesn't match table */
        desc.query_terms[term_count].term_trav_flags = EcsSelf;

        ecs_query_init(world, &desc);
    }

    ecs_table_t *table = NULL;
    for (int t = 0; t < term_count; t ++) {
        table = ecs_table_add_id(world, table, ids[t]);
    }

    bench_t b = bench_begin(label, 2);
    do {
        ecs_entity_t id = ecs_new_low_id(world);
        ecs_table_add_id(world, table, id);
        ecs_delete(world, id);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

void rematch_tables(const char *label, int32_t rematch_count, int32_t total_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, 0, true, false, true);

    make_inheritable(world, ids[0]);

    ecs_entity_t base_1 = ecs_new_w_id(world, ids[0]);
    ecs_entity_t base_2 = ecs_new_w_id(world, ids[0]);

    for (int i = 0; i < rematch_count; i ++) {
        ecs_table_t *table = ecs_table_add_id(world, NULL, ecs_pair(EcsIsA, base_1));
        table = ecs_table_add_id(world, table, ecs_new_low_id(world));
        ecs_new_w_table(world, table);
    }
    for (int i = 0; i < (total_count - rematch_count); i ++) {
        ecs_table_t *table = ecs_table_add_id(world, NULL, ecs_pair(EcsIsA, base_2));
        table = ecs_table_add_id(world, table, ecs_new_low_id(world));
        ecs_new_w_table(world, table);
    }

    ecs_query(world, {
        .query_terms[0].id = ids[0], /* matches table */
        .query_terms[0].term_trav_flags = EcsSelf,
        #if FLECS_VERSION_NUMBER >= 40000
            .cache_kind = EcsQueryCacheAuto
        #endif
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

    ecs_os_free(ids);
}

void table_add_remove(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

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

    ecs_os_free(ids);
}

void has_id_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 2, 0, true, false, true);

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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

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

void owns_id_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 2, 0, true, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }

    bench_t b = bench_begin("owns_id_not_found", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_owns_id(world, entities[e], ids[1]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void owns_id(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_owns_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_id_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 2, 4, true, false, true);

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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

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

void get_mut_not_found(void) {
    #if FLECS_VERSION_NUMBER < 30212
        printf("get_mut_not_found\n"); // get_mut was ensure pre 3.2.12
        return;
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 2, 4, true, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }
    
    bench_t b = bench_begin("get_mut_not_found", ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_mut_id(world, entities[e], ids[1]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void get_mut_id(const char *label, int32_t id_count, bool sparse, bool fragment) {
    #if FLECS_VERSION_NUMBER < 30212
        printf("%s\n", label); // get_mut was ensure pre 3.2.12
        return;
    #endif

    #if FLECS_VERSION_NUMBER < 40000
        if (sparse) {
            printf("%s\n", label);
            return;
        }
    #endif
    #if FLECS_VERSION_NUMBER <= 40005
        if (!fragment) {
            printf("%s\n", label);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, sparse, fragment);

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

void get_target_not_found(const char *label, bool exclusive, bool fragment) {
    #if FLECS_VERSION_NUMBER <= 40005
        if (!fragment) {
            printf("%s\n", label);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t rel = ecs_new(world);

    if (exclusive) {
        ecs_add_id(world, rel, EcsExclusive);
    }
    #if FLECS_VERSION_NUMBER > 40005
        if (!fragment) {
            ecs_add_id(world, rel, EcsDontFragment);
        }
    #endif

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_target(world, entities[e], rel, 0);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
}

void get_target(const char *label, bool exclusive, bool fragment) {
    #if FLECS_VERSION_NUMBER <= 40005
        if (!fragment) {
            printf("%s\n", label);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *tgts = create_ids(world, 8, 0, false, false, true);
    ecs_entity_t rel = ecs_new(world);

    if (exclusive) {
        ecs_add_id(world, rel, EcsExclusive);
    }
    #if FLECS_VERSION_NUMBER > 40005
        if (!fragment) {
            ecs_add_id(world, rel, EcsDontFragment);
        }
    #endif

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_pair(world, entities[e], rel, tgts[e % 8]);
    }

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_target(world, entities[e], rel, 0);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(tgts);
}

void get_parent_not_found(const char *label) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *tgts = create_ids(world, 8, 0, false, false, true);

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_parent(world, entities[e]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(tgts);
}

void get_parent(const char *label) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *tgts = create_ids(world, 8, 0, false, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_pair(world, entities[e], EcsChildOf, tgts[e % 8]);
    }

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_parent(world, entities[e]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(tgts);
}

void get_sparse_not_found(const char *label, int32_t id_count) {
    #if FLECS_VERSION_NUMBER > 40005
        ecs_world_t *world = ecs_mini();
        ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
        ecs_entity_t *ids = create_ids(world, id_count, 4, true, true, false);

        bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
        do {
            for (int e = 0; e < ENTITY_COUNT; e ++) {
                for (int i = 0; i < id_count; i ++) {
                    ecs_get_sparse_id(world, entities[e], ids[i]);
                }
            }
        } while (bench_next(&b));
        bench_end(&b);

        ecs_fini(world);
        ecs_os_free(entities);
        ecs_os_free(ids);
    #else
        printf("%s\n", label);
    #endif
}

void get_sparse_id(const char *label, int32_t id_count) {
    #if FLECS_VERSION_NUMBER > 40005
        ecs_world_t *world = ecs_mini();
        ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
        ecs_entity_t *ids = create_ids(world, id_count, 4, true, true, false);

        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_add_id(world, entities[e], ids[i]);
            }
        }

        bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
        do {
            for (int e = 0; e < ENTITY_COUNT; e ++) {
                for (int i = 0; i < id_count; i ++) {
                    ecs_get_sparse_id(world, entities[e], ids[i]);
                }
            }
        } while (bench_next(&b));
        bench_end(&b);

        ecs_fini(world);
        ecs_os_free(entities);
        ecs_os_free(ids);
    #else
        printf("%s\n", label);
    #endif
}

void ensure_id(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_ensure_id(world, entities[e], ids[i]);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
    ecs_os_free(ids);
}

void ensure_remove(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_ensure_id(world, entities[e], ids[i]);
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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *rel = create_ids(world, 1, 4, true, false, true);
    ecs_entity_t *tgt = create_ids(world, target_count, 0, false, false, true);

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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t id = ecs_new(world); ecs_set(world, id, EcsComponent, {4, 4});

    make_inheritable(world, id);

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

    ecs_os_free(entities);
}

void ref_init(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 1, 4, true, false, true);
    
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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 1, 4, true, false, true);
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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, false, true);

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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, false, true);

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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, component_count, 4, true, false, true);
    ecs_entity_t tag = ecs_new(world);

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
    ecs_os_free(ids);
}

void add_remove_override(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    ecs_entity_t base = ecs_new(world);
    for (int i = 0; i < id_count; i ++) {
        make_inheritable(world, ids[i]);
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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

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
    ecs_entity_t *entities = create_ids(world, entity_count, 0, false, false, true);

    ecs_entity_t id = ecs_new(world);
    ecs_entity_t add_id = ecs_new(world);

    ecs_observer(world, {
        .observer_terms = {{ id, .term_trav_flags = EcsSelf }},
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
    ecs_os_free(entities);
}

void add_remove_cmd(const char* label, int32_t id_count, bool component) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, false, true);

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

void ensure_remove_cmd(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_ensure_id(world, entities[e], ids[i]);
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

void ensure_cmd(const char* label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
    do {
        ecs_defer_begin(world);
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_ensure_id(world, entities[e], ids[i]);
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
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

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
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, false, true);

    bench_t b = bench_begin(label, ENTITY_COUNT * (2 + id_count));
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_entity_t e = ecs_new(world);
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

void create_children_w_reachable(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, false, true, false, true);

    bench_t b = bench_begin("create_children_w_reachable", ENTITY_COUNT * 2);
    do {
        ecs_entity_t parent = ecs_new(world);
        ecs_add_id(world, parent, ids[0]);

        for (int i = 0; i < ENTITY_COUNT; i ++) {
            ecs_entity_t p1 = 
                ecs_new_w_pair(world, EcsChildOf, parent);
            ecs_entity_t p2 = 
                ecs_new_w_pair(world, EcsChildOf, p1);
            ecs_new_w_pair(world, EcsChildOf, p1);
            ecs_new_w_pair(world, EcsChildOf, p2);
        }

        ecs_delete(world, parent);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

void create_delete_tree(const char *label, int32_t width, int32_t depth) {
    ecs_world_t *world = ecs_mini();

    bench_t b = bench_begin(label, width); /* calculate overhead per child */
    do {
        ecs_entity_t root = ecs_new(world), cur = root;
        for (int i = 0; i < depth; i ++) {
            for (int w = 0; w < width - 1; w ++) {
                ecs_entity_t e = ecs_new(world);
                ecs_add_pair(world, e, EcsChildOf, cur);
            }
            ecs_entity_t e = ecs_new(world);
            ecs_add_pair(world, e, EcsChildOf, cur);
            cur = e;
        }

        ecs_delete(world, root);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

void instantiate_delete_tree(const char *label, int32_t width, int32_t depth, int32_t components) {
    ecs_world_t *world = ecs_mini();

    ecs_id_t *ids = create_ids(world, components, 4, true, false, true);

    // In a prefab hierarchy children usually don't have the same archetype, so
    // give each child a different tag.
    ecs_id_t *child_tags = create_ids(world, width, 0, true, false, true);

    ecs_entity_t root = ecs_new_w_id(world, EcsPrefab), cur = root;
    for (int c = 0; c < components; c ++) {
        ecs_add_id(world, root, ids[c]);
    }

    for (int i = 0; i < depth; i ++) {
        for (int w = 0; w < width - 1; w ++) {
            ecs_entity_t e = ecs_new(world);
            ecs_add_pair(world, e, EcsChildOf, cur);

            for (int c = 0; c < components; c ++) {
                ecs_add_id(world, e, ids[c]);
            }
            ecs_add_id(world, e, child_tags[w]);
        }
        ecs_entity_t e = ecs_new(world);
        ecs_add_pair(world, e, EcsChildOf, cur);
        for (int c = 0; c < components; c ++) {
            ecs_add_id(world, e, ids[c]);
        }
        cur = e;
    }

    bench_t b = bench_begin(label, 2);
    do {
        ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, root);
        ecs_delete(world, e);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

void change_parent(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t p1 = ecs_new(world);
    ecs_entity_t p2 = ecs_new(world);

    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);

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
    ecs_os_free(entities);
}

void change_parent_root(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t p = ecs_new(world);
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);

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
    ecs_os_free(entities);
}

void change_parent_w_name(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t p1 = ecs_entity(world, { .name = "parent_1" });
    ecs_entity_t p2 = ecs_entity(world, { .name = "parent_2" });
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        char name[256];
        sprintf(name, "child_%d", e);
        ecs_set_name(world, entities[e], name);
        ecs_add_pair(world, entities[e], EcsChildOf, p2);
    }

    bench_t b = bench_begin("change_parent_w_name", 2 * ENTITY_COUNT);
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
    ecs_os_free(entities);
}

void lookup(const char *label, int32_t depth) {
    ecs_world_t *world = ecs_mini();

    char *lookup_str = ecs_os_strdup("foo");
    for (int i = 0; i < depth; i ++) {
        char *tmp = bench_asprintf("%s.foo", lookup_str);
        ecs_os_free(lookup_str);
        lookup_str = tmp;
    }

    ecs_entity_t e = ecs_entity(world, { .name = "foo" });
    for (int i = 0; i < depth; i ++) {
        ecs_entity_t child = ecs_new_w_pair(world, EcsChildOf, e);
        ecs_set_name(world, child, "foo");
        e = child;
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_lookup(world, lookup_str);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_os_free(lookup_str);

    ecs_fini(world);
}

void set_name(void) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t e = ecs_new(world);

    bench_t b = bench_begin("set_name", 2);
    do {
        ecs_set_name(world, e, "foo");
        ecs_set_name(world, e, NULL);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
}

static void Dummy(ecs_iter_t *it) { }

void emit(const char *label, int32_t observer_count, int32_t term_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 8, 0, true, false, true);
    ecs_entity_t evt = ecs_new(world);
    ecs_entity_t *entities = ecs_os_malloc_n(ecs_entity_t, ENTITY_COUNT);

    for (int i = 0; i < ENTITY_COUNT; i ++) {
        entities[i] = ecs_new(world);

        ecs_add_id(world, entities[i], ids[0]);

        for (int t = 1; t < 8; t ++) {
            if (flip_coin()) {
                ecs_add_id(world, entities[i], ids[t]);
            }
        }
    }

    for (int i = 0; i < observer_count; i ++) {
        ecs_observer_desc_t desc = {
            .callback = Dummy,
            .events = { evt }
        };

        for (int t = 0; t < term_count; t ++) {
            desc.observer_terms[t].id = ids[t];
            desc.observer_terms[t].term_trav_flags = EcsSelf;
        }

        ecs_observer_init(world, &desc);
    }

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int i = 0; i < ENTITY_COUNT; i ++) {
            ecs_emit(world, &(ecs_event_desc_t) {
                .event = evt,
                .ids = &(ecs_type_t){ .array = &ids[0], .count = 1 },
                #if FLECS_VERSION_NUMBER >= 30205
                    .entity = entities[i],
                #else
                    .table = ecs_get_table(world, entities[i]),
                #endif
                .observable = world
            });
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(entities);
    ecs_os_free(ids);
}

void modified(const char *label, int32_t observer_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, 4, true, false, true);
    ecs_entity_t e = ecs_new_w_id(world, ids[0]);

    for (int i = 0; i < observer_count; i ++) {
        ecs_observer(world, {
            .observer_terms = {{ ids[0], .term_trav_flags = EcsSelf }},
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

    ecs_os_free(ids);
}

void emit_propagate(const char *label, int32_t depth) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 1, 0, true, false, true);
    make_inheritable(world, ids[0]);

    ecs_entity_t root = ecs_new_w_id(world, ids[0]), cur = root;
    ecs_table_t *root_table = ecs_get_table(world, root);
    ecs_entity_t evt = ecs_new(world);

    ecs_observer(world, {
        .observer_terms = {{ ids[0], .term_trav_flags = EcsUp, .term_trav = EcsChildOf }},
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

    ecs_os_free(ids);
}

void emit_forward(const char *label, int32_t id_count, int32_t depth) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);
    ecs_entity_t root = ecs_new(world), cur = root;

    for (int i = 0; i < id_count; i ++) {
        make_inheritable(world, ids[i]);
        ecs_observer(world, {
            .observer_terms = {{ ids[i], .term_trav_flags = EcsUp, .term_trav = EcsChildOf }},
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

    ecs_entity_t e = ecs_new(world);
    bench_t b = bench_begin(label, 1);
    do {
        ecs_add_pair(world, e, EcsChildOf, cur);
        ecs_remove_pair(world, e, EcsChildOf, cur);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

static
int util_delete_empty_tables(ecs_world_t *world, double budget) {
    #if FLECS_VERSION_NUMBER >= 40004
        ecs_delete_empty_tables_desc_t desc = {0};
        desc.delete_generation = 1;
        desc.time_budget_seconds = budget;
        return ecs_delete_empty_tables(world, &desc);
    #else
        return ecs_delete_empty_tables(world, 0, 0, 1, 0, budget);
    #endif
}

void delete_empty_tables(const char *label, int32_t table_count, int32_t empty_count, double budget) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, table_count, 0, true, false, true);
    ecs_entity_t *entities = ecs_os_malloc_n(ecs_entity_t, table_count);

    util_delete_empty_tables(world, budget);
    util_delete_empty_tables(world, budget);

    for (int i = 0; i < table_count; i ++) {
        entities[i] = ecs_new_w_id(world, ids[i]);
    }

    for (int i = 0; i < empty_count; i ++) {
        ecs_delete(world, entities[i]);
    }

    bench_t b = {0};
    ecs_time_measure(&b.t);
    int32_t deleted = util_delete_empty_tables(world, budget);
    if (deleted != 0) {
        #if FLECS_VERSION_NUMBER >= 30212
        abort(); // doesn't work < 3.2.12
        #endif
    }
    deleted = util_delete_empty_tables(world, budget);
    if (deleted != empty_count) {
        #if FLECS_VERSION_NUMBER >= 30212
        abort(); // doesn't work < 3.2.12
        #endif
    }
    b.dt = ecs_time_measure(&b.t);
    bench_print(label, b.dt);

    ecs_fini(world);

    ecs_os_free(ids);
}

void uncach_init_fini(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_filter_desc_t desc = {0};
        for (int i = 0; i < id_count; i ++) {
            desc.terms[i].id = ids[i];
            desc.terms[i].term_trav_flags = EcsSelf;
        }

        ecs_filter_t *f = ecs_filter_init(world, &desc);
        ecs_filter_fini(f);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

#if FLECS_VERSION_NUMBER < 40000
void uncach_query_iter(
    const char *label, int32_t id_count, int32_t term_count, bool component) 
{
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, false, true);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    ecs_filter_desc_t desc = {0};

    for (int i = 0; i < term_count; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].term_trav_flags = EcsSelf;
    }

    ecs_filter_t *f = ecs_filter_init(world, &desc);
    int32_t result = 0;

    if (!component) {
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
    } else {
        bench_t b = bench_begin(label, 1);
        do {
            ecs_iter_t it = ecs_filter_iter(world, f);
            while (ecs_filter_next(&it)) {
                for (int f = 0; f < term_count; f ++) {
                    ecs_field_w_size(&it, 0, f);
                }
    
                for (int i = 0; i < it.count; i ++) {
                    result += it.entities[i];
                }
            }
        } while (bench_next(&b));
        bench_end(&b);
    }

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_filter_fini(f);
    ecs_fini(world);

    ecs_os_free(ids);
}
#endif

void query_iter(
    const char *label, ecs_query_cache_kind_t cache_kind, int32_t id_count, int32_t term_count, bool component, bool sparse, bool fragment) 
{
    #if FLECS_VERSION_NUMBER < 40000
        if (sparse) {
            printf("%s\n", label);
            return;
        }
        if (!fragment) {
            printf("%s\n", label);
            return;
        }

        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_iter(label, id_count, term_count, component);
        }
    #endif
    #if FLECS_VERSION_NUMBER <= 40005
        if (!fragment) {
            printf("%s\n", label);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, sparse, fragment);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    ecs_query_desc_t desc = {0};
    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    for (int i = 0; i < term_count; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
    }

    ecs_query_t *f = ecs_query_init(world, &desc);
    int32_t result = 0;

    if (!component) {
        bench_t b = bench_begin(label, 1);
        do {
            ecs_iter_t it = ecs_query_iter(world, f);
            while (ecs_query_next(&it)) {    
                for (int i = 0; i < it.count; i ++) {
                    result += it.entities[i];
                }
            }
        } while (bench_next(&b));
        bench_end(&b);
    } else if (!sparse && fragment) {
        bench_t b = bench_begin(label, 1);
        do {
            ecs_iter_t it = ecs_query_iter(world, f);
            while (ecs_query_next(&it)) {
                for (int f = 0; f < term_count; f ++) {
                    ecs_field_w_size(&it, 0, f);
                }
    
                for (int i = 0; i < it.count; i ++) {
                    result += it.entities[i];
                }
            }
        } while (bench_next(&b));
        bench_end(&b);
    } else if (sparse || !fragment) {
        bench_t b = bench_begin(label, 1);
        do {
            ecs_iter_t it = ecs_query_iter(world, f);
            while (ecs_query_next(&it)) {
                #if FLECS_VERSION_NUMBER < 40001
                    for (int f = 0; f < term_count; f ++) {
                        ecs_field_w_size(&it, 0, f);
                    }
                #endif
                for (int i = 0; i < it.count; i ++) {
                    #if FLECS_VERSION_NUMBER >= 40001
                        for (int f = 0; f < term_count; f ++) {
                            ecs_field_at_w_size(&it, 0, f, i);
                        }
                    #endif
                    result += it.entities[i];
                }
            }
        } while (bench_next(&b));
        bench_end(&b);
    }

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_query_fini(f);
    ecs_fini(world);

    ecs_os_free(ids);
}

void uncach_iter_up(const char *label, bool component, bool query_self) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, component ? 4 : 0, true, false, true);

    make_inheritable(world, ids[0]);

    ecs_entity_t parent_with = ecs_new(world);
    ecs_add_id(world, parent_with, ids[0]);
    ecs_entity_t parent_without = ecs_new(world);
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
    desc.terms[0].term_trav_flags = EcsUp;
    desc.terms[0].term_trav = EcsChildOf;
    if (query_self) {
        desc.terms[1].id = ids[1];
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

void uncach_iter_up_w_mut(const char *label, bool component, bool query_self) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, 2, component ? 4 : 0, true, false, true);
    
    make_inheritable(world, ids[0]);

    ecs_entity_t parent_with = ecs_new(world);
    ecs_add_id(world, parent_with, ids[0]);
    ecs_entity_t parent_without = ecs_new(world);
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
    desc.terms[0].term_trav_flags = EcsUp;
    desc.terms[0].term_trav = EcsChildOf;
    if (query_self) {
        desc.terms[1].id = ids[1];
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

void query_inheritance(const char *label, int32_t depth, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

    ecs_entity_t id = ecs_new(world);
    ecs_entity_t cur = id;
    for (int i = 0; i < depth; i ++) {
        cur = ecs_new_w_pair(world, EcsIsA, cur);
    }

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
        ecs_add_id(world, e, cur); /* derived id */
    }

    ecs_query_t *f = ecs_query(world, {
        .query_terms = {{ id, .term_trav_flags = EcsSelf }}
    });
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, f);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",
        result);

    ecs_query_fini(f);
    ecs_fini(world);

    ecs_os_free(ids);
}

void query_init_fini(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_query_desc_t desc = {
            #if FLECS_VERSION_NUMBER > 40000
                .cache_kind = EcsQueryCacheAuto
            #else
                0
            #endif
        };
        for (int i = 0; i < id_count; i ++) {
            desc.query_terms[i].id = ids[i];
            desc.query_terms[i].term_trav_flags = EcsSelf;
        }

        ecs_query_t *q = ecs_query_init(world, &desc);
        ecs_query_fini(q);
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

void query_iter_empty(const char *label, int32_t table_count, ecs_query_cache_kind_t cache_kind) {
    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            printf("%s\n", label);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *table_ids = create_ids(world, table_count + 1, 0, true, false, true);

    for (int i = 0; i < table_count; i ++) {
        ecs_entity_t e = ecs_new(world);

        /* Make sure entities have all queried for components */
        ecs_add_id(world, e, table_ids[table_count]);

        /* Make sure entities are spread over different tables */
        ecs_add_id(world, e, table_ids[i]);

        ecs_delete(world, e);
    }

    /* One non-empty table */
    ecs_entity_t e = ecs_new(world);
    ecs_add_id(world, e, table_ids[table_count]);

    ecs_query_t *q = ecs_query(world, {
        .query_terms = {{ table_ids[table_count], .term_trav_flags = EcsSelf }},
        #if FLECS_VERSION_NUMBER >= 40000
            .cache_kind = cache_kind
        #endif
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

void query_count(const char *label, int32_t table_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, table_count + 1, 0, true, false, true);

    for (int i = 0; i < table_count; i ++) {
        for (int j = 0; j < QUERY_ENTITY_COUNT / table_count; j ++) {
            ecs_entity_t e = ecs_new(world);

            /* Make sure entities have queried for component */
            ecs_add_id(world, e, ids[table_count]);

            /* Make sure entities are spread over different tables */
            ecs_add_id(world, e, ids[i]);
        }
    }

    ecs_query_t *q = ecs_query(world, {
        .query_terms = {{ ids[table_count], .term_trav_flags = EcsSelf }},
        #if FLECS_VERSION_NUMBER >= 40000
            .cache_kind = EcsQueryCacheAuto
        #endif
    });
    int32_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        result += query_get_count(q);
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_query_fini(q);
    ecs_fini(world);

    ecs_os_free(ids);
}

int main(int argc, char *argv[]) {
    ecs_os_set_api_defaults(); // Required for timers to work

    header_print();

    baseline();

    // World init fini
    world_mini_fini();
    world_init_fini();

    // Has
    has_id_not_found();
    has_id("has", 1);

    // Owns
    owns_id_not_found();
    owns_id("owns", 1);

    // Get
    get_id_not_found();
    get_id("get", 1);
    get_pair("get_pair", 1);

    // Get inherited
    get_inherited("get_inherited_depth_1", 1);
    get_inherited("get_inherited_depth_2", 2);
    get_inherited("get_inherited_depth_16", 16);

    // Get mut
    get_mut_not_found();
    get_mut_id("get_mut", 1, false, true);
    get_mut_id("get_mut_sparse", 1, true, true);
    get_mut_id("get_mut_dont_fragment", 1, true, false);

    // Get sparse
    get_sparse_not_found("get_sparse_not_found", 1);
    get_sparse_id("get_sparse", 1);

    // Get target
    get_target_not_found("get_target_not_found", false, true);
    get_target("get_target", false, true);
    get_target("get_target_dont_fragment", false, false);
    get_target("get_target_dont_fragment_exclusive", true, false);

    // Get parent
    get_parent_not_found("get_parent_not_found");
    get_parent("get_parent");

    // Ensure
    ensure_id("ensure", 1);

    // Set mut
    set_id("set_id", 1);

    // Ensure remove
    ensure_remove("ensure_remove", 1);
    ensure_remove("ensure_remove_16", 16);
    ensure_remove("ensure_remove_32", 32);

    // Ref
    ref_init();
    ref_get();

    // Add remove
    add_remove("add_remove_16_tags", 16, false);
    add_remove("add_remove_32_tags", 32, false);
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
    ensure_cmd("ensure_cmd_1", 1);
    ensure_cmd("ensure_cmd_2", 2);
    ensure_cmd("ensure_cmd_16", 16);
    ensure_cmd("ensure_cmd_32", 32);

    // Set cmd
    set_cmd("set_cmd_1", 1);
    set_cmd("set_cmd_2", 2);
    set_cmd("set_cmd_16", 16);
    set_cmd("set_cmd_32", 32);

    // Get mut remove cmd
    ensure_remove_cmd("ensure_remove_cmd_1", 1);
    ensure_remove_cmd("ensure_remove_cmd_2", 2);
    ensure_remove_cmd("ensure_remove_cmd_16", 16);
    ensure_remove_cmd("ensure_remove_cmd_32", 32);

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

    // Stresstest for event propagation
    create_children_w_reachable();

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

    // Instantiate prefabs
    instantiate_delete_tree("instantiate_delete_tree_w0_d0", 0, 0, 3);
    instantiate_delete_tree("instantiate_delete_tree_w1_d1", 1, 1, 3);
    instantiate_delete_tree("instantiate_delete_tree_w5_d1", 3, 1, 3);
    instantiate_delete_tree("instantiate_delete_tree_w10_d1", 10, 1, 3);
    instantiate_delete_tree("instantiate_delete_tree_w50_d1", 10, 1, 3);
    
    instantiate_delete_tree("instantiate_delete_tree_w1_d2", 1, 2, 3);
    instantiate_delete_tree("instantiate_delete_tree_w5_d2", 5, 2, 3);
    instantiate_delete_tree("instantiate_delete_tree_w10_d2", 10, 2, 3);
    instantiate_delete_tree("instantiate_delete_tree_w50_d2", 10, 2, 3);

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
    emit("emit_0_observers", 0, 1);
    emit("emit_1_observer", 1, 1);
    emit("emit_10_observers", 10, 1);
    emit("emit_50_observers", 50, 1);
    emit("emit_multi_2_100_observers", 50, 2);
    emit("emit_multi_4_100_observers", 50, 4);
    emit("emit_multi_8_100_observers", 50, 8);

    // Emit propagate
    emit_propagate("emit_propagate_depth_1", 0);
    emit_propagate("emit_propagate_depth_10", 10);
    emit_propagate("emit_propagate_depth_100", 100);

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

    // Empty table deletion
    delete_empty_tables("cleanup_tables_0_empty", 32768, 0, 0);
    delete_empty_tables("cleanup_tables_half_empty", 32768, 16384, 0);
    delete_empty_tables("cleanup_tables_all_empty", 32768, 32768, 0);
    delete_empty_tables("cleanup_tables_0_empty_w_budget", 32768, 0, 1);
    delete_empty_tables("cleanup_tables_half_empty_w_budget", 32768, 16384, 1);
    delete_empty_tables("cleanup_tables_all_empty_w_budget", 32768, 32768, 1);

    // Uncached query init fini
    uncach_init_fini("uncach_init_fini_1_ids", 1);
    uncach_init_fini("uncach_init_fini_4_ids", 4);
    uncach_init_fini("uncach_init_fini_8_ids", 8);
    uncach_init_fini("uncach_init_fini_16_ids", 16);

    // Uncached query iter
    query_iter("uncach_8_tags_1_term",           EcsQueryCacheDefault, 8,  1, false, false, true);
    query_iter("uncach_8_tags_4_terms",          EcsQueryCacheDefault, 8,  4, false, false, true);
    query_iter("uncach_16_tags_1_term",          EcsQueryCacheDefault, 16, 1, false, false, true);
    query_iter("uncach_16_tags_4_terms",         EcsQueryCacheDefault, 16, 4, false, false, true);
    query_iter("uncach_16_tags_8_terms",         EcsQueryCacheDefault, 16, 8, false, false, true);
    query_iter("uncach_8_comps_1_term",          EcsQueryCacheDefault, 8,  1, true,  false, true);
    query_iter("uncach_8_comps_4_terms",         EcsQueryCacheDefault, 8,  4, true,  false, true);
    query_iter("uncach_16_comps_1_term",         EcsQueryCacheDefault, 16, 1, true,  false, true);
    query_iter("uncach_16_comps_4_terms",        EcsQueryCacheDefault, 16, 4, true,  false, true);
    query_iter("uncach_16_comps_8_terms",        EcsQueryCacheDefault, 16, 8, true,  false, true);

    query_iter("uncach_16_sparse_tags_4_terms",  EcsQueryCacheDefault, 16, 4, false, true, true);
    query_iter("uncach_16_sparse_comps_4_terms", EcsQueryCacheDefault, 16, 4, true,  true, true);
    query_iter("uncach_16_nofrag_tags_4_terms",  EcsQueryCacheDefault, 16, 4, false, true, false);
    query_iter("uncach_16_nofrag_comps_4_terms", EcsQueryCacheDefault, 16, 4, true,  true, false);

    // Cached empty iter
    query_iter_empty("uncach_255_empty_1_fill", 256, EcsQueryCacheDefault);
    query_iter_empty("uncach_1023_empty_1_fill", 1024, EcsQueryCacheDefault);

    // Uncached query iter up
    uncach_iter_up("uncach_up_8_tags", false, false);
    uncach_iter_up("uncach_up_8_tags_w_self", false, true);

    // Uncached query iter up w mut
    uncach_iter_up_w_mut("uncach_up_w_mut_8_tags", false, false);
    uncach_iter_up_w_mut("uncach_up_w_mut_8_tags_w_self", false, true);

    // Uncached query inheritance
    query_inheritance("uncach_inherit_depth_1_tables_1", 1, 0);
    query_inheritance("uncach_inherit_depth_1_tables_1024", 1, 10);
    query_inheritance("uncach_inherit_depth_2_tables_1", 2, 0);
    query_inheritance("uncach_inherit_depth_2_tables_1024", 2, 10);
    query_inheritance("uncach_inherit_depth_8_tables_1", 8, 0);
    query_inheritance("uncach_inherit_depth_8_tables_1024", 8, 10);
    query_inheritance("uncach_inherit_depth_16_tables_1", 16, 0);
    query_inheritance("uncach_inherit_depth_16_tables_1024", 16, 10);

    // Cached init fini
    query_init_fini("cached_init_fini_1_ids", 1);
    query_init_fini("cached_init_fini_4_ids", 4);
    query_init_fini("cached_init_fini_8_ids", 8);
    query_init_fini("cached_init_fini_16_ids", 16);

    // Cached query iter
    query_iter("cached_8_tags_1_term", EcsQueryCacheAuto, 8, 1, false, false, true);
    query_iter("cached_8_tags_4_terms", EcsQueryCacheAuto, 8, 4, false, false, true);
    query_iter("cached_16_tags_1_term", EcsQueryCacheAuto, 16, 1, false, false, true);
    query_iter("cached_16_tags_4_terms", EcsQueryCacheAuto, 16, 4, false, false, true);
    query_iter("cached_16_tags_8_terms", EcsQueryCacheAuto, 16, 8, false, false, true);
    query_iter("cached_8_components_1_term", EcsQueryCacheAuto, 8, 1, true, false, true);
    query_iter("cached_8_components_4_terms", EcsQueryCacheAuto, 8, 4, true, false, true);
    query_iter("cached_16_components_1_term", EcsQueryCacheAuto, 16, 1, true, false, true);
    query_iter("cached_16_components_4_terms", EcsQueryCacheAuto, 16, 4, true, false, true);
    query_iter("cached_16_components_8_terms", EcsQueryCacheAuto, 16, 8, true, false, true);

    query_iter("cached_16_sparse_4_terms", EcsQueryCacheAuto, 16, 4, true, true, true);
    query_iter("cached_16_nofrag_4_terms", EcsQueryCacheAuto, 16, 4, true, true, false);

    // Cached empty iter
    query_iter_empty("cached_255_empty_1_fill", 256, EcsQueryCacheAuto);
    query_iter_empty("cached_1023_empty_1_fill", 1024, EcsQueryCacheAuto);

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
    match_table_w_query("match_1_of_100_queries_1_term",    1, 1, 100);
    match_table_w_query("match_10_of_100_queries_1_term",   1, 10, 100);
    match_table_w_query("match_100_of_100_queries_1_term",  1, 100, 100);
    match_table_w_query("match_1_of_100_queries_4_terms",   4, 1, 100);
    match_table_w_query("match_10_of_100_queries_4_terms",  4, 10, 100);
    match_table_w_query("match_100_of_100_queries_4_terms", 4, 100, 100);
    match_table_w_query("match_1_of_100_queries_8_terms",   8, 1, 100);
    match_table_w_query("match_10_of_100_queries_8_terms",  8, 10, 100);
    match_table_w_query("match_100_of_100_queries_8_terms", 8, 100, 100);

    // Rematch tables
    rematch_tables("rematch_1_of_1000_tables", 1, 1000);
    rematch_tables("rematch_10_of_1000_tables", 10, 1000);
    rematch_tables("rematch_100_of_1000_tables", 100, 1000);
    rematch_tables("rematch_1000_of_1000_tables", 1000, 1000);

    // Table add remove
    table_add_remove("table_add_remove_1_id", 1);
    table_add_remove("table_add_remove_4_ids", 4);
    table_add_remove("table_add_remove_16_ids", 16);
    table_add_remove("table_add_remove_32_ids", 32);
    table_add_remove("table_add_remove_64_ids", 64);

    return 0;
}
