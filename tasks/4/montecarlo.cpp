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

float integrate(IntegralFunc f, float x0, float x1, DomainFunc y0, DomainFunc y1, unsigned int count)
{
    float sum = 0;
    srand(time(0));

    float ymin = y0(x0);
    float ymax = y1(x1);

    for (unsigned int i = 0; i < count; i++)
    {
        float x = floatRand(x0, x1);
        float y = floatRand(ymin, ymax);

        if (y >= y0(x) && y < y1(x)) // check if y is correct domain
            sum += f(x, y);
    }

    sum /= count;

    return (x1 - x0)*(ymax - ymin) * sum;
}
