#ifndef COMPAT_H
#define COMPAT_H

#include <flecs.h>

#ifdef FLECS_VERSION_MAJOR
#define FLECS_VERSION_NUMBER (FLECS_VERSION_MAJOR * 10000 + FLECS_VERSION_MINOR * 100 + FLECS_VERSION_PATCH)
#else
#define FLECS_VERSION_NUMBER 30000

#ifdef EcsFilter
#undef FLECS_VERSION_NUMBER
#define FLECS_VERSION_NUMBER 30100
#endif

#ifdef ECS_ENTITY_DECLARE
#undef FLECS_VERSION_NUMBER
#define FLECS_VERSION_NUMBER 30200
#endif

#ifdef ecs_emplace_pair
#undef FLECS_VERSION_NUMBER
#define FLECS_VERSION_NUMBER 30205
#endif

#ifdef ecs_ensure_pair
#undef FLECS_VERSION_NUMBER
#define FLECS_VERSION_NUMBER 30212
#endif

#endif

// v3 compatibility
#if FLECS_VERSION_NUMBER < 40000
    #define ecs_os_vsnprintf(ptr, len, fmt, args) vsnprintf(ptr, ECS_CAST(size_t, len), fmt, args)

    #undef ecs_new
    #define ecs_new(world) ecs_new_id(world)

    typedef enum ecs_query_cache_kind_t {
        EcsQueryCacheDefault,
        EcsQueryCacheAuto,
    } ecs_query_cache_kind_t;

    #define query_terms filter.terms
    #define observer_terms filter.terms
    #define term_trav src.trav
    #define term_trav_flags src.flags
    #define make_inheritable(world, component)
    #define query_get_count(query) ecs_query_entity_count(query)

    #define ecs_field_w_size(it, size, field) ecs_field_w_size(it, size, field + 1)

    #if FLECS_VERSION_NUMBER < 30212
        #define ecs_ensure_id ecs_get_mut_id
    #endif

    #if FLECS_VERSION_NUMBER < 30200
        ecs_entity_t ecs_new_w_table(ecs_world_t *world, ecs_table_t *table);

        #define ecs_get_parent(world, entity) ecs_get_target(world, entity, EcsChildOf, 0)
    #endif
#else
    #define query_terms terms
    #define observer_terms query.terms
    #define term_trav trav
    #define term_trav_flags src.id
    #define make_inheritable(world, component) ecs_add_pair(world, component, EcsOnInstantiate, EcsInherit)
    #define query_get_count(query) ecs_query_count(query).entities

    #define ecs_filter_t ecs_query_t
    #define ecs_filter_desc_t ecs_query_desc_t
    #define ecs_filter_init ecs_query_init
    #define ecs_filter_fini ecs_query_fini
    #define ecs_filter_iter ecs_query_iter
    #define ecs_filter_next ecs_query_next
    #define ecs_filter ecs_query

    #define ecs_rule_t ecs_query_t
    #define ecs_rule_desc_t ecs_query_desc_t
    #define ecs_rule_init ecs_query_init
    #define ecs_rule_fini ecs_query_fini
    #define ecs_rule_iter ecs_query_iter
    #define ecs_rule_next ecs_query_next
    #define ecs_rule ecs_query
#endif

#endif
