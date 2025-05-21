#include "tests.h"

ecs_entity_t* create_ids(
    ecs_world_t *world, int32_t count, ecs_size_t size, bool low, bool sparse, bool fragment) 
{
    if (count) {
        ecs_entity_t *ids = ecs_os_calloc_n(ecs_entity_t, count);
        for (int i = 0; i < count; i ++) {
            if (low) {
                ids[i] = ecs_new_low_id(world);
            } else {
                ids[i] = ecs_new(world);
            }
            if (size) {
                ecs_set(world, ids[i], EcsComponent, {size, 4});
            }
            #if FLECS_VERSION_NUMBER >= 40000
            if (sparse) {
                ecs_add_id(world, ids[i], EcsSparse);
            }
            #endif
            #if FLECS_VERSION_NUMBER > 40005
            if (!fragment) {
                ecs_add_id(world, ids[i], EcsDontFragment);
            }
            #endif
        }
        return ids;
    } else {
        return NULL;
    }
}
