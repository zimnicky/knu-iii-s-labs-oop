#include <iostream>
#include "parallelogram.h"

using namespace std;

int main()
{
    Point a,b,c;

    double x, y;

    cin >> x >> y;
    a = Point(x,y);
    cin >> x >> y;
    b = Point(x,y);
    cin >> x >> y;
    c = Point(x,y);

    cout << "--------\n";
    Parallelogram p(a,b,c);
    for (int i = 0; i < 4;i++)
        cout << p.getPoint(i).x() << " " << p.getPoint(i).y() << endl;
    cout << "P:" << p.perimeter() << endl;
    cout << "S:" << p.area() << endl;

    return 0;
}

