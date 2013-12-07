#ifndef POINT_H
#define POINT_H

class Point
{
    double _x, _y;
public:
    Point():_x(0),_y(0){}
    Point(double x, double y);

    double x() const;
    double y() const;

    void setX(double);
    void setY(double);

    Point operator+(const Point&) const;
    Point operator-(const Point&) const;
    Point operator*(double) const;

    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;


};

#endif // POINT_H
