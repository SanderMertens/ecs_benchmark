#include "tests.h"

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

void parenting_names_tests() {
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
}
