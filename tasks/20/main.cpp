#include <iostream>
#include "number.h"
#include <string>

using namespace std;

int main()
{
    Number a;
    Number b;

    cin >> a;
    cin >> b;

    cout << "+:" <<  a+b << endl;
    cout << "-:" << a-b << endl;
    cout << "*:" << a*b << endl;
    cout << "/:" << a/b << endl;

    return 0;
}

