#ifndef TIMER_H
#define TIMER_H

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct timespec timespec;

typedef struct {
    timespec start;
    timespec end;
    uint64_t start_ns;
    uint64_t end_ns;
    int64_t elapsed_time;
} Timer;

/**
 * macro: tm_timespec_to_nanosconds
 * Convert a timespec struct value to nanoseconds
 * @param time_, timespect struct
 */
#define tm_timespec_to_nanosconds(time_) (time_.tv_sec * 1000000000) + time_.tv_nsec

#endif