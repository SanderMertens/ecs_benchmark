#include "tests.h"

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
                    int32_t *ptr = ecs_field_w_size(&it, 0, f);
                    result += ptr[0];
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
    const char *label, ecs_query_cache_kind_t cache_kind, int32_t id_count, int32_t term_count, 
    bool component, bool sparse, bool fragment) 
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
            return;
        }
    #endif
    #if FLECS_VERSION_NUMBER <= 40005
        if (!fragment) {
            printf("%s\n", label);
            return;
        }
        if (sparse && !component) {
            // initially Sparse trait was not supported for tags
            printf("%s\n", label);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, component ? 4 : 0, true, sparse, fragment);

    ecs_query_desc_t desc = {0};
    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    for (int i = 0; i < term_count; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    // Create 100 other queries to increase cache element fragmentation
    if (cache_kind == EcsQueryCacheAuto) {
        for (int i = 0; i < 100; i ++) {
            ecs_query_init(world, &desc);
        }
    }

    ecs_query_t *f = ecs_query_init(world, &desc);
    int32_t result = 0;

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    if (!component) {
        if (cache_kind == EcsQueryCacheAuto) {
            bench_t b = bench_begin(label, 1);
            do {
                ecs_iter_t it = ecs_query_iter(world, f);
                while (flecs_query_trivial_cached_next(&it)) {    
                    for (int i = 0; i < it.count; i ++) {
                        result += it.entities[i];
                    }
                }
            } while (bench_next(&b));
            bench_end(&b);
        } else {
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
        }
    } else if (!sparse && fragment) {
        if (cache_kind == EcsQueryCacheAuto) {
            bench_t b = bench_begin(label, 1);
            do {
                ecs_iter_t it = ecs_query_iter(world, f);
                while (flecs_query_trivial_cached_next(&it)) {
                    for (int f = 0; f < term_count; f ++) {
                        int32_t *ptr = ecs_field_w_size(&it, 4, f);
                        result += ptr[0];
                    }
                    for (int i = 0; i < it.count; i ++) {
                        result += it.entities[i];
                    }
                }
            } while (bench_next(&b));
            bench_end(&b);
        } else {
            bench_t b = bench_begin(label, 1);
            do {
                ecs_iter_t it = ecs_query_iter(world, f);
                while (ecs_query_next(&it)) {
                    for (int f = 0; f < term_count; f ++) {
                        int32_t *ptr = ecs_field_w_size(&it, 4, f);
                        result += ptr[0];
                    }
                    for (int i = 0; i < it.count; i ++) {
                        result += it.entities[i];
                    }
                }
            } while (bench_next(&b));
            bench_end(&b);
        }
    } else if (sparse || !fragment) {
        bench_t b = bench_begin(label, 1);
        do {
            ecs_iter_t it = ecs_query_iter(world, f);
            while (ecs_query_next(&it)) {
                #if FLECS_VERSION_NUMBER < 40001
                    for (int f = 0; f < term_count; f ++) {
                        int32_t *ptr = ecs_field_w_size(&it, 4, f);
                        result += ptr[0];
                    }
                #endif
                for (int i = 0; i < it.count; i ++) {
                    #if FLECS_VERSION_NUMBER >= 40001
                        for (int f = 0; f < term_count; f ++) {
                            int32_t *ptr = ecs_field_at_w_size(&it, 4, f, i);
                            result += ptr[0];
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

void query_iter_read_1(
    const char *label, ecs_query_cache_kind_t cache_kind, int32_t id_count) 
{
    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_iter_read_1(label, id_count, term_count, component);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    ecs_query_desc_t desc = {0};
    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    for (int i = 0; i < 1; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    ecs_query_t *f = ecs_query_init(world, &desc);
    int32_t result = 0;

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, f);
        // optimized next call that's selected automatically by c++/system api
        while (flecs_query_trivial_cached_next(&it)) {
            int32_t *c1 = ecs_field_w_size(&it, 4, 0);
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
                result += c1[i];
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

void query_iter_read_4(
    const char *label, ecs_query_cache_kind_t cache_kind, int32_t id_count) 
{
    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_iter_read_4(label, id_count, term_count, component);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    ecs_query_desc_t desc = {0};
    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    for (int i = 0; i < 4; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    ecs_query_t *f = ecs_query_init(world, &desc);
    int32_t result = 0;

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, f);
        // optimized next call that's selected automatically by c++/system api
        while (flecs_query_trivial_cached_next(&it)) {
            int32_t *c1 = ecs_field_w_size(&it, 4, 0);
            int32_t *c2 = ecs_field_w_size(&it, 4, 1);
            int32_t *c3 = ecs_field_w_size(&it, 4, 2);
            int32_t *c4 = ecs_field_w_size(&it, 4, 3);
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
                result += c1[i];
                result += c2[i];
                result += c3[i];
                result += c4[i];
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

void query_iter_read_8(
    const char *label, ecs_query_cache_kind_t cache_kind, int32_t id_count) 
{
    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_iter_read_8(label, id_count, term_count, component);
            return;
        }
    #endif

    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);

    ecs_query_desc_t desc = {0};
    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    for (int i = 0; i < 8; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    ecs_query_t *f = ecs_query_init(world, &desc);
    int32_t result = 0;

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < id_count; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, f);
        // optimized next call that's selected automatically by c++/system api
        while (flecs_query_trivial_cached_next(&it)) {
            int32_t *c1 = ecs_field_w_size(&it, 4, 0);
            int32_t *c2 = ecs_field_w_size(&it, 4, 1);
            int32_t *c3 = ecs_field_w_size(&it, 4, 2);
            int32_t *c4 = ecs_field_w_size(&it, 4, 3);
            int32_t *c5 = ecs_field_w_size(&it, 4, 4);
            int32_t *c6 = ecs_field_w_size(&it, 4, 5);
            int32_t *c7 = ecs_field_w_size(&it, 4, 6);
            int32_t *c8 = ecs_field_w_size(&it, 4, 7);
            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
                result += c1[i];
                result += c2[i];
                result += c3[i];
                result += c4[i];
                result += c5[i];
                result += c6[i];
                result += c7[i];
                result += c8[i];
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

#if FLECS_VERSION_NUMBER < 40000
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
#endif

void query_iter_up(const char *label, ecs_query_cache_kind_t cache_kind, bool component, bool query_self) {
    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_iter_up(label, component, query_self);
            return;
        }
    #endif

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

        ecs_entity_t e = ecs_new_w_pair(world, EcsChildOf, parent);
        ecs_add_id(world, e, ids[1]);
    }

    ecs_filter_desc_t desc = {0};
    desc.terms[0].id = ids[0];
    desc.terms[0].term_trav_flags = EcsUp;
    desc.terms[0].term_trav = EcsChildOf;
    if (query_self) {
        desc.terms[1].id = ids[1];
    }

    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

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

    ecs_rule_t *f = ecs_rule(world, {
        .terms = {{ id, .term_trav_flags = EcsSelf }}
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

    ecs_os_free(ids);
}

void query_init_fini(const char *label, int32_t id_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, id_count, 0, true, false, true);

    bench_t b = bench_begin(label, 2);
    do {
        ecs_query_desc_t desc = {
            #if FLECS_VERSION_NUMBER >= 40000
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

    ecs_query_t *q = ecs_query(world, {
        .query_terms[0].id = ids[0], /* matches table */
        .query_terms[0].term_trav_flags = EcsSelf|EcsUp,
        #if FLECS_VERSION_NUMBER >= 40000
            .cache_kind = EcsQueryCacheAuto
        #endif
    });

    bench_t b = bench_begin(label, 2);
    do {
        ecs_remove_id(world, base_1, ids[0]);
        {
            ecs_iter_t it = ecs_query_iter(world, q);
            ecs_iter_fini(&it);
        }

        ecs_add_id(world, base_1, ids[0]);
        {
            ecs_iter_t it = ecs_query_iter(world, q);
            ecs_iter_fini(&it);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);

    ecs_os_free(ids);
}

void query_w_vars(const char *label, ecs_query_cache_kind_t cache_kind) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t SpaceShip = ecs_new(world);
    ecs_set_name(world, SpaceShip, "SpaceShip");
    ecs_entity_t DockedTo = ecs_new(world);
    ecs_set_name(world, DockedTo, "DockedTo");
    ecs_entity_t Planet = ecs_new(world);
    ecs_set_name(world, Planet, "Planet");
    ecs_entity_t Moon = ecs_new(world);
    ecs_set_name(world, Moon, "Moon");

    for (int p = 0; p < ENTITY_COUNT; p ++) {
        ecs_entity_t planet = ecs_new_w_id(world, Planet);

        for (int i = 0; i < 10; i ++) {
            ecs_entity_t spaceship = ecs_new_w_id(world, SpaceShip);
            ecs_add_pair(world, spaceship, DockedTo, planet);
            ecs_add_id(world, spaceship, ecs_new(world));
        }
    }

    for (int p = 0; p < ENTITY_COUNT; p ++) {
        ecs_entity_t moon = ecs_new_w_id(world, Moon);

        for (int i = 0; i < 10; i ++) {
            ecs_entity_t spaceship = ecs_new_w_id(world, SpaceShip);
            ecs_add_pair(world, spaceship, DockedTo, moon);
            ecs_add_id(world, spaceship, ecs_new(world));
        }
    }

    for (int p = 0; p < ENTITY_COUNT; p ++) {
        ecs_entity_t spaceship = ecs_new_w_id(world, SpaceShip);
        ecs_add_id(world, spaceship, ecs_new(world));
    }

    ecs_rule_t *q = ecs_rule(world, {
        .expr = "SpaceShip, (DockedTo, $planet), Planet($planet)",
    #if FLECS_VERSION_NUMBER >= 40000
        .cache_kind = cache_kind
    #endif
    });

    uint64_t result = 0;

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
}

#if FLECS_VERSION_NUMBER < 40000
void uncach_query_w_singleton(const char *label, ecs_world_t *world, ecs_entity_t *ids) {
    ecs_filter_desc_t desc = {0};

    for (int i = 0; i < 4; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].term_trav_flags = EcsSelf;
        desc.terms[i].inout = EcsIn;
    }

    desc.terms[4].id = ids[4];
    desc.terms[4].src.id = ids[4];
    desc.terms[4].inout = EcsIn;

    ecs_filter_t *q = ecs_filter_init(world, &desc);

    uint64_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, q);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < 5; i ++) {
                int32_t *f = ecs_field_w_size(&it, 4, i);
                result += *f;
            }

            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_filter_fini(q);

    ecs_os_free(ids);

    ecs_fini(world);
}
#endif

void query_w_singleton(const char *label, ecs_query_cache_kind_t cache_kind) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t *ids = create_ids(world, 5, 4, true, false, true);

    ecs_add_id(world, ids[4], ids[4]);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < 4; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }
    }

    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_w_singleton(label, world, ids);
            return;
        }
    #endif

    ecs_query_desc_t desc = {0};

    for (int i = 0; i < 4; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    desc.query_terms[4].id = ids[4];
    desc.query_terms[4].src.id = ids[4];
    desc.query_terms[4].inout = EcsIn;

    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    ecs_query_t *q = ecs_query_init(world, &desc);

    uint64_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < 5; i ++) {
                int32_t *f = ecs_field_w_size(&it, 4, i);
                result += *f;
            }

            for (int i = 0; i < it.count; i ++) {
                result += it.entities[i];
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    printf("result = %u\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b", 
        (uint32_t)result);

    ecs_query_fini(q);

    ecs_os_free(ids);

    ecs_fini(world);
}

#if FLECS_VERSION_NUMBER < 40000
void uncach_query_w_not(const char *label, ecs_world_t *world, ecs_entity_t rel, ecs_entity_t *ids) {
    ecs_filter_desc_t desc = {0};

    for (int i = 0; i < 4; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].term_trav_flags = EcsSelf;
        desc.terms[i].inout = EcsIn;
    }

    desc.terms[4].id = ids[4];
    desc.terms[4].oper = EcsNot;
    desc.terms[5].id = ecs_pair(rel, EcsWildcard);
    desc.terms[5].oper = EcsNot;

    ecs_filter_t *q = ecs_filter_init(world, &desc);

    uint64_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, q);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < 4; i ++) {
                int32_t *f = ecs_field_w_size(&it, 4, i);
                result += *f;
            }

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
#endif

void query_w_not(const char *label, ecs_query_cache_kind_t cache_kind) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t *ids = create_ids(world, 6, 4, true, false, true);
    ecs_entity_t rel = ecs_new(world);
    ecs_entity_t tgt = ecs_new(world);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < 6; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }

        if (flip_coin()) {
            ecs_add_pair(world, e, rel, tgt);
        }
    }

    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_w_not(label, world, rel, ids);
            return;
        }
    #endif

    ecs_query_desc_t desc = {0};

    for (int i = 0; i < 4; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    desc.query_terms[4].id = ids[4];
    desc.query_terms[4].oper = EcsNot;
    desc.query_terms[5].id = ecs_pair(rel, EcsWildcard);
    desc.query_terms[5].oper = EcsNot;

    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    ecs_query_t *q = ecs_query_init(world, &desc);

    uint64_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < 4; i ++) {
                int32_t *f = ecs_field_w_size(&it, 4, i);
                result += *f;
            }

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

#if FLECS_VERSION_NUMBER < 40000
void uncach_query_w_optional(const char *label, ecs_world_t *world, ecs_entity_t rel, ecs_entity_t *ids) {
    ecs_filter_desc_t desc = {0};

    for (int i = 0; i < 4; i ++) {
        desc.terms[i].id = ids[i];
        desc.terms[i].term_trav_flags = EcsSelf;
        desc.terms[i].inout = EcsIn;
    }

    desc.terms[4].id = ids[4];
    desc.terms[4].term_trav_flags = EcsSelf;
    desc.terms[4].oper = EcsOptional;

    ecs_filter_t *q = ecs_filter_init(world, &desc);

    uint64_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_filter_iter(world, q);
        while (ecs_filter_next(&it)) {
            for (int i = 0; i < 5; i ++) {
                int32_t *f = ecs_field_w_size(&it, 4, i);
                result += *f;
            }

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
#endif

void query_w_optional(const char *label, ecs_query_cache_kind_t cache_kind) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t *ids = create_ids(world, 6, 4, true, false, true);
    ecs_entity_t rel = ecs_new(world);
    ecs_entity_t tgt = ecs_new(world);

    for (int i = 0; i < QUERY_ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        for (int c = 0; c < 6; c ++) {
            if (flip_coin()) {
                ecs_add_id(world, e, ids[c]);
            }
        }

        if (flip_coin()) {
            ecs_add_pair(world, e, rel, tgt);
        }
    }

    #if FLECS_VERSION_NUMBER < 40000
        if (cache_kind == EcsQueryCacheDefault) {
            uncach_query_w_optional(label, world, rel, ids);
            return;
        }
    #endif

    ecs_query_desc_t desc = {0};

    for (int i = 0; i < 4; i ++) {
        desc.query_terms[i].id = ids[i];
        desc.query_terms[i].term_trav_flags = EcsSelf;
        desc.query_terms[i].inout = EcsIn;
    }

    desc.query_terms[4].id = ids[4];
    desc.query_terms[4].oper = EcsOptional;

    #if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = cache_kind;
    #endif

    ecs_query_t *q = ecs_query_init(world, &desc);

    uint64_t result = 0;

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            for (int i = 0; i < 4; i ++) {
                int32_t *f = ecs_field_w_size(&it, 4, i);
                result += *f;
            }

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

typedef struct {
    float x, y, z;
} LocalTransform, WorldTransform;

void query_transform(const char *label) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, LocalTransform);
    ECS_COMPONENT(world, WorldTransform);

    ecs_add_pair(world, ecs_id(LocalTransform), EcsWith, ecs_id(WorldTransform));

    ecs_query_t *q = ecs_query(world, {
        .query_terms = {
            { ecs_id(LocalTransform), .inout = EcsIn },
            { ecs_id(WorldTransform), .term_trav_flags = EcsCascade, .oper = EcsOptional, .inout = EcsIn },
            { ecs_id(WorldTransform), .inout = EcsOut },
        },
#if FLECS_VERSION_NUMBER >= 40000
        .cache_kind = EcsQueryCacheAuto
#endif
    });

    // Simulate hierarchy with lots of narrow assets
    for (int i = 0; i < ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        ecs_set(world, e, LocalTransform, {i, i * 2});

        for (int j = 0; j < 5; j ++) {
            ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, e);
            ecs_set(world, c, LocalTransform, {i, i * 2});

            for (int k = 0; k < 5; k ++) {
                ecs_entity_t gc = ecs_new_w_pair(world, EcsChildOf, c);
                ecs_set(world, gc, LocalTransform, {k, k * 2});

                for (int l = 0; l < 2; l ++) {
                    ecs_entity_t ggc = ecs_new_w_pair(world, EcsChildOf, gc);
                    ecs_set(world, ggc, LocalTransform, {l, l * 2});
                }
            }
        }
    }

    bench_t b = bench_begin(label, 1);
    do {
        ecs_iter_t it = ecs_query_iter(world, q);
        while (ecs_query_next(&it)) {
            LocalTransform *t = ecs_field(&it, LocalTransform, 0);
            WorldTransform *parent_wt = ecs_field(&it, WorldTransform, 1);
            WorldTransform *wt = ecs_field(&it, WorldTransform, 2);

            if (!parent_wt) {
                for (int i = 0; i < it.count; i ++) {
                    wt[i].x = t[i].x;
                    wt[i].y = t[i].y;
                    wt[i].z = t[i].z;
                }
            } else {
                for (int i = 0; i < it.count; i ++) {
                    wt[i].x = t[i].x + parent_wt->x;
                    wt[i].y = t[i].y + parent_wt->y;
                    wt[i].z = t[i].z + parent_wt->z;
                }
            }
        }
    } while (bench_next(&b));
    bench_end(&b);
    
    ecs_query_fini(q);

    ecs_fini(world);
}

static
void query_iter_dfs(ecs_world_t *world, ecs_query_t *q, ecs_entity_t parent) {
    ecs_iter_t it = ecs_query_iter(world, q);
    ecs_iter_set_group(&it, parent);

    while (ecs_query_next(&it)) {
        LocalTransform *t = ecs_field(&it, LocalTransform, 0);
        WorldTransform *parent_wt = ecs_field(&it, WorldTransform, 1);
        WorldTransform *wt = ecs_field(&it, WorldTransform, 2);

        for (int i = 0; i < it.count; i ++) {
            if (!parent_wt) {
                for (int i = 0; i < it.count; i ++) {
                    wt[i].x = t[i].x;
                    wt[i].y = t[i].y;
                    wt[i].z = t[i].z;
                }
            } else {
                for (int i = 0; i < it.count; i ++) {
                    wt[i].x = t[i].x + parent_wt->x;
                    wt[i].y = t[i].y + parent_wt->y;
                    wt[i].z = t[i].z + parent_wt->z;
                }
            }
        }

        for (int i = 0; i < it.count; i ++) {
            query_iter_dfs(world, q, it.entities[i]);
        }
    }
}

void query_depth_first(const char *label) {
    ecs_world_t *world = ecs_mini();

    ECS_COMPONENT(world, LocalTransform);
    ECS_COMPONENT(world, WorldTransform);

    ecs_add_pair(world, ecs_id(LocalTransform), EcsWith, ecs_id(WorldTransform));

    ecs_query_t *q = ecs_query(world, {
        .query_terms = {
            { ecs_id(LocalTransform), .inout = EcsIn },
            { ecs_id(WorldTransform), .term_trav_flags = EcsUp, .oper = EcsOptional, .inout = EcsIn },
            { ecs_id(WorldTransform), .inout = EcsOut },
        },
        .query_group_by = EcsChildOf,
#if FLECS_VERSION_NUMBER >= 40000
        .cache_kind = EcsQueryCacheAuto
#endif
    });

    // Simulate hierarchy with lots of narrow assets
    for (int i = 0; i < ENTITY_COUNT; i ++) {
        ecs_entity_t e = ecs_new(world);
        ecs_set(world, e, LocalTransform, {i, i * 2});

        for (int j = 0; j < 5; j ++) {
            ecs_entity_t c = ecs_new_w_pair(world, EcsChildOf, e);
            ecs_set(world, c, LocalTransform, {i, i * 2});

            for (int k = 0; k < 5; k ++) {
                ecs_entity_t gc = ecs_new_w_pair(world, EcsChildOf, c);
                ecs_set(world, gc, LocalTransform, {k, k * 2});

                for (int l = 0; l < 2; l ++) {
                    ecs_entity_t ggc = ecs_new_w_pair(world, EcsChildOf, gc);
                    ecs_set(world, ggc, LocalTransform, {l, l * 2});
                }
            }
        }
    }

    bench_t b = bench_begin(label, 1);
    do {
        query_iter_dfs(world, q, 0);
    } while (bench_next(&b));
    bench_end(&b);
    
    ecs_query_fini(q);

    ecs_fini(world);
}

void query_w_cantoggle_no_disabled(const char *label, int32_t term_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, term_count, 0, true, false, true);
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);

#if FLECS_VERSION_NUMBER >= 40000
    for (int i = 0; i < term_count; i ++) {
        ecs_add_id(world, ids[i], EcsCanToggle);
    }
#endif
    
    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < term_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    ecs_query_desc_t desc = {0};
    for (int i = 0; i < term_count; i ++) {
        desc.query_terms[i].id = ids[i];
    }

#if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = EcsQueryCacheAuto;
#endif

    ecs_query_t *q = ecs_query_init(world, &desc);

    uint64_t result = 0;
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
}

void query_w_cantoggle_half_disabled(const char *label, int32_t term_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, term_count, 0, true, false, true);
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);

#if FLECS_VERSION_NUMBER >= 40000
    for (int i = 0; i < term_count; i ++) {
        ecs_add_id(world, ids[i], EcsCanToggle);
    }
#endif
    
    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < term_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    for (int e = 0; e < ENTITY_COUNT / 2; e ++) {
        for (int i = 0; i < term_count; i ++) {
            ecs_enable_id(world, entities[e], ids[i], true);
        }
    }

    for (int e = ENTITY_COUNT / 2; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < term_count; i ++) {
            ecs_enable_id(world, entities[e], ids[i], false);
        }
    }

    ecs_query_desc_t desc = {0};
    for (int i = 0; i < term_count; i ++) {
        desc.query_terms[i].id = ids[i];
    }

#if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = EcsQueryCacheAuto;
#endif

    ecs_query_t *q = ecs_query_init(world, &desc);

    uint64_t result = 0;
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
}

void query_w_cantoggle_alt_disabled(const char *label, int32_t term_count) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *ids = create_ids(world, term_count, 0, true, false, true);
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);

#if FLECS_VERSION_NUMBER >= 40000
    for (int i = 0; i < term_count; i ++) {
        ecs_add_id(world, ids[i], EcsCanToggle);
    }
#endif
    
    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < term_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < term_count; i ++) {
            ecs_enable_id(world, entities[e], ids[i], (e % 2) == 0);
        }
    }

    ecs_query_desc_t desc = {0};
    for (int i = 0; i < term_count; i ++) {
        desc.query_terms[i].id = ids[i];
    }

#if FLECS_VERSION_NUMBER >= 40000
    desc.cache_kind = EcsQueryCacheAuto;
#endif

    ecs_query_t *q = ecs_query_init(world, &desc);

    uint64_t result = 0;
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
}

void query_tests() {
    // // Uncached query init fini
    uncach_init_fini("uncach_init_fini_1_ids", 1);
    uncach_init_fini("uncach_init_fini_4_ids", 4);
    uncach_init_fini("uncach_init_fini_8_ids", 8);
    uncach_init_fini("uncach_init_fini_16_ids", 16);

    // Uncached query iter
    query_iter("uncach_6_tags_1_term",           EcsQueryCacheDefault, 6,  1, false, false, true);
    query_iter("uncach_6_tags_4_terms",          EcsQueryCacheDefault, 6,  4, false, false, true);
    query_iter("uncach_10_tags_1_term",          EcsQueryCacheDefault, 10, 1, false, false, true);
    query_iter("uncach_10_tags_4_terms",         EcsQueryCacheDefault, 10, 4, false, false, true);
    query_iter("uncach_10_tags_8_terms",         EcsQueryCacheDefault, 10, 8, false, false, true);
    query_iter("uncach_6_comps_1_term",          EcsQueryCacheDefault, 6,  1, true,  false, true);
    query_iter("uncach_6_comps_4_terms",         EcsQueryCacheDefault, 6,  4, true,  false, true);
    query_iter("uncach_10_comps_1_term",         EcsQueryCacheDefault, 10, 1, true,  false, true);
    query_iter("uncach_10_comps_4_terms",        EcsQueryCacheDefault, 10, 4, true,  false, true);
    query_iter("uncach_10_comps_8_terms",        EcsQueryCacheDefault, 10, 8, true,  false, true);

    query_iter("uncach_10_sparse_tags_4_terms",  EcsQueryCacheDefault, 10, 4, false, true, true);
    query_iter("uncach_10_sparse_comps_4_terms", EcsQueryCacheDefault, 10, 4, true,  true, true);
    query_iter("uncach_10_nofrag_tags_4_terms",  EcsQueryCacheDefault, 10, 4, false, true, false);
    query_iter("uncach_10_nofrag_comps_4_terms", EcsQueryCacheDefault, 10, 4, true,  true, false);

    // Uncached empty iter
    query_iter_empty("uncach_255_empty_1_fill", 256, EcsQueryCacheDefault);
    query_iter_empty("uncach_1023_empty_1_fill", 1024, EcsQueryCacheDefault);

    // Uncached query iter up
    query_iter_up("uncach_up_tags", EcsQueryCacheDefault, false, false);
    query_iter_up("uncach_up_tags_w_self", EcsQueryCacheDefault, false, true);

    // Uncached query iter up w mut
    uncach_iter_up_w_mut("uncach_up_w_mut_8_tags", false, false);
    uncach_iter_up_w_mut("uncach_up_w_mut_8_tags_w_self", false, true);

    // Uncached query with variables
    query_w_vars("uncach_w_vars", EcsQueryCacheDefault);

    // Uncached query with singleton
    query_w_singleton("uncach_w_singleton", EcsQueryCacheDefault);

    // Uncached query with not
    query_w_not("uncach_w_not", EcsQueryCacheDefault);

    // Cached query with optional
    query_w_optional("uncach_w_optional", EcsQueryCacheDefault);

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
    query_iter("cached_6_tags_1_term", EcsQueryCacheAuto, 6, 1, false, false, true);
    query_iter("cached_6_tags_4_terms", EcsQueryCacheAuto, 6, 4, false, false, true);
    query_iter("cached_8_tags_1_term", EcsQueryCacheAuto, 8, 1, false, false, true);
    query_iter("cached_8_tags_4_terms", EcsQueryCacheAuto, 8, 4, false, false, true);
    query_iter("cached_10_tags_1_term", EcsQueryCacheAuto, 10, 1, false, false, true);
    query_iter("cached_10_tags_4_terms", EcsQueryCacheAuto, 10, 4, false, false, true);
    query_iter("cached_10_tags_8_terms", EcsQueryCacheAuto, 10, 8, false, false, true);
    query_iter("cached_16_tags_1_term", EcsQueryCacheAuto, 16, 1, false, false, true);
    query_iter("cached_16_tags_4_terms", EcsQueryCacheAuto, 16, 4, false, false, true);
    query_iter("cached_16_tags_8_terms", EcsQueryCacheAuto, 16, 8, false, false, true);

    query_iter("cached_6_components_1_term", EcsQueryCacheAuto, 6, 1, true, false, true);
    query_iter("cached_6_components_4_terms", EcsQueryCacheAuto, 6, 4, true, false, true);
    query_iter("cached_8_components_1_term", EcsQueryCacheAuto, 8, 1, true, false, true);
    query_iter("cached_8_components_4_terms", EcsQueryCacheAuto, 8, 4, true, false, true);
    query_iter("cached_10_components_1_term", EcsQueryCacheAuto, 10, 1, true, false, true);
    query_iter("cached_10_components_4_terms", EcsQueryCacheAuto, 10, 4, true, false, true);
    query_iter("cached_10_components_8_terms", EcsQueryCacheAuto, 10, 8, true, false, true);
    query_iter("cached_16_components_1_term", EcsQueryCacheAuto, 16, 1, true, false, true);
    query_iter("cached_16_components_4_terms", EcsQueryCacheAuto, 16, 4, true, false, true);
    query_iter("cached_16_components_8_terms", EcsQueryCacheAuto, 16, 8, true, false, true);

    // Cached query iter where the entire component array is read
    query_iter_read_1("cached_6_read_1_term", EcsQueryCacheAuto, 6);
    query_iter_read_4("cached_6_read_4_terms", EcsQueryCacheAuto, 6);
    query_iter_read_1("cached_8_read_1_term", EcsQueryCacheAuto, 8);
    query_iter_read_4("cached_8_read_4_terms", EcsQueryCacheAuto, 8);
    query_iter_read_1("cached_10_read_1_term", EcsQueryCacheAuto, 10);
    query_iter_read_4("cached_10_read_4_terms", EcsQueryCacheAuto, 10);
    query_iter_read_8("cached_10_read_8_terms", EcsQueryCacheAuto, 10);
    query_iter_read_1("cached_16_read_1_term", EcsQueryCacheAuto, 16);
    query_iter_read_4("cached_16_read_4_terms", EcsQueryCacheAuto, 16);
    query_iter_read_8("cached_16_read_8_terms", EcsQueryCacheAuto, 16);

    query_iter("cached_10_sparse_4_terms", EcsQueryCacheAuto, 10, 4, true, true, true);
    query_iter("cached_10_nofrag_4_terms", EcsQueryCacheAuto, 10, 4, true, true, false);

    // Cached empty iter
    query_iter_empty("cached_255_empty_1_fill", 256, EcsQueryCacheAuto);
    query_iter_empty("cached_1023_empty_1_fill", 1024, EcsQueryCacheAuto);

    // Cached query iter up
    query_iter_up("cached_up_tags", EcsQueryCacheAuto, false, false);
    query_iter_up("cached_up_tags_w_self", EcsQueryCacheAuto, false, true);

    // Cached query with variables
    query_w_vars("cached_w_vars", EcsQueryCacheAuto);

    // Cached query with singleton
    query_w_singleton("cached_w_singleton", EcsQueryCacheAuto);

    // Cached query with not
    query_w_not("cached_w_not", EcsQueryCacheAuto);

    // Cached query with optional
    query_w_optional("cached_w_optional", EcsQueryCacheAuto);

    // Cached with toggle
    query_w_cantoggle_no_disabled("cached_cantoggle_no_toggle_1_term", 1);
    query_w_cantoggle_no_disabled("cached_cantoggle_no_toggle_4_terms", 4);
    query_w_cantoggle_no_disabled("cached_cantoggle_no_toggle_8_terms", 8);

    query_w_cantoggle_half_disabled("cached_cantoggle_half_toggle_1_term", 1);
    query_w_cantoggle_half_disabled("cached_cantoggle_half_toggle_4_terms", 4);
    query_w_cantoggle_half_disabled("cached_cantoggle_half_toggle_8_terms", 8);

    query_w_cantoggle_alt_disabled("cached_cantoggle_alt_toggle_1_term", 1);
    query_w_cantoggle_alt_disabled("cached_cantoggle_alt_toggle_4_terms", 4);
    query_w_cantoggle_alt_disabled("cached_cantoggle_alt_toggle_8_terms", 8);

    /* Canonical transform system */
    query_transform("query_transform");

    /* Depth first iteration */
    query_depth_first("query_depth_first");

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
    // benchmark is broken in 3.1.0
    #if FLECS_VERSION_NUMBER != 30100
        rematch_tables("rematch_1_of_1000_tables", 1, 1000);
        rematch_tables("rematch_10_of_1000_tables", 10, 1000);
        rematch_tables("rematch_100_of_1000_tables", 100, 1000);
        rematch_tables("rematch_1000_of_1000_tables", 1000, 1000);
    #else
        // bugged in 3.1.0
        printf("rematch_1_of_1000_tables\n");
        printf("rematch_10_of_1000_tables\n");
        printf("rematch_100_of_1000_tables\n");
        printf("rematch_1000_of_1000_tables\n");
    #endif
}
