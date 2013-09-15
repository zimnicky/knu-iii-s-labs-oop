#include "task.h"


bool Task::Point::between(const Point &a, const Point &b) const
{
    if (a.x == b.x) //vertical segment
    {
        if (x != a.x) return false;
        return (y >= a.y && y <= b.y) || (y >= b.y && y <= a.y);
    }
    else //horizontal segment
    {
        if (y != a.y) return false;
        return (x >= a.x && x <= b.x) || (x >= b.x && x <= a.x);
    }
}

void Task::Rectangle::read(istream &in)
{
    // read two coners of the rectangle
    in >> points[0].x >> points[0].y >> points[2].x >> points[2].y;

    if (points[0].y < points[2].y)
        swap(points[0].y, points[2].y);
    if (points[0].x > points[2].x)
        swap(points[0].x, points[2].x);

    points[1].x = points[2].x;
    points[1].y = points[0].y;
    points[3].x = points[0].x;
    points[3].y = points[2].y;
}

bool Task::Rectangle::isNeighbor(Rectangle *rect) //checks if rects have common points
{
    bool outside = (points[0].x > rect->points[1].x) || (rect->points[0].x > points[1].x) || // x projections
                   (points[3].y > rect->points[0].y) || (rect->points[3].y > points[0].y); // y projections

    bool first_inside = (points[0].x > rect->points[0].x) && (points[1].x < rect->points[1].x) &&
                        (points[3].y > rect->points[3].y) && (points[0].y < rect->points[0].y);

    bool second_inside = (rect->points[0].x > points[0].x) && (rect->points[1].x < points[1].x) &&
                         (rect->points[3].y > points[3].y) && (rect->points[0].y < points[0].y);

    return !(outside || first_inside || second_inside);
}

void Task::read(istream &in)
{
    int count;
    in >> count;
    rects.resize(count);
    for (int t = 0; t < count; t++)
    {
        rects[t] = new Rectangle();
        rects[t]->read(in);

        for (int i = 0; i < 4; i++)
            points.insert(rects[t]->points[i]);
    }
}

void Task::addIntersection(int x, int y)
{
    Point *p = new Point(x, y);
    intersections.insert(*p);
}

// first must be horizontal & second -- vertical
void Task::intersectSegments(const Point &a, const Point &b, const Point &c, const Point &d)
{
    if (d.y <= a.y && a.y <= c.y &&
        a.x <= c.x && c.x <= b.x)
        addIntersection(c.x, a.y);
}

void Task::intersectRects(Rectangle *a, Rectangle *b)
{
    intersectSegments(a->points[0], a->points[1],
                      b->points[1], b->points[2]);

    intersectSegments(a->points[3], a->points[2],
                      b->points[1], b->points[2]);

    intersectSegments(a->points[0], a->points[1],
                      b->points[0], b->points[3]);

    intersectSegments(a->points[3], a->points[2],
                      b->points[0], b->points[3]);
}

void Task::findIntersections()
{
    for (uint i = 0; i < rects.size(); i++)
        for (uint j = 0; j < rects.size(); j++)
            intersectRects(rects[i], rects[j]);
}

uint Task::countPointEdges()
{
    uint res = 0;
    for (set<Point>::iterator i = points.begin(); i != points.end(); i++)
    {
        bool toSide[2][2] = {{0,0},{0,0}};
        for (uint j = 0; j < rects.size(); j++)
        {
            for (uint t = 0; t < 4; t++)
                if (i->between(rects[j]->points[t], rects[j]->points[(t+1)%4]))
                {
                    /* t & 1: horizontal or vertical segment
                    *  t < 2(t >= 2): correct side (left-right or up-down),
                    *               last segment has opposite order of points
                    */
                    if (*i != rects[j]->points[t])
                        toSide[t & 1][t >= 2] = true;
                    if (*i != rects[j]->points[(t+1)%4])
                        toSide[t&1][t < 2] = true;
                }
        }
        for (int t = 0; t < 4; t++)
            if (toSide[t < 2][t&1])
                res++;
    }
    return res;
}

void Task::markComponent(Rectangle *rect, int component)
{
    rect->component = component;
    for (uint i = 0; i < rects.size(); i++)
        if (rects[i]->component == -1 && rect->isNeighbor(rects[i]))
            markComponent(rects[i], component);
}

uint Task::countComponents()
{
    uint res = 0;
    for (uint i = 0; i < rects.size(); i++)
        if (rects[i]->component == -1)
            markComponent(rects[i], ++res);
    return res;
}

uint Task::solve()
{
    uint V = points.size(); // count of points without intersections
    uint E = countPointEdges(); // count of edges
    uint C = countComponents();

    findIntersections();
    points.insert(intersections.begin(), intersections.end()); // add intersections to points
    E += (points.size() - V)*4; // add edges of intersections( 4 on each one)
    E /= 2; // remove doubles
    V = points.size(); // count points with intersections

    return 1-V+E+C; //Euler's formula
}
