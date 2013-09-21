#include "gradientdescent.h"

// = a1x1 + a2x2 + .. + anxn + b1x1^2 + b2x2^2 + .. + bnxn^2
double func(const vector<double> &a, const vector<double> &b, const vector<double> &x)
{
    double res = 0;

    for (uint i = 0; i < a.size(); i++)
        res += a[i]*x[i] + b[i]*x[i]*x[i];

    return res;
}

// gradient of function
vector<double> gradient(const vector<double> &a, const vector<double> &b, const vector<double> &x)
{
    vector<double> res;
    res.resize(a.size());

    for (uint i = 0; i < a.size(); i++)
        res[i] = a[i] + 2*b[i]*x[i]; // df/dxi

    return res;
}

// length of vector
double vectorNorm(const vector<double> &x)
{
    double res = 0;
    for (uint i = 0; i < x.size(); i++)
        res += x[i]*x[i];

    return sqrt(res);
}

// search maximum of func
vector<double> gradientDescent(const vector<double> &a, const vector<double> &b, const vector<double> &start_point)
{
    vector<double> gr; // gradient
    vector<double> res = start_point;
    bool found = false;

    int iterations = 0;

    while (!found)
    {
        gr = gradient(a, b, res);
        for (uint i = 0; i < res.size(); i++) // go to the direction of gradient
            res[i] += step*gr[i];

        found = vectorNorm(gr) < stoppingE || ++iterations > max_iterations;
    }

    return res;
}
