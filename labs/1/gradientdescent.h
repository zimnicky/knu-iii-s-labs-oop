#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <vector>
#include <cmath>

using namespace std;

typedef unsigned int uint;

const double step = 1e-4; // fixed step between iterations
const double stoppingE = 1e-7; // constatant for stopping algorithm (accuracy)
const int max_iterations = 100000; // maximum number of iterations

// = a1x1 + a2x2 + .. + anxn + b1x1^2 + b2x2^2 + .. + bnxn^2
// a, b, x must have same dimensions
double func(const vector<double> &a, const vector<double> &b, const vector<double> &x);

// gradient of function
vector<double> gradient(const vector<double> &a, const vector<double> &b, const vector<double> &x);

// length of gradient
double vectorNorm(const vector<double> &a, const vector<double> &b, const vector<double> &x);

// search maximum of func
vector<double> gradientDescent(const vector<double> &a, const vector<double> &b, const vector<double> &start_point);

#endif // GRADIENTDESCENT_H
