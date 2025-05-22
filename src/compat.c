#include "compat.h"

#if FLECS_VERSION_NUMBER < 30200

ecs_entity_t ecs_new_w_table(ecs_world_t *world, ecs_table_t *table) {
    const ecs_entity_t *r = ecs_bulk_init(world, &(ecs_bulk_desc_t) {
        .table = table,
        .count = 1
    });
    return r[0];
}

#endif
