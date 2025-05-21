#include "tests.h"

void has_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 2, 0, true, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }

    bench_t b = bench_begin("has_not_found", ENTITY_COUNT);
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

void owns_not_found(void) {
    ecs_world_t *world = ecs_mini();
    ecs_entity_t *entities = create_ids(world, ENTITY_COUNT, 0, false, false, true);
    ecs_entity_t *ids = create_ids(world, 2, 0, true, false, true);

    for (int e = 0; e < ENTITY_COUNT; e ++) {
        ecs_add_id(world, entities[e], ids[0]);
    }

    bench_t b = bench_begin("owns_not_found", ENTITY_COUNT);
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

void has_tests() {
    // Has
    has_not_found();
    has_id("has", 1);

    // Owns
    owns_not_found();
    owns_id("owns", 1);
}
