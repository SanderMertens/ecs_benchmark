#include "tests.h"

void baseline(void) {
    bench_t b = bench_begin("baseline", 1);
    do {
    } while (bench_next(&b));
    bench_end(&b);
}

int main(int argc, char *argv[]) {
    printf("Flecs version detected: %d\n", FLECS_VERSION_NUMBER);
    printf("-----------------------------\n\n");
    ecs_os_set_api_defaults(); // Required for timers to work

    header_print();

    baseline();

    has_tests();

    get_tests();

    add_remove_tests();

    set_ensure_tests();

    ref_tests();

    commands_tests();

    create_delete_tests();

    parenting_names_tests();

    observers_tests();

    query_tests();

    world_tests();

    return 0;
}
