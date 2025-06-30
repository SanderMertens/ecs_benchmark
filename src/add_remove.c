#include "tests.h"

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

void toggle_component(const char* label, int32_t id_count, bool component) {
    ecs_world_t *world = ecs_mini();

    ecs_entity_t *ids = create_ids(world, id_count, 4, true, false, true);
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    
#if FLECS_VERSION_NUMBER >= 40000
    for (int i = 0; i < id_count; i ++) {
        ecs_add_id(world, ids[i], EcsCanToggle);
    }
#endif

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        for (int i = 0; i < id_count; i ++) {
            ecs_add_id(world, entities[e], ids[i]);
        }
    }

    bench_t b = bench_begin(label, 2 * ENTITY_COUNT * id_count);
    do {
        for (int e = 0; e < ENTITY_COUNT; e ++) {
            for (int i = 0; i < id_count; i ++) {
                ecs_enable_id(world, entities[e], ids[i], true);
                ecs_enable_id(world, entities[e], ids[i], false);
            }
        }
    } while (bench_next(&b));
    bench_end(&b);

    ecs_fini(world);
    ecs_os_free(entities);
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

void add_remove_tests() {
    // Add remove
    add_remove("add_remove_1_tags", 1, false);
    add_remove("add_remove_2_tags", 2, false);
    add_remove("add_remove_16_tags", 16, false);
    add_remove("add_remove_32_tags", 32, false);
    return;
    add_remove("add_remove_1_components", 1, true);
    add_remove("add_remove_2_components", 2, true);
    add_remove("add_remove_16_components", 16, true);
    add_remove("add_remove_32_components", 32, true);

    // Add remove hooks
    add_remove_hooks("add_remove_hooks_1", 1);
    add_remove_hooks("add_remove_hooks_2", 2);
    add_remove_hooks("add_remove_hooks_16", 16);
    add_remove_hooks("add_remove_hooks_32", 32);

    // Table add remove
    table_add_remove("table_add_remove_1_id", 1);
    table_add_remove("table_add_remove_4_ids", 4);
    table_add_remove("table_add_remove_16_ids", 16);
    table_add_remove("table_add_remove_32_ids", 32);
    table_add_remove("table_add_remove_64_ids", 64);

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

    // Toggle
#if FLECS_VERSION_NUMBER > 30000
    toggle_component("toggle_16_tags", 16, false);
    toggle_component("toggle_32_tags", 32, false);
    toggle_component("toggle_16_components", 16, true);
    toggle_component("toggle_32_components", 32, true);
#else
    // crahes in v3
    printf("toggle_16_tags\n");
    printf("toggle_32_tags\n");
    printf("toggle_16_components\n");
    printf("toggle_32_components\n");
#endif
}
