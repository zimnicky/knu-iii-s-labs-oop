#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <vector>
#include <set>
#include <memory.h>

using namespace std;

typedef unsigned int uint;

class Task
{
    struct Point
    {
        int x, y;
        Point(){ x = y = 0;}
        Point(int x, int y){
            this->x = x;
            this->y = y;
        }
        bool operator != (const Point &p) const
        {
            return p.x != x || p.y != y;
        }

        bool operator < (const Point &p) const
        {
            return (x == p.x)?y < p.y:x < p.x;
        }

        bool between(const Point &a, const Point &b) const; // checks if point is between two others
    };

    struct Rectangle
    {
        Point points[4];
        int component; // number of connected component
        Rectangle(){
            memset(points, 0, sizeof points);
            component = -1;
        }
        void read(istream &in);
        bool isNeighbor(Rectangle *rect);
    };


    vector<Rectangle*> rects;
    set<Point> points;
    set<Point> intersections;
    vector<int> rect_colors;

    void addIntersection(int x, int y);
    void intersectSegments(const Point &a, const Point &b, const Point &c, const Point &d);
    void intersectRects(Rectangle *a, Rectangle *b);
    void findIntersections();

    uint countPointEdges();

    void markComponent(Rectangle *rect, int component);
    uint countComponents();
public:
    Task(){}
    void read(istream &in);
    uint solve();
};



#endif // TASK_H
