#include "tests.h"

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

void create_delete_tests() {
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

    create_delete_tree("create_delete_tree_w10_d1", 10, 1);
    create_delete_tree("create_delete_tree_w10_d10", 10, 10);
    create_delete_tree("create_delete_tree_w10_d100", 10, 100);

    create_delete_tree("create_delete_tree_w100_d1", 100, 1);
    create_delete_tree("create_delete_tree_w100_d10", 100, 10);
    create_delete_tree("create_delete_tree_w100_d100", 100, 100);

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
}