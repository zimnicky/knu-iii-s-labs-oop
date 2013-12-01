#include <iostream>
#include <fstream>
#include "polygon.h"

using namespace std;

int main()
{
    ifstream in("input.txt");
    Polygon p;
    p.read(in);
    in.close();
    cout << "Min sum: " << p.taskA() << endl;
    cout << "Min max diagonal: " << p.taskB() << endl;
    return 0;
}

