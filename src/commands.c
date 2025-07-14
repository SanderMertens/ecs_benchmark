#include "tests.h"

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
                ecs_ensure_id(world, entities[e], ids[i], 4);
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
                ecs_ensure_id(world, entities[e], ids[i], 4);
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

void commands_tests() {
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
}
