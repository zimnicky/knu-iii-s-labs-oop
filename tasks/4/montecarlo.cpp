#include "montecarlo.h"
#include <cstdlib>
#include <ctime>

/*
 * return random value in [a,b]
 */
float floatRand(float a, float b)
{
    return a + ((float)rand()/(float)RAND_MAX)*(b - a);
}

float integrate(IntegralFunc f, float x0, float x1, float y0, float y1, unsigned int count)
{
    float sum = 0;
    srand(time(0));

    for (unsigned int i = 0; i < count; i++)
    {
        float x = floatRand(x0, x1);
        float y = floatRand(y0, y1);
        sum += f(x, y);
    }

    sum /= count;

    return (x1 - x0)*(y1 - y0) * sum;
}
