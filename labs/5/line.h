#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
protected:
    Point p1;
    Point p2;

    void getCoefs(double &a, double &b, double &c) const;
    static double det(double m11, double m12, double m21, double m22); // determinant of matrix 2x2
public:
    Line();
    Line(const Point &p1, const Point &p2);

    double A() const;
    double B() const;
    double C() const;

    Point firstPoint() const;
    Point secondPoint() const;

    bool intersect(const Line &b, Point &point) const;
    bool isParallel(const Line &b) const;
};

#endif // LINE_H
