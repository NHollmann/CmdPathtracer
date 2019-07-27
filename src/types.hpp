#pragma once

#include <limits>

#ifdef DOUBLE_AS_FLOAT
typedef double floating;
#else
typedef float floating;
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_FLOATING (std::numeric_limits<floating>::max())

#ifdef WIN32
inline double drand48()
{
    return (rand() / (RAND_MAX + 1.0));
}
#endif
