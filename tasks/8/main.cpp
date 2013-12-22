#include <iostream>
#include <fstream>
#include "cubicspline.h"

using namespace std;

int main()
{
    vector<double> x = {-0.5, 1.5, 2.0, 3.5, 6.0, 9.0};
    vector<double> f = {2.5, 6, -3.5, -7, -10 , 2};

    CubicSpline spline(x, f);

    cout << "f(2.5) = " << spline.f(2.5) << endl;

    return 0;
}

