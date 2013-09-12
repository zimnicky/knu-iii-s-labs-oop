#include <iostream>
#include <vector>
#include <memory.h>
#include <fstream>

using namespace std;

struct Point
{
    int x, y;
    Point(){ x = y = 0;}
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    bool operator !=(const Point &p) const
    {
        return p.x != x || p.y != y;
    }
};

struct Segment
{
    Point points[2];
    Segment()
    {
        memset(points, 0, sizeof points);
    }
};

struct Rectangle
{
    Point points[4];
    Rectangle(){
        memset(points, 0, sizeof points);
    }
    void read(istream &in)
    {
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
};

vector<Rectangle*> read(istream &in)
{
    int count;
    in >> count;
    vector<Rectangle*> res;
    res.resize(count);
    for (int t = 0; t < count; t++)
    {
        res[t] = new Rectangle();
        res[t]->read(in);
    }
    return res;
}

void addPoint(vector<Point*> points, Point *p)
{
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i] == p)
            return;
    }

}

int countParts(const vector<Rectangle*> &rects)
{
    vector<Point*> points;
    return 2 - V + E + C;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    vector<Rectangle*> rects = read(in);
    in.close();
    out << countParts(rects) << endl;
    out.close();
    return 0;
}

