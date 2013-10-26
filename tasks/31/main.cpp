#include <iostream>
#include "task.h"
#include <cmath>

using namespace std;

int main()
{
    double val;
    cin >> val;

    cout << "Standart cos(x):" << cos(val) << endl;
    cout << "My cos(x):" << cos(val, 1e-10) << endl;

    return 0;
}

