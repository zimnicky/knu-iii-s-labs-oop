#include <iostream>
#include "montecarlo.h"

using namespace std;

int main()
{
    float x0 = 0.5;
    float x1 = 1;
    unsigned int count;

    cin >> count;
    cout << integrate(
                    [](float x, float y){return x*x + y*y;},
                    x0, x1,
                    [](float){return 0.f;},
                    [](float x){return 2*x - 1;},
                    count
                ) << endl;

    return 0;
}

