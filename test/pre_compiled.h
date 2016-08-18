#ifndef __PRE_COMPILED_H__
#define __PRE_COMPILED_H__

#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

#include <cstdio>
#include <cstring>

#include "Clock.hpp"

#define PRINT_TIME_COST(op) \
        printf(#op " cost\t= %lf seconds\n", (CClock::GetMicroTimeStampNow() - begin)/(1000.0*1000.0))

#endif // __PRE_COMPILED_H__
