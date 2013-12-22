#include "cubicspline.h"

CubicSpline::CubicSpline()
{
}

CubicSpline::CubicSpline(vector<double> &x, vector<double> &f)
{
    build(x,f);
}

void CubicSpline::build(vector<double> &x, vector<double> &f)
{
    segments.resize(x.size());

    // initializing segments using known data
    for (unsigned int i = 0 ; i < x.size(); i++)
    {
        segments[i].x = x[i];
        segments[i].a = f[i];
    }
    segments[0].c = 0;

    // using Thomas algorithm to find segments[i].c

    // solution Xi = coefA[i] * X(i+1) + coefB[i]
    vector<double> coefA(x.size() - 1, 0.f);
    vector<double> coefB(x.size() - 1, 0.f);

    double A, B, C, F;   // system: Ai*X(i-1) + Ci*Xi + Bi*X(i+1) = Fi
    double tmp;

    for (unsigned int i = 1; i < x.size() - 1; i++)
    {
        A = x[i] - x[i-1];
        B = x[i+1] - x[i];
        C = 2 * (A + B);
        F = 6 * ( (f[i+1] - f[i])/B  - (f[i] - f[i-1])/A );

        tmp = A * coefA[i-1] + C;

        coefA[i] = -B/tmp;
        coefB[i] = (F - A * coefB[i-1]) / tmp;
    }

    segments[x.size() - 1].c = (F - A * coefB[x.size() - 2]) / (A * coefA[x.size() - 2] + C);

    for (unsigned int i = x.size() - 2; i > 0; i--)
        segments[i].c = coefA[i] * segments[i+1].c + coefB[i];



    // getting segments[i].b & segments[i].d
    for (unsigned int i = x.size() - 1; i > 0; i--)
    {
        double t = x[i] - x[i-1];
        segments[i].b = t * (2 * segments[i].c + segments[i-1].c)/6 + (f[i] - f[i-1])/t;
        segments[i].d = (segments[i].c - segments[i - 1].c)/t;
    }

}


double CubicSpline::f(double x) const
{
    unsigned int curr;
    for (curr = 0; curr < segments.size()-1 && x > segments[curr].x; curr++)
    {}

    // Si(xi) = ai + bi * (x - xi) + ci/2 * (x - xi)^2 + di/2 * (x - xi)^3
    double dx = x - segments[curr].x;
    return segments[curr].a + (segments[curr].b + (segments[curr].c/2 + (segments[curr].d/6)*dx)*dx)*dx;
}
