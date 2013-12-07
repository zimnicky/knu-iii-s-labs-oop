#include "line.h"
#include <cmath>

Line::Line()
{
}


Line::Line(const Point &p1, const Point &p2)
{
   this->p1 = p1;
   this->p2 = p2;
}

Point Line::firstPoint() const
{
    return p1;
}

Point Line::secondPoint() const
{
    return p2;
}

void Line::getCoefs(double &a, double &b, double &c) const
{
    a = p1.y() - p2.y();
    b =  p2.x() - p1.x();
    c = -A()*p1.x() - B()*p1.y();

    //normalize
    double z = sqrt(a*a + b*b);
    a /= z;
    b /= z;
    c /= z;
}

double Line::A() const
{
    double a,b,c;
    getCoefs(a,b,c);
    return a;
}

double Line::B() const
{
    double a,b,c;
    getCoefs(a,b,c);
    return b;
}

double Line::C() const
{
    double a,b,c;
    getCoefs(a,b,c);
    return c;
}

double Line::det(double m11, double m12, double m21, double m22)
{
    return m11*m22 - m12*m21;
}

bool Line::intersect(const Line &b, Point &point) const
{
    double a1, b1, c1, a2, b2, c2;

    getCoefs(a1, b1, c1);
    b.getCoefs(a2, b2, c2);

    // using Cramer's rule
    double den = det(a1, b1, a2, b2);  // denominator

    if (std::abs(den) < 1e-9)
        return false;

    point.setX(-det (c1, b1, c2, b2) / den);
    point.setY(-det (a1, c1, a2, c2) / den);

    return true;
}

bool Line::isParallel(const Line &b) const
{
    Point t;
    return !intersect(b, t);
}
