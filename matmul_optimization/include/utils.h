#ifndef UTILS_H
#define UTILS_H

#include <sys/time.h>

inline double get_time() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec + 1e-6 * tv.tv_usec;
}

#endif
