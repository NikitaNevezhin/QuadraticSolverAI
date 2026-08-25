#include "FloatTools.h"
#include <math.h>
#include <stdbool.h>

#define ACCURACY 10e-6


bool FloatEqual(const double x, const double y)
{
    return fabs(x - y) < ACCURACY;
}


bool IsGreater(const double x1, const double x2)
{
    return (x1 - x2) > ACCURACY;
}
