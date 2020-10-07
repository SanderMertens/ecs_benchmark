#ifndef BENCH_COMMON_H
#define BENCH_COMMON_H

/* This generated file contains includes for project dependencies */
#include "bench_common/bake_config.h"
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

typedef struct timespec bench_time_t;

BENCH_COMMON_API
void bench_time_get(
    bench_time_t* time);

BENCH_COMMON_API
double bench_time_measure(
    bench_time_t *time);

typedef struct { float value; } Comp_A;
typedef struct { float value; } Comp_B;
typedef struct { float value; } Comp_C;
typedef struct { float value; } Comp_D;
typedef struct { float value; } Comp_E;
typedef struct { float value; } Comp_F;
typedef struct { float value; } Comp_G;
typedef struct { float value; } Comp_H;

typedef struct { float value; } Comp_I;
typedef struct { float value; } Comp_J;
typedef struct { float value; } Comp_K;
typedef struct { float value; } Comp_L;
typedef struct { float value; } Comp_M;
typedef struct { float value; } Comp_N;
typedef struct { float value; } Comp_O;
typedef struct { float value; } Comp_P;

typedef struct { float value; } Comp_Q;

typedef struct bench_t {
    bench_time_t t;
    int32_t count;
    int32_t iter_count;
} bench_t;

typedef struct bench_result_t {
    double sample;
    double avg;
    double min;
    int dummy; // store value to trick optimizer 
} bench_result_t;

#define BENCH_START(b)\
    bench_time_t start; bench_time_get(&start);\
    for (int i = 0; i < b.iter_count; i ++) {\
        __asm__ volatile("" : : : "memory");\

#define BENCH_STOP(b, b_out)\
        __asm__ volatile("" : : : "memory");\
    }\
    b_out->sample = bench_time_measure(&start);

#define BENCH_MIN(min, sample)\
    (((min) < (sample)) ? (min) : (sample))

#define BENCH_NUM(v)\
    (v < 1000) ? v : ((v < 1000000) ? (v / 1000) : (v / 1000000))

#define BENCH_NUM_SYM(v)\
    (v < 1000) ? "ns" : ((v < 1000000) ? "us" : "ms")

#define BENCH_NUM_LEN(v)\
    ((v > 1000) ? 4 : ((v > 100) ? 3 : ((v > 10) ? 2 : 1)))

#define BENCH_HEADER(name)\
    printf("\n%s %*s | Min           | Avg\n", name, 35 - (int)strlen(name), "");\
    printf("-------------------------------------|---------------|--------------\n");

#define BENCH_RUN_EX(fw, bench, n, it_count, repeat)\
    {\
        bench_t b = { .count = n, .iter_count = it_count };\
        bench_result_t r = { .min = INT_MAX };\
        fw##_##bench((bench_t){.count = n}, &(bench_result_t){.min = INT_MAX});\
        for(int i = 0; i < repeat; i ++) {\
            fw##_##bench(b, &r);\
            r.avg += r.sample / (double)repeat;\
            r.min = BENCH_MIN(r.min, r.sample);\
        }\
        double min_n = r.min * (1000000000 / b.count);\
        double avg_n = r.avg * (1000000000 / b.count);\
        printf("%s %*s | %.3f %s %*s | %.3f %s\n",\
            #fw "." #bench,\
            35 - (int)strlen(#fw "." #bench), "",\
            BENCH_NUM(min_n), BENCH_NUM_SYM(min_n),\
            5 - BENCH_NUM_LEN(min_n), "",\
            BENCH_NUM(avg_n), BENCH_NUM_SYM(avg_n));\
    }

#define BENCH_RUN(fw, bench, it_count, repeat)\
    BENCH_RUN_EX(fw, bench, it_count, it_count, repeat)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
