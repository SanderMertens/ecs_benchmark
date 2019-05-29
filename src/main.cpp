#include <ecs_benchmark.h>

#define N_ENTITIES (1000000)
#define N_ITERATIONS_CREATE (25)
#define N_ITERATIONS_ADD (25)
#define N_ITERATIONS (1000)

#define FLECS
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

struct Health {
    float value;
};

struct Attack {
    float value;
};

struct Defense {
    float value;
};

struct Stamina {
    float value;
};

struct Strength {
    float value;
};

struct Agility {
    float value;
};

struct Intelligence {
    float value;
};


#ifdef ENTT
#include "entt.hpp"
#endif
#ifdef FLECS
#include "flecs.hpp"
#endif

void bench_heading(const char *title) {
    printf("\n### %s\n", title);
}

void bench_start(const char *title, unsigned int n) {
    printf("\n---\n");
    printf("%s (n = %d):\n\n", title, n);
    printf("| Framework | Measurement                        |\n");
    printf("|-----------|------------------------------------|\n");
}

void bench_report(const char *framework, double benchmark, const char *sub) {
    printf("|%10s |  %f %s %*s|\n", framework, benchmark, sub, (int)(24 - strlen(sub)), "");
}

#define bench_report_n(framework, benchmark, sub, iter)\
    result = 0;\
    for (int i = 0; i < iter; i ++) {\
        double t = benchmark;\
        if (!result || result > t) {\
            result = t;\
        }\
    }\
    bench_report(framework, result, sub);

void bench_stop() {
    printf("\n");
}

/* Creation tests */
void bench_create(int n) {
    double result;

    bench_heading("Creating entities\n");

    bench_start("Entity creation, empty", n);
    #ifdef ENTT    
    bench_report_n("EnTT",    bench_create_empty_entt(n), "", N_ITERATIONS_CREATE);
    #endif
    #ifdef FLECS 
    bench_report_n("  Flecs", bench_create_empty_flecs(n), "", N_ITERATIONS_CREATE);
    #endif
    #ifdef ENTT    
    bench_report_n("EnTT",    bench_create_empty_entt_batch(n), "(batching)", N_ITERATIONS_CREATE);
    #endif
    #ifdef FLECS 
    bench_report_n("  Flecs", bench_create_empty_flecs_batch(n), "(batching)", N_ITERATIONS_CREATE);
    #endif
    bench_stop();

    bench_start("Entity creation, 1 component", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_create_1component_entt(n), "", N_ITERATIONS_CREATE);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_create_1component_flecs_batch(n), "(batching)", N_ITERATIONS_CREATE);
    #endif
    bench_stop();

    bench_start("Entity creation, 2 component", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_create_2component_entt(n), "", N_ITERATIONS_CREATE);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_create_2component_flecs_batch(n), "(batching, family)", N_ITERATIONS_CREATE);
    #endif
    bench_stop();

    bench_start("Entity creation, 3 component", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_create_3component_entt(n), "", N_ITERATIONS_CREATE);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_create_3component_flecs_batch(n), "(batching, family)", N_ITERATIONS_CREATE);
    #endif
    bench_stop();

    bench_start("Entity deletion, 1 component", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_delete_1component_entt(n), "", N_ITERATIONS_CREATE);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_delete_1component_flecs(n), "", N_ITERATIONS_CREATE);
    #endif
    bench_stop();
}

/* Add/Remove tests */
void bench_add(int n) {
    double result;

    bench_heading("Adding & removing components\n");

    bench_start("Add one component", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_add_one_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_add_one_flecs(n), "", N_ITERATIONS_ADD);
    bench_report_n("  Flecs", bench_add_one_flecs_new(n), "(new w/component)", N_ITERATIONS_ADD);
    #endif
    bench_stop();

    bench_start("Add two components", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_add_two_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_add_two_flecs(n), "", N_ITERATIONS_ADD);
    bench_report_n("  Flecs", bench_add_two_flecs_family(n), "(add w/family)", N_ITERATIONS_ADD);
    #endif
    bench_stop();

    bench_start("Add three components", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_add_three_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_add_three_flecs(n), "", N_ITERATIONS_ADD);
    bench_report_n("  Flecs", bench_add_three_flecs_family(n), "(add w/family)", N_ITERATIONS_ADD);
    #endif
    bench_stop();

    bench_start("Add four components", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_add_four_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_add_four_flecs(n), "", N_ITERATIONS_ADD);
    bench_report_n("  Flecs", bench_add_four_flecs_family(n), "(add w/family)", N_ITERATIONS_ADD);
    #endif
    bench_stop();

    bench_start("Remove one component", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_remove_one_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_remove_one_flecs(n), "", N_ITERATIONS_ADD);
    #endif
    bench_stop();

    bench_start("Remove two components", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_remove_two_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_remove_two_flecs(n), "", N_ITERATIONS_ADD);
    bench_report_n("  Flecs", bench_remove_two_flecs_family(n), "(remove w/family)", N_ITERATIONS_ADD);
    #endif
    bench_stop();

    bench_start("Remove three components", n);
    #ifdef ENTT
    bench_report_n("EnTT",    bench_remove_three_entt(n), "", N_ITERATIONS_ADD);
    #endif
    #ifdef FLECS
    bench_report_n("  Flecs", bench_remove_three_flecs(n), "", N_ITERATIONS_ADD);
    bench_report_n("  Flecs", bench_remove_three_flecs_family(n), "(remove w/family)", N_ITERATIONS_ADD);
    #endif
    bench_stop();
}

/* Iteration tests */
void bench_iterate(int n, int n_iter) {

    bench_heading("Iterating over entities with systems\n");

    /*bench_start("Iterate, small component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_small_entt_view(n, n_iter), "(view)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_small_flecs(n, n_iter), "");
    #endif
    bench_stop();*/

    bench_start("Iterate, one component", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_one_entt_view(n, n_iter), "(view)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_one_flecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, two components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_entt_view(n, n_iter), "(view)");
    bench_report("EnTT",    bench_iter_two_entt_group(n, n_iter), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_two_flecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, two components, eight types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_eight_types_entt_view(n, n_iter, true), "(view)");
    bench_report("EnTT",    bench_iter_two_eight_types_entt_group(n, n_iter, true), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_two_eight_types_flecs(n, n_iter, true), "");
    #endif
    bench_stop();

    bench_start("Iterate, two components, eight types, four matching", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_eight_types_entt_view(n, n_iter, false), "(view)");
    bench_report("EnTT",    bench_iter_two_eight_types_entt_group(n, n_iter, false), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_two_eight_types_flecs(n, n_iter, false), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_entt_view(n, n_iter), "(view)");
    bench_report("EnTT",    bench_iter_three_entt_group(n, n_iter), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_three_flecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components, two types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_two_types_entt_view(n, n_iter), "(view)");
    bench_report("EnTT",    bench_iter_three_two_types_entt_group(n, n_iter), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_three_two_types_flecs(n, n_iter), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components, eight types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_eight_types_entt_view(n, n_iter, true), "(view)");
    bench_report("EnTT",    bench_iter_three_eight_types_entt_group(n, n_iter, true), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_three_eight_types_flecs(n, n_iter, true), "");
    #endif
    bench_stop();

    bench_start("Iterate, three components, eight types, four matching", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_eight_types_entt_view(n, n_iter, false), "(view)");
    bench_report("EnTT",    bench_iter_three_eight_types_entt_group(n, n_iter, false), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_three_eight_types_flecs(n, n_iter, false), "");
    #endif
    bench_stop();

    bench_start("Iterate, four components, eight types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_four_eight_types_entt_view(n, n_iter, true), "(view)");
    bench_report("EnTT",    bench_iter_four_eight_types_entt_group(n, n_iter, true), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_four_eight_types_flecs(n, n_iter, true), "");
    #endif
    bench_stop();

    bench_start("Iterate, four components, eight types, four matching", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_four_eight_types_entt_view(n, n_iter, false), "(view)");
    bench_report("EnTT",    bench_iter_four_eight_types_entt_group(n, n_iter, false), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_four_eight_types_flecs(n, n_iter, false), "");
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
void bench_pathological(int n, int n_iter) {

    bench_heading("Ten randomized components\n");

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

    bench_start("Pathological, one component, 1024 types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_one_pathological_entt(n_iter, entity_list), "(view)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_one_pathological_flecs(n_iter, entity_list), "");
    #endif
    bench_stop();

    bench_start("Pathological, two components, 1024 types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_two_pathological_entt_view(n_iter, entity_list), "(view)");
    bench_report("EnTT",    bench_iter_two_pathological_entt_group(n_iter, entity_list), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_two_pathological_flecs(n_iter, entity_list), "");
    #endif
    bench_stop();

    bench_start("Pathological, three components, 1024 types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_three_pathological_entt_view(n_iter, entity_list), "(view)");
    bench_report("EnTT",    bench_iter_three_pathological_entt_group(n_iter, entity_list), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_three_pathological_flecs(n_iter, entity_list), "");
    #endif
    bench_stop();

    bench_start("Pathological, four components, 1024 types", n);
    #ifdef ENTT
    bench_report("EnTT",    bench_iter_four_pathological_entt_view(n_iter, entity_list), "(view)");
    bench_report("EnTT",    bench_iter_four_pathological_entt_group(n_iter, entity_list), "(group, owning)");
    #endif
    #ifdef FLECS
    bench_report("  Flecs", bench_iter_four_pathological_flecs(n_iter, entity_list), "");
    #endif
    bench_stop();
}

int main(int argc, char *argv[]) {

    bench_create(N_ENTITIES);

    bench_add(N_ENTITIES);

    bench_iterate(N_ENTITIES, N_ITERATIONS);

    bench_pathological(N_ENTITIES, N_ITERATIONS);

    printf("\n");
}
