#include "tests.h"

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

    bench_t b = bench_begin(label, ENTITY_COUNT);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            ecs_get_parent(world, entities[e]);
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
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
    #if FLECS_VERSION_NUMBER > 40006
        ecs_world_t *world = ecs_mini();
        ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
        ecs_entity_t *ids = create_ids(world, id_count, 4, true, true, false);

        bench_t b = bench_begin(label, ENTITY_COUNT * id_count);
        do {
            for (int e = 0; e < ENTITY_COUNT; e ++) {
                for (int i = 0; i < id_count; i ++) {
                    // ecs_get_sparse_id(world, entities[e], ids[i]);
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
    #if FLECS_VERSION_NUMBER > 40006
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
                    // ecs_get_sparse_id(world, entities[e], ids[i]);
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

void get_tests() {
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
}
