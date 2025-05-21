#include "tests.h"

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

void world_tests() {
    // World init fini
    world_mini_fini();
    world_init_fini();

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

    // Empty table deletion
    delete_empty_tables("cleanup_tables_0_empty", 32768, 0, 0);
    delete_empty_tables("cleanup_tables_half_empty", 32768, 16384, 0);
    delete_empty_tables("cleanup_tables_all_empty", 32768, 32768, 0);
    delete_empty_tables("cleanup_tables_0_empty_w_budget", 32768, 0, 1);
    delete_empty_tables("cleanup_tables_half_empty_w_budget", 32768, 16384, 1);
    delete_empty_tables("cleanup_tables_all_empty_w_budget", 32768, 32768, 1);
}
