#ifndef MONTECARLO_H
#define MONTECARLO_H

typedef float (*IntegralFunc)(float, float);
typedef float (*DomainFunc)(float);

/*
 * Calculates double integral of function f(x,y) in domains x0-x1, y0-y1, using count random values
 */
float integrate(IntegralFunc f, float x0, float x1, DomainFunc y0, DomainFunc y1, unsigned int count = 1000);

#endif // MONTECARLO_H
