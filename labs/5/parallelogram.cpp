#include "parallelogram.h"
#include <algorithm>
#include <cmath>

Parallelogram::Parallelogram(Point a, Point b, Point c)
{
    points[0] = a;
    points[1] = b;
    points[2] = c;
}

Parallelogram::Parallelogram(Line a, Line b, Line c) throw(std::invalid_argument)
{
    Point pa, pb, pc;
    if (a.isParallel(b))
        std::swap(b,c);
    else
        if (!a.isParallel(c))
            throw new std::invalid_argument("Parallelogram must have 2 parallel lines");

    if (a.isParallel(b))
        throw new std::invalid_argument("Parallelogram must have only 2 parallel lines");

    a.intersect(b, pa);
    b.intersect(c, pb);
    c.intersect(c, pc);

    Parallelogram(pa, pb, pc);
}


double Parallelogram::perimeter() const
{
    double sum = 0;

    for (int i = 0; i < 2; i++)
        sum += Edge(points[i], points[i+1]).length();

    return 2*sum;
}

double Parallelogram::area() const
{
    /*  Determinant of matrix:
     *  |0x 0y 1|
     *  |1x 1y 1|
     *  |2x 2y 1|
     *
     */
    double det = points[0].x()*points[1].y() +
            points[0].y()*points[2].x() +
            points[1].x()*points[2].y() -
            points[1].y()*points[2].x() -
            points[0].x()*points[2].y() -
            points[0].y()*points[1].x();

    return abs(det);
}


void Parallelogram::translate(Point vector)
{
    for (int i = 0; i < 3; i++)
        points[i] = points[i] + vector;
}


void Parallelogram::scale(double scope)
{
    for (int i = 0; i < 3; i++)
        points[i] = points[i] * scope;
}

void Parallelogram::rotate(Point point, double angle)
{
    for (int i = 0; i < 3; i++)
    {
        Point t = points[i] - point;
        points[i].setX(t.x()*cos(angle) - t.y()*sin(angle));
        points[i].setX(t.x()*cos(angle) + t.y()*sin(angle));
        points[i] = points[i] + point;
    }
}

Point Parallelogram::getPoint(unsigned int num) throw (std::invalid_argument)
{
    if (num > 3)
        throw new std::invalid_argument("num must be from 0 to 3");
    if (num == 3)
    {
        Point t(points[2].x() + (points[0].x() - points[1].x()), points[0].y());
        return t;
    }

    return points[num];
}
