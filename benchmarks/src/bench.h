#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct BenchResult
{
    double min_ns;
    double mean_ns;
    double median_ns;
} BenchResult;

#define BENCHMARK(name, warmup, iterations, code)   \
    do                                              \
    {                                               \
        for (int _w = 0; _w < (warmup); ++_w)       \
        {                                           \
            code;                                   \
        }                                           \
        double _samples[(iterations)];              \
        for (int _i = 0; _i < (iterations); ++_i)   \
        {                                           \
            double _t0 = bench_now_ns();            \
            code;                                   \
            _samples[_i] = bench_now_ns() - _t0;    \
        }                                           \
        bench_report(name, _samples, (iterations)); \
    } while (0)

static inline double bench_now_ns(void)
{
    struct timespec ts;

    if (timespec_get(&ts, TIME_UTC) == TIME_UTC)
    {
        long nanoseconds = ((long)ts.tv_sec * 1000000000LL) + (long)ts.tv_nsec;

        return (double)nanoseconds;
    }

    perror("Failed to obtain high-resolution time.\n");

    return 0.0;
}

static int compare(const void *a, const void *b)
{
    double double_a = *(const double *)a;
    double double_b = *(const double *)b;

    if (double_a < double_b)
        return -1;
    if (double_a > double_b)
        return 1;
    return 0;
}

static inline void bench_report(const char *name, double *samples, int iterations)
{
    qsort(samples, (size_t)iterations, sizeof(double), compare);

    double min = samples[0];

    double sum = 0;
    for (int i = 0; i < iterations; ++i)
    {
        sum += samples[i];
    }

    int middle = iterations / 2;
    double median;

    if (iterations % 2 == 0)
    {
        median = (samples[middle] + samples[middle + 1]) / 2.0;
    }
    else
    {
        median = samples[middle];
    }

    double mean = sum / iterations;

    printf("\tBENCHMARK: %s\n", name);
    printf("Iterations: %d\n", iterations);
    printf("Minimum (ns): %g\n", min);
    printf("Mean    (ns): %g\n", mean);
    printf("Median  (ns): %g\n", median);
}
