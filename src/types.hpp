#pragma once

#include <limits>

#ifdef DOUBLE_AS_FLOAT
typedef double floating;
#else
typedef float floating;
#endif

#define MAX_FLOATING (std::numeric_limits<floating>::max())
