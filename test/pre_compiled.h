#ifndef __PRE_COMPILED_H__
#define __PRE_COMPILED_H__

#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

#include <cstdio>
#include <cstring>

#include <unistd.h>

#include "Clock.hpp"

#define PRINT_TIME_COST(op) \
        do { \
        double diff = (CClock::GetMicroTimeStampNow() - begin) / (1000.0 * 1000.0); \
        printf(#op " cost\t= %lf seconds\n", diff); \
        } while (0)

#endif // __PRE_COMPILED_H__
