#include <iostream>
#include "task.h"

using namespace std;

double f(int x)
{
    return x*x;
}

int main()
{
    int p,i;
    cin >> p >> i;
    double r = findMin(p, i, &f);
    cout << "min=" << r << endl;
    return 0;
}

