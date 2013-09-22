#include <iostream>
#include <fstream>
#include "gradientdescent.h"

using namespace std;

void readVector(istream &in, vector<double> &a)
{
    int n;
    in >> n;
    a.resize(n);
    for (int i = 0; i < n; i++)
        in >> a[i];
}

void readDoubleVector(istream &in, vector<vector<double>> &a)
{
    int n, k;
    in >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        a[i].resize(k);
        for (int j = 0; j < k; j++)
            in >> a[i][j];
    }
}

void showResult(GradientDescent &g, const vector<double> &res)
{
    cout << "Value:" << g.getValue(res) << endl;
    cout << "Point: \n(" << res[0];
    for (uint i = 1; i < res.size(); i++)
        cout << ", " << res[i];
    cout << ")" << endl;
}

int main()
{
    vector<double> x0; // start point
    vector<double> a; // a1..an coefs
    vector<double> b; //b1..bn coefs
    vector<vector<double>> c; // c11..akn coefs
    vector<double> d; //d1..dk coefs

    vector<double> res;
    ifstream in("input.txt");
    readVector(in, a);
    readVector(in, b);
    readVector(in, x0);
    readDoubleVector(in, c);
    readVector(in, d);
    in.close();

    GradientDescent g;
    g.setFunctionCoefs(a, b);
    res = g.maximize(x0);

    showResult(g, res);

    cout << "with constraints:" << endl;

    res = g.maximize(x0,c,d);

    showResult(g, res);

    return 0;
}

