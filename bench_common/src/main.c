#include <bench_common.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

bench_time_t bench_time_sub(
    bench_time_t t1, 
    bench_time_t t2) 
{
    bench_time_t result;
    if (t1.tv_nsec >= t2.tv_nsec) {
        result.tv_nsec = t1.tv_nsec - t2.tv_nsec;
        result.tv_sec = t1.tv_sec - t2.tv_sec;
    } else {
        result.tv_nsec = t1.tv_nsec - t2.tv_nsec + 1000000000;
        result.tv_sec = t1.tv_sec - t2.tv_sec - 1;
    }
    return result;
}

double bench_time_toDouble(
    bench_time_t t) 
{
    double result;
    result = (double)t.tv_sec;
    result += (double)t.tv_nsec / (double)1000000000;
    return result;
}

void bench_time_get(
    bench_time_t* time) 
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    time->tv_sec = mts.tv_sec;
    time->tv_nsec = mts.tv_nsec;
#elif _WIN32
    timespec_get(time, TIME_UTC);
#else
    clock_gettime(CLOCK_REALTIME, time);
#endif
}

double bench_time_measure(
    bench_time_t *start)
{
    struct timespec stop, temp;
    bench_time_get(&stop);
    temp = stop;
    stop = bench_time_sub(stop, *start);
    *start = temp;
    return bench_time_toDouble(stop);
}
