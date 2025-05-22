#include "bench.h"
#include "compat.h"

ecs_entity_t* create_ids(
    ecs_world_t *world, 
    int32_t count, 
    ecs_size_t size, 
    bool low, 
    bool sparse, 
    bool fragment);

void has_tests();

void get_tests();

void set_ensure_tests();

void ref_tests();

void add_remove_tests();

void commands_tests();

void create_delete_tests();

void parenting_names_tests();

void observers_tests();

void query_tests();

void world_tests();
