#ifndef CUBICSPLINE_H
#define CUBICSPLINE_H

#include <vector>

using namespace std;

class CubicSpline
{
private:
    // Params of polynome on segment
    struct Segment
    {
        double a, b, c, d, x;   // Si(xi) = ai + bi * (x - xi) + ci/2 * (x - xi)^2 + di/2 * (x - xi)^3
    };

    vector<Segment> segments;   // a = x0 < ... < xn = b
public:
    CubicSpline();
    CubicSpline(vector<double> &x, vector<double> &f);

    void build(vector<double> &x, vector<double> &f);
    double f(double x) const;

};

#endif // CUBICSPLINE_H
