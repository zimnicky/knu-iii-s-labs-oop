#include <iostream>
#include "montecarlo.h"

using namespace std;

int main()
{
    float x0 = 0.5;
    float x1 = 1;
    float y0 = 0;
    float y1 = 2*x1 - 1;
    unsigned int count;

    cin >> count;
    cout << integrate(
                    [](float x, float y){return x*x + y*y;},
                    x0, x1, y0, y1,
                    count
                ) << endl;

    return 0;
}

