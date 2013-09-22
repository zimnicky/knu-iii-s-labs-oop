#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H

#include <vector>
#include <cmath>
#include "matrix.h"

using namespace std;

class GradientDescent
{
private:
    enum class EType{Maximun, Minimum};
    double step = 1e-4; // fixed step between iterations
    double stoppingE = 1e-9; // constatant for stopping algorithm (accuracy)
    int max_iterations = 100000; // maximum number of iterations

    vector<double> a, b; // coefficients of function

    // gradient of function
    virtual vector<double> gradient(const vector<double> &x);

    // length of vector
    double vectorNorm(const vector<double> &x);

    // returns extremum of function(min or max)
    vector<double> extremum(const vector<double> &start_point, EType type);

    // returns extremum with constraints
    vector<double> extremum(const vector<double> &start_point, const vector<vector<double>> &c,
                             const vector<double> &d, EType type);

    // returns matrix with constraints with equality
    Matrix getActiveConstraints(const vector<vector<double>> &c,
                                const vector<double> &d, const vector<double> &x);

public:
    GradientDescent();

    void setStep(double step){ this->step = step;} // sets fixed step between iterations
    void setAccuracy(double accuracy){stoppingE = accuracy;}
    void setFunctionCoefs(const vector<double> &a, const vector<double> &b); // sets coefficients of function


    vector<double> maximize(const vector<double> &start_point);
    vector<double> minimize(const vector<double> &start_point);

    //cij & di -- coefficients from the task
    vector<double> maximize(const vector<double> &start_point, const vector<vector<double>> &c,
                            const vector<double> &d);

    vector<double> minimize(const vector<double> &start_point, const vector<vector<double>> &c,
                            const vector<double> &d);

    // returns value of function
    // f(.) = a1x1 + a2x2 + .. + anxn + b1x1^2 + b2x2^2 + .. + bnxn^2
    virtual double getValue(const vector<double> &x);

};

#endif // GRADIENTDESCENT_H
