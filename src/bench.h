#include <ecs_benchmark.h>
#include <stdio.h>
#include <stdlib.h>

#define FLECS_VERSION_NUMBER (FLECS_VERSION_MAJOR * 10000 + FLECS_VERSION_MINOR * 100 + FLECS_VERSION_PATCH)

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

    #if FLECS_VERSION_NUMBER < 30205
        // ecs_entity_t ecs_new_w_table(ecs_world_t *world, ecs_table_t *table) {
        //     const ecs_entity_t *r = ecs_bulk_init(world, &(ecs_bulk_desc_t) {
        //         .table = table,
        //         .count = 1
        //     });
        //     return r[0];
        // }

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

#ifdef NDEBUG
// accurate measurement in release mode
#define WARMUP_INTERVALS (5)
#define MEASURE_INTERVAL (50)
#define MEASURE_TIME (0.5)
#else
// run to verify tests don't assert in debug mode
#define WARMUP_INTERVALS (1)
#define MEASURE_INTERVAL (1)
#define MEASURE_TIME (0.05)
#endif

// #define PRETTY_TIME_FMT

typedef struct bench_t {
    // Benchmark state
    // The number of times a benchmark is run before taking a measurement.
    uint32_t interval;
    // The total number of intervals that have been run.
    uint32_t intervals;
    // The time at which the benchmark was started.
    ecs_time_t t;
    // The time it took to run the benchmark.
    double dt;

    // Benchmark settings
    // The label of the benchmark.
    const char *lbl;
    // The number of times the operation is run per interval.
    uint32_t count;
} bench_t;

#define THOUSAND (1000.0)
#define MILLION (1000.0 * 1000.0)
#define BILLION (1000.0 * MILLION)

#define FRAC_THOUSAND (1.0 / THOUSAND)
#define FRAC_MILLION (1.0 / MILLION)
#define FRAC_BILLION (1.0 / BILLION)

#define NUM_LEN(v)\
    ((v > THOUSAND) ? 4 : ((v > 100) ? 3 : ((v > 10) ? 2 : 1)))

#define SYM(v)\
    (v < FRAC_MILLION) ? "ns" : ((v < FRAC_THOUSAND) ? "us" : "ms")

#define NUM(v)\
    ((v < FRAC_MILLION) ? (v * BILLION) : ((v < FRAC_THOUSAND) ? (v * MILLION) : (v * THOUSAND)))

#define COLOR(v)\
    ((v < FRAC_MILLION) ? ECS_GREEN : (v < FRAC_THOUSAND) ? ECS_YELLOW : ECS_RED)

bool flip_coin(void);

const char* spacing(float v);

char* bench_vasprintf(
    const char *fmt,
    va_list args);

char* bench_asprintf(
    const char *fmt,
    ...);

void header_print(void);

void bench_print(const char *label, float v);

bench_t bench_begin(const char *lbl, int32_t count);

double time_measure(
    ecs_time_t *start);

bool bench_next(bench_t *b);

void bench_end(bench_t *b);

/* Number of entities created for most benchmarks */
#define ENTITY_COUNT (1000)

/* Number of entities used for query benchmark */
#define QUERY_ENTITY_COUNT (65536)
