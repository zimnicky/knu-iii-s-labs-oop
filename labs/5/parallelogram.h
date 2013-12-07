#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include <stdexcept>
#include "edge.h"

class Parallelogram
{
private:
    Point points[3];
public:
    Parallelogram(Point a, Point b, Point c);
    Parallelogram(Line a, Line b, Line c) throw (std::invalid_argument);

    double perimeter() const;
    double area() const;

    void translate(Point vector);
    void scale(double scope);
    void rotate(Point point, double angle); // rotates parallelogram around the point

    Point getPoint(unsigned int num) throw (std::invalid_argument);       // returns point of parallelogram with number num
};

#endif // PARALLELOGRAM_H
