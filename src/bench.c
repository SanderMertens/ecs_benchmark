#include "bench.h"

bool flip_coin(void) {
    int r = rand();
    return r >= ((float)RAND_MAX / 2.0f);
}

const char* spacing(float v) {
    if (v > 1000000) {
        return "";
    } else if (v > 100000) {
        return " ";
    } else if (v > 10000) {
        return "  ";
    } else if (v > 1000) {
        return "   ";
    } else if (v > 100) {
        return "    ";
    } else if (v > 10) {
        return "     ";
    } else {
        return "      ";
    }
}

char* bench_vasprintf(
    const char *fmt,
    va_list args)
{
    ecs_size_t size = 0;
    char *result  = NULL;
    va_list tmpa;

    va_copy(tmpa, args);

    size = vsnprintf(result, 0, fmt, tmpa);

    va_end(tmpa);

    if ((int32_t)size < 0) { 
        return NULL; 
    }

    result = (char *) ecs_os_malloc(size + 1);

    if (!result) { 
        return NULL; 
    }

    ecs_os_vsnprintf(result, size + 1, fmt, args);

    return result;
}

char* bench_asprintf(
    const char *fmt,
    ...)
{
    va_list args;
    va_start(args, fmt);
    char *result = bench_vasprintf(fmt, args);
    va_end(args);
    return result;
}

#ifdef PRETTY_TIME_FMT
void header_print(void) {
    printf("| Benchmark                             | Measurement  |\n");
    printf("|---------------------------------------|--------------|\n");
}

void bench_print(const char *label, float v) {
    printf("| %s %*s | %s%.2f%s%s%s |\n", 
        label, (int)(36 - strlen(label)), "", COLOR(v), NUM(v), SYM(v), spacing(NUM(v)), ECS_NORMAL);
}
#else
void header_print(void) {
    printf("Benchmark                              Measurement\n");
}

void bench_print(const char *label, float v) {
    printf("%s %*s  %s%.2f%s%s\n", 
        label, (int)(36 - strlen(label)), "", COLOR(v), v * BILLION, spacing(v * BILLION), ECS_NORMAL);
}
#endif

bench_t bench_begin(const char *lbl, int32_t count) {
    bench_t b = {0};
    b.lbl = lbl;
    b.interval = MEASURE_INTERVAL;
    b.intervals = 0;
    b.count = count;
    return b;
}

double time_measure(
    ecs_time_t *start)
{
    ecs_time_t stop;
    ecs_os_get_time(&stop);
    return ecs_time_to_double(ecs_time_sub(stop, *start));
}

bool bench_next(bench_t *b) {
    if (!--b->interval) {
        b->intervals ++;
        if (b->intervals > WARMUP_INTERVALS) {
            double dt = time_measure(&b->t);
            if (dt > MEASURE_TIME) {
                b->dt = dt;
                return false;
            }
        } else if (b->intervals == WARMUP_INTERVALS) {
            ecs_os_get_time(&b->t);
        }
        b->interval = MEASURE_INTERVAL;
    }
    return true;
}

void bench_end(bench_t *b) {
    bench_print(b->lbl, b->dt / ((b->intervals - WARMUP_INTERVALS) * MEASURE_INTERVAL * b->count));
}
