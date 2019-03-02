#include <include/ecs_benchmark.h>

#define N_ENTITIES (1000000)
#define N_ITERATIONS (1000)

#define REFLECS
#define ENTT

/* -- Components -- */

struct Position {
    float x;
    float y;
};

struct Rotation {
    float angle;
};

struct Velocity {
    float x;
    float y;
};

struct Mass {
    float value;
};

struct Color {
    char r;
    char g;
    char b;
};

struct Battery {
    float charge;
    float output;
    float temperature;
};

struct Damage {
    float value;
};

#ifdef ENTT
#include "entt.hpp"
#endif
#ifdef REFLECS
#include "reflecs.hpp"
#endif

void bench_start(const char *title, unsigned int n) {
    printf("\n");
    printf("%s (n = %d):\n", title, n);
    printf("+---------+------------------------------------+\n");
}

void bench_report(const char *framework, double benchmark, const char *sub) {
    printf("|%8s |  %f %s %*s|\n", framework, benchmark, sub, (int)(24 - strlen(sub)), "");
}

void bench_stop() {
    printf("+---------+------------------------------------+\n");
}

/* Creation tests */
void bench_create(int n) {
    bench_start("Entity creation, empty", n);
    #ifdef ENTT    
    bench_report("EnTT",    bench_create_empty_entt(n), "");
    #endif
    #ifdef REFLECS 
    bench_report("Reflecs", bench_create_empty_reflecs(n), "");
    #endif
    #ifdef ENTT    
    bench_report("EnTT",    bench_create_empty_entt_batch(n), "(batching)");
    #endif
    #ifdef REFLECS 
    bench_report("Reflecs", bench_create_empty_reflecs_batch(n), "(batching)");
    #endif
    bench_stop();

    bench_start("Entity creation, 1 component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_create_1component_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_create_1component_reflecs_batch(n), "(batching)");
    #endif
    bench_stop();

    bench_start("Entity creation, 2 component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_create_2component_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_create_2component_reflecs_batch(n), "(batching, family)");
    #endif
    bench_stop();

    bench_start("Entity creation, 3 component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_create_3component_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_create_3component_reflecs_batch(n), "(batching, family)");
    #endif
    bench_stop();

    bench_start("Entity deletion, 1 component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_delete_1component_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_delete_1component_reflecs(n), "");
    #endif
    bench_stop();
}

/* Add/Remove tests */
void bench_add(int n) {
    bench_start("Add one component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_add_one_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_add_one_reflecs(n), "");
    bench_report("Reflecs", bench_add_one_reflecs_new(n), "(new w/component)");
    #endif
    bench_stop();

    bench_start("Add two components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_add_two_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_add_two_reflecs(n), "");
    bench_report("Reflecs", bench_add_two_reflecs_family(n), "(add w/family)");
    #endif
    bench_stop();

    bench_start("Add three components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_add_three_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_add_three_reflecs(n), "");
    bench_report("Reflecs", bench_add_three_reflecs_family(n), "(add w/family)");
    #endif
    bench_stop();

    bench_start("Add four components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_add_four_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_add_four_reflecs(n), "");
    bench_report("Reflecs", bench_add_four_reflecs_family(n), "(add w/family)");
    #endif
    bench_stop();

    bench_start("Remove one component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_remove_one_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_remove_one_reflecs(n), "");
    #endif
    bench_stop();

    bench_start("Remove two components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_remove_two_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_remove_two_reflecs(n), "");
    bench_report("Reflecs", bench_remove_two_reflecs_family(n), "(remove w/family)");
    #endif
    bench_stop();

    bench_start("Remove three components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_remove_three_entt(n), "");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_remove_three_reflecs(n), "");
    bench_report("Reflecs", bench_remove_three_reflecs_family(n), "(remove w/family)");
    #endif
    bench_stop();
}

/* Iteration tests */
void bench_iterate(int n, int n_iter) {
    bench_start("Iterate, one component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_one_entt_view(n, n_iter), "(view)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_one_reflecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, two components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_entt_view(n, n_iter), "(view)");
    bench_report("EnTT",    bench_iter_two_entt_group(n, n_iter), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_two_reflecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, two components, eight types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_eight_types_entt_view(n, n_iter, true), "(view)");
    bench_report("EnTT",    bench_iter_two_eight_types_entt_group(n, n_iter, true), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_two_eight_types_reflecs(n, n_iter, true), "");
    #endif
    bench_stop();

    bench_start("Iterate, two components, eight types, four matching", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_eight_types_entt_view(n, n_iter, false), "(view)");
    bench_report("EnTT",    bench_iter_two_eight_types_entt_group(n, n_iter, false), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_two_eight_types_reflecs(n, n_iter, false), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_entt_view(n, n_iter), "(view)");
    bench_report("EnTT",    bench_iter_three_entt_group(n, n_iter), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_three_reflecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components, two types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_two_types_entt_view(n, n_iter), "(view)");
    bench_report("EnTT",    bench_iter_three_two_types_entt_group(n, n_iter), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_three_two_types_reflecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components, eight types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_eight_types_entt_view(n, n_iter, true), "(view)");
    bench_report("EnTT",    bench_iter_three_eight_types_entt_group(n, n_iter, true), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_three_eight_types_reflecs(n, n_iter, true), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components, eight types, four matching", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_eight_types_entt_view(n, n_iter, false), "(view)");
    bench_report("EnTT",    bench_iter_three_eight_types_entt_group(n, n_iter, false), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_three_eight_types_reflecs(n, n_iter, false), "");
    #endif
    bench_stop();

    bench_start("Iterate, four components, eight types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_four_eight_types_entt_view(n, n_iter, true), "(view)");
    bench_report("EnTT",    bench_iter_four_eight_types_entt_group(n, n_iter, true), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_four_eight_types_reflecs(n, n_iter, true), "");
    #endif
    bench_stop();

    bench_start("Iterate, four components, eight types, four matching", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_four_eight_types_entt_view(n, n_iter, false), "(view)");
    bench_report("EnTT",    bench_iter_four_eight_types_entt_group(n, n_iter, false), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_four_eight_types_reflecs(n, n_iter, false), "");
    #endif
    bench_stop();
}

bool coin_toss() {
    int r = std::rand();
    
    if (r >= ((float)RAND_MAX / 2.0f)) {
        return true;
    } else {
        return false;
    }
}

/* Pathological tests (iteration w/10 randomized components) */
/*void bench_pathological(int n, int n_iter) {
    std::vector< std::vector<int> > entity_list;

    for (int i = 0; i < n; i ++) {
        std::vector<int> component_list;

        for (int c = 0; c < 10; c ++) {
            if (coin_toss()) {
                component_list.push_back(c);
            }
        }

        entity_list.push_back(component_list);
    }

    bench_start("Pathological", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_pathological(n_iter, entity_list), "(view)");
    bench_report("EnTT",    bench_iter_pathological(n_iter, entity_list), "(group, owning)");
    #endif
    #ifdef REFLECS
    bench_report("Reflecs", bench_iter_pathological(n_iter, entity_list), "");
    #endif
    bench_stop();
}*/

int main(int argc, char *argv[]) {

    bench_create(N_ENTITIES);

    bench_add(N_ENTITIES);

    bench_iterate(N_ENTITIES, N_ITERATIONS);

    //bench_pathological(N_ENTITIES, N_ITERATIONS);

    printf("\n");
}
