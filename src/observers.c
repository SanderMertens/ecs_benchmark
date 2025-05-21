#include "tests.h"

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

void observers_tests() {
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
}
