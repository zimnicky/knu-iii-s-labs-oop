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

void showResult(const vector<double> &a, const vector<double> &b, const vector<double> &res)
{
    cout << "Value:" << func(a, b, res) << endl;
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
    vector<double> res;
    ifstream in("input.txt");
    readVector(in, a);
    readVector(in, b);
    readVector(in, x0);
    in.close();

    res = gradientDescent(a, b, x0);

    showResult(a, b ,res);

    return 0;
}

