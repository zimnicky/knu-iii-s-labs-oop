#ifndef EDGE_H
#define EDGE_H

#include "line.h"

class Edge : public Line
{
public:
    Edge():Line(){}
    Edge(const Point &a, const Point &b):Line(a, b){}

    double length();
};

#endif // EDGE_H
