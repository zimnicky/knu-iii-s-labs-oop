#include <iostream>
#include "fstream"
#include "salesman.h"

using namespace std;

int main()
{
    ifstream in("input.txt");
    Salesman s;

    double x, y;
    while (in >> x)
    {
        in >> y;
        s.addCity(Salesman::Point(x,y));
    }

    unsigned int population, iterations;
    double chanceOfMutation;
    double chanceOfCrossing;
    cin >> population >> iterations >> chanceOfCrossing >> chanceOfMutation;

    auto res = s.run(population, iterations, chanceOfCrossing, chanceOfMutation);

    cout << "Result:" << endl;
    for (auto i: res)
        cout << i << " ";

    return 0;
}

