#include "gradientdescent.h"

GradientDescent::GradientDescent()
{
    step = 1e-4;
    stoppingE = 1e-9;
    max_iterations = 100000;
}

void GradientDescent::setFunctionCoefs(const vector<double> &a, const vector<double> &b)
{
    this->a = a;
    this->b = b;
}

// = a1x1 + a2x2 + .. + anxn + b1x1^2 + b2x2^2 + .. + bnxn^2
double GradientDescent::getValue(const vector<double> &x)
{
    double res = 0;

    for (uint i = 0; i < a.size(); i++)
        res += a[i]*x[i] + b[i]*x[i]*x[i];

    return res;
}

// gradient of function
vector<double> GradientDescent::gradient(const vector<double> &x)
{
    vector<double> res;
    res.resize(a.size());

    for (uint i = 0; i < a.size(); i++)
        res[i] = a[i] + 2*b[i]*x[i]; // df/dxi

    return res;
}

// length of vector
double GradientDescent::vectorNorm(const vector<double> &x)
{
    double res = 0;
    for (uint i = 0; i < x.size(); i++)
        res += x[i]*x[i];

    return sqrt(res);
}

Matrix GradientDescent::getActiveConstraints(const vector<vector<double>> &c,
                            const vector<double> &d, const vector<double> &x)
{
    vector<double> tmp;
    Matrix res;
    for (uint i = 0; i < c.size(); i++)
    {
        double sum = 0;
        tmp.resize(c[i].size());

        for (uint j = 0; j < c[i].size(); j++) // calculating ci1*x1 + .. + cin*xn
        {
            sum += c[i][j] * x[j];
            tmp[j] = c[i][j];
        }

        if (abs(sum - d[i]) < step) // sum & di are equal
            res.addRow(tmp);
    }
    return res;
}

// search maximum or minimum of func
vector<double> GradientDescent::extremum(const vector<double> &start_point, EType type)
{
    vector<double> gr; // gradient
    vector<double> res = start_point;
    bool found = false;

    int iterations = 0;

    while (!found)
    {
        gr = gradient(res);
        for (uint i = 0; i < res.size(); i++) // go to the direction of gradient(antigradient if miminization)
            if (type == EType::Maximun)
                res[i] += step*gr[i];
            else
                res[i] -= step*gr[i];

        found = vectorNorm(gr) < stoppingE || ++iterations > max_iterations;
    }

    return res;
}


vector<double> GradientDescent::extremum(const vector<double> &start_point, const vector<vector<double>> &c,
                         const vector<double> &d, EType type)
{
    vector<double> gr; // gradient
    vector<double> res = start_point;
    Matrix mat; // matrix of active constraints
    bool found = false;

    int iterations = 0;

    while (!found)
    {
        gr = gradient(res);

        mat = getActiveConstraints(c, d, res); // constraints, where sum = di

        if (mat.size().first != 0) // there are some active constraints
        {
            //project gradient onto this area
            mat = mat.transpose() * (mat * mat.transpose()).inverse() * mat;
            mat = Matrix::E(mat.size().first) - mat;

            mat = Matrix(gr) * mat;
        }
        else
            mat = gr; // use gradient

        for (uint i = 0; i < res.size(); i++) // go to the direction of projection of gradient(antigradient if miminization)
            if (type == EType::Maximun)
                res[i] += step*mat.at(0, i);
            else
                res[i] -= step*mat.at(0, i);

        found = vectorNorm(gr) < stoppingE || ++iterations > max_iterations;
    }

    return res;

}

vector<double> GradientDescent::maximize(const vector<double> &start_point)
{
    return extremum(start_point, EType::Maximun);
}


vector<double> GradientDescent::minimize(const vector<double> &start_point)
{
    return extremum(start_point, EType::Minimum);
}


vector<double> GradientDescent::maximize(const vector<double> &start_point, const vector<vector<double>> &c,
                                         const vector<double> &d)
{
    return extremum(start_point, c, d, EType::Maximun);
}


vector<double> GradientDescent::minimize(const vector<double> &start_point, const vector<vector<double>> &c,
                                         const vector<double> &d)
{
    return extremum(start_point, c, d, EType::Minimum);
}
