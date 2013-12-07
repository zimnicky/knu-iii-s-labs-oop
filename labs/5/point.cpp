#include "point.h"

Point::Point(double x, double y)
{
    this->_x = x;
    this->_y = y;
}


double Point::x() const
{
    return _x;
}

double Point::y() const
{
    return _y;
}

void Point::setX(double val)
{
    _x = val;
}

void Point::setY(double val)
{
    _y = val;
}


Point Point::operator+(const Point &b) const
{
    return Point(_x+b.x(), _y+b.y());
}

Point Point::operator-(const Point &b) const
{
    return Point(_x-b.x(), _y-b.y());
}

Point Point::operator*(double a) const
{
    return Point(_x*a, _y*a);
}

bool Point::operator==(const Point& b) const
{
    return _x == b.x() && _y == b.y();
}

bool Point::operator!=(const Point& b) const
{
    return _x != b.x() || _y != b.y();
}
