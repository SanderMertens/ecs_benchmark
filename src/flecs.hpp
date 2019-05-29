#include <ecs_benchmark.h>

double iterate(ecs_world_t *world, int n_iter) {
    double result = 0;

    for (int i = 0; i < N_ITERATIONS; i ++) {
        struct timespec start; timespec_gettime(&start);
        
        /* Pass constant time, so flecs won't request time */
        ecs_progress(world, 1); 
        
        double t = timespec_measure(&start);
        if (!result || t < result) {
            result = t;
        }
    }

    return result;
}


double bench_create_empty_flecs(int n) {
    ecs_world_t *world = ecs_init();

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_new(world, 0);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_create_empty_flecs_batch(int n) {
    ecs_world_t *world = ecs_init();

    struct timespec start; timespec_gettime(&start);
    ecs_new_w_count(world, 0, n);
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_create_1component_flecs_batch(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    struct timespec start; timespec_gettime(&start);
    ecs_new_w_count(world, Position, n);
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_create_2component_flecs_batch(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Movable, Position, Velocity);

    struct timespec start; timespec_gettime(&start);
    ecs_new_w_count(world, Movable, n);
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_create_3component_flecs_batch(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Movable, Position, Velocity, Mass);

    struct timespec start; timespec_gettime(&start);
    ecs_new_w_count(world, Movable, n);
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_delete_1component_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_start = ecs_new_w_count(world, Position, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_delete(world, e_start + i);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_one_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Position);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_one_flecs_new(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_new(world, Position);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_two_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);
    ecs_dim(world, n);
    ecs_dim_type(world, Type, n);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Position);
        ecs_add(world, e_start + i, Velocity);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_two_flecs_family(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Type);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_three_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Position);
        ecs_add(world, e_start + i, Velocity);
        ecs_add(world, e_start + i, Mass);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_three_flecs_family(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type, Position, Velocity, Mass);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Type);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_four_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Position);
        ecs_add(world, e_start + i, Velocity);
        ecs_add(world, e_start + i, Mass);
        ecs_add(world, e_start + i, Color);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_add_four_flecs_family(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);
    ECS_TYPE(world, Type, Position, Velocity, Mass, Color);

    ecs_entity_t e_start = ecs_new_w_count(world, 0, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_add(world, e_start + i, Type);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}


double bench_remove_one_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e_start = ecs_new_w_count(world, Position, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_remove(world, e_start + i, Position);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_remove_two_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e_start = ecs_new_w_count(world, Type, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_remove(world, e_start + i, Position);
        ecs_remove(world, e_start + i, Velocity);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_remove_two_flecs_family(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Type, Position, Velocity);

    ecs_entity_t e_start = ecs_new_w_count(world, Type, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_remove(world, e_start + i, Type);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_remove_three_flecs(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type, Position, Velocity, Mass);

    ecs_entity_t e_start = ecs_new_w_count(world, Type, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_remove(world, e_start + i, Position);
        ecs_remove(world, e_start + i, Velocity);
        ecs_remove(world, e_start + i, Mass);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}

double bench_remove_three_flecs_family(int n) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Type, Position, Velocity, Mass);

    ecs_entity_t e_start = ecs_new_w_count(world, Type, n);

    struct timespec start; timespec_gettime(&start);
    for (int i = 0; i < n; i ++) {
        ecs_remove(world, e_start + i, Type);
    }
    double result = timespec_measure(&start);

    ecs_fini(world);

    return result;
}


/* -- ITERATION -- */

void IterSmall(ecs_rows_t *rows) {
    int count = rows->count;
    Mass *m = ecs_column(rows, Mass, 1);

    for (int i = 0; i < count; i ++) {
        m[i].value ++;
    }
}

void IterOne(ecs_rows_t *rows) {
    int count = rows->count;
    Position *p = ecs_column(rows, Position, 1);

    for (int i = 0; i < count; i ++) {
        p[i].x ++;
        p[i].y ++;
    }
}

void IterTwo(ecs_rows_t *rows) {
    int count = rows->count;
    Position *p = ecs_column(rows, Position, 1);
    Velocity *v = ecs_column(rows, Velocity, 2);

    for (int i = 0; i < count; i ++) {
        p[i].x += v[i].x;
        p[i].y += v[i].y;
    }
}

void IterThree(ecs_rows_t *rows) {
    int count = rows->count;
    Position *p = ecs_column(rows, Position, 1);
    Velocity *v = ecs_column(rows, Velocity, 2);
    Mass *m = ecs_column(rows, Mass, 3);

    for (int i = 0; i < count; i ++) {
        p[i].x += v[i].x / m[i].value;
        p[i].y += v[i].y / m[i].value;
    }
}

void IterFour(ecs_rows_t *rows) {
    int count = rows->count;
    Position *p = ecs_column(rows, Position, 1);
    Velocity *v = ecs_column(rows, Velocity, 2);
    Mass *m = ecs_column(rows, Mass, 3);
    Damage *d = ecs_column(rows, Damage, 4);

    for (int i = 0; i < count; i ++) {
        p[i].x += v[i].x / m[i].value / d[i].value;
        p[i].y += v[i].y / m[i].value / d[i].value;
    }
}

double bench_iter_small_flecs(int n, int n_iter) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Mass);
    ECS_SYSTEM(world, IterSmall, EcsOnUpdate, Mass);

    ecs_new_w_count(world, Mass, n);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_one_flecs(int n, int n_iter) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_SYSTEM(world, IterOne, EcsOnUpdate, Position);

    ecs_new_w_count(world, Position, n);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_two_flecs(int n, int n_iter) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_TYPE(world, Movable, Position, Velocity);
    ECS_SYSTEM(world, IterTwo, EcsOnUpdate, Position, Velocity);

    ecs_new_w_count(world, Movable, n);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_three_two_types_flecs(int n, int n_iter) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, TypeOne, Position, Velocity, Mass);
    ECS_TYPE(world, TypeTwo, Position, Velocity, Mass, Rotation);
    ECS_SYSTEM(world, IterThree, EcsOnUpdate, Position, Velocity, Mass);

    ecs_new_w_count(world, TypeOne, n / 2);
    ecs_new_w_count(world, TypeTwo, n / 2);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_three_flecs(int n, int n_iter) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Mass);
    ECS_TYPE(world, Movable, Position, Velocity, Mass);
    ECS_SYSTEM(world, IterThree, EcsOnUpdate, Position, Velocity, Mass);

    ecs_new_w_count(world, Movable, n);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

void create_eight_types(ecs_world_t *world, int count, bool match_all) {
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);
    ECS_COMPONENT(world, Battery);
    ECS_COMPONENT(world, Damage);

    for(uint64_t i = 0; i < count; i++) {
        ecs_entity_t e = ecs_new(world, 0);
        ecs_add(world, e, Position);
        ecs_add(world, e, Mass);
        ecs_add(world, e, Damage);
        if ((i % 8) == 1) {
            ecs_add(world, e, Rotation);
        } else 
        if ((i % 8) == 2) {
            ecs_add(world, e, Color);
        } else 
        if ((i % 8) == 3) {
            ecs_add(world, e, Battery);
        } else 
        if ((i % 8) == 4) {
            ecs_add(world, e, Rotation);
            ecs_add(world, e, Color);
        } else 
        if ((i % 8) == 5) {
            ecs_add(world, e, Rotation);
            ecs_add(world, e, Battery);
        } else 
        if ((i % 8) == 6) {
            ecs_add(world, e, Battery);
            ecs_add(world, e, Color);
        } else 
        if ((i % 8) == 7) {
            ecs_add(world, e, Rotation);
            ecs_add(world, e, Battery);
            ecs_add(world, e, Color);
        }

        if (match_all || i % 2) {
            ecs_add(world, e, Velocity);
        }
    }
}

double bench_iter_two_eight_types_flecs(int n, int n_iter, bool match_all) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);
    ECS_COMPONENT(world, Battery);

    int count = n * (2 - match_all);

    create_eight_types(world, count, match_all);

    ECS_SYSTEM(world, IterTwo, EcsOnUpdate, Position, Velocity);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_three_eight_types_flecs(int n, int n_iter, bool match_all) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);
    ECS_COMPONENT(world, Battery);

    int count = n * (2 - match_all);

    create_eight_types(world, count, match_all);

    ECS_SYSTEM(world, IterThree, EcsOnUpdate, Position, Velocity, Mass);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_four_eight_types_flecs(int n, int n_iter, bool match_all) {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);
    ECS_COMPONENT(world, Battery);
    ECS_COMPONENT(world, Damage);

    int count = n * (2 - match_all);

    create_eight_types(world, count, match_all);

    ECS_SYSTEM(world, IterFour, EcsOnUpdate, Position, Velocity, Mass, Damage);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

void create_pathological(ecs_world_t *world, std::vector< std::vector <int>> entity_list) {
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Rotation);
    ECS_COMPONENT(world, Mass);
    ECS_COMPONENT(world, Color);
    ECS_COMPONENT(world, Battery);
    ECS_COMPONENT(world, Damage);
    ECS_COMPONENT(world, Health);
    ECS_COMPONENT(world, Attack);
    ECS_COMPONENT(world, Defense);
    ECS_COMPONENT(world, Stamina);
    ECS_COMPONENT(world, Strength);
    ECS_COMPONENT(world, Agility);
    ECS_COMPONENT(world, Intelligence);

    for (std::vector<int> &component_list: entity_list) {
        ecs_entity_t e = ecs_new(world, 0);
        ecs_add(world, e, Position);
        ecs_add(world, e, Velocity);
        ecs_add(world, e, Mass);
        ecs_add(world, e, Damage);

        for (int c: component_list) {
            switch(c) {
            case 0:
                ecs_add(world, e, Stamina);
                break;
            case 1:
                ecs_add(world, e, Strength);
                break;
            case 2:
                ecs_add(world, e, Agility);
                break;
            case 3:
                ecs_add(world, e, Intelligence);
                break;
            case 4:
                ecs_add(world, e, Color);
                break;
            case 5:
                ecs_add(world, e, Battery);
                break;
            case 6:
                ecs_add(world, e, Rotation);
                break;
            case 7:
                ecs_add(world, e, Health);
                break;
            case 8:
                ecs_add(world, e, Attack);
                break;
            case 9:
                ecs_add(world, e, Defense);
                break;
            }
        }
    }
}

double bench_iter_one_pathological_flecs(int n_iter, std::vector< std::vector<int>> entity_list) {
    ecs_world_t *world = ecs_init();

    create_pathological(world, entity_list);

    ECS_SYSTEM(world, IterOne, EcsOnUpdate, Position);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_two_pathological_flecs(int n_iter, std::vector< std::vector<int>> entity_list) {
    ecs_world_t *world = ecs_init();

    create_pathological(world, entity_list);

    ECS_SYSTEM(world, IterTwo, EcsOnUpdate, Position, Velocity);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_three_pathological_flecs(int n_iter, std::vector< std::vector<int>> entity_list) {
    ecs_world_t *world = ecs_init();

    create_pathological(world, entity_list);

    ECS_SYSTEM(world, IterThree, EcsOnUpdate, Position, Velocity, Mass);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}

double bench_iter_four_pathological_flecs(int n_iter, std::vector< std::vector<int>> entity_list) {
    ecs_world_t *world = ecs_init();

    create_pathological(world, entity_list);

    ECS_SYSTEM(world, IterFour, EcsOnUpdate, Position, Velocity, Mass, Damage);

    double result = iterate(world, n_iter);

    ecs_fini(world);

    return result;
}
