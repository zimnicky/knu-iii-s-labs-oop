#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>

using namespace std;

class Polygon
{
private:
    struct Point{
        float x, y;
    };
    vector<vector<float>> diagolnals;   // length of each diagonal

    float distance(const Point &a, const Point &b);
public:
    Polygon();
    void read(istream &in);
    float taskA();
    float taskB();
};

#endif // POLYGON_H
