#include "compat.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
// accurate measurement in release mode
#define WARMUP_INTERVALS (5)
#define MEASURE_INTERVAL (50)
#define MEASURE_TIME (0.5)
#else
// run to verify tests don't assert in debug mode
#define WARMUP_INTERVALS (1)
#define MEASURE_INTERVAL (1)
#define MEASURE_TIME (0.001)
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
