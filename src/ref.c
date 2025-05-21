#include "tests.h"

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

void ref_tests() {
    // Ref
    ref_init();
    ref_get();
}
