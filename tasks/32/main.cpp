#include <iostream>
#include <string>
#include "task.h"

using namespace std;

int main()
{
    string a, b;

    getline(cin, a, '\n');
    getline(cin, b, '\n');

    cout << "Result:" << maxCommon(a, b) << endl;

    return 0;
}

