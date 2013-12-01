#include "polygon.h"
#include <cmath>


Polygon::Polygon()
{
}

float Polygon::distance(const Point &a, const Point &b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void Polygon::read(istream &in)
{\
    int t;
    in >> t;

    diagolnals.resize(t, vector<float>(t, 0));

    vector<Point> points(t);

    for (int i = 0; i < t; i++)
    {
        in >> points[i].x >> points[i].y;
        for (int j = 0; j < i; j++)
            diagolnals[i][j] = diagolnals[j][i] = distance(points[i], points[j]);
    }
}


float Polygon::taskA()
{
    int n = diagolnals.size();
    vector<vector<float>> f(n, vector<float>(n, 0));

    // searching minimal sum of diagonals for each subpolygon
    for (int j = 2; j < n; j++)      // choosing second point((i+j)%n)
        for (int i = 0; i < n; i++)      // choosing first point(i)
        {
            float minF = f[i][(i+1)%n] + f[(i+1)%n][(i+j)%n];
            for (int t = 2; t < j; t++)               // choosing third point
                minF = min(minF, f[i][(i+t)%n] + f[(i+t)%n][(i+j)%n]);

            f[i][(i+j)%n] = diagolnals[i][(i+j)%n] + minF;
        }

    //choose minimum from them
    float res = f[0][n-2];
    for (int i = 1; i < n; i++)
        res = min(res, f[i][(i + n-2)%n]);

    return res;
}


float Polygon::taskB()
{
    int n = diagolnals.size();
    vector<vector<float>> f(n, vector<float>(n, 0));

    // searching minimal maximum of diagonals for each subpolygon
    for (int j = 2; j < n; j++)      // choosing second point((i+j)%n)
        for (int i = 0; i < n; i++)      // choosing first point(i)
        {
            float minF = max(diagolnals[i][(i+j)%n],
                             max(f[i][(i+1)%n], f[(i+1)%n][(i+j)%n]));
            for (int t = 2; t < j; t++)               // choosing third point
                minF = min(minF, max(diagolnals[i][(i+j)%n],
                                    max(f[i][(i+t)%n], f[(i+t)%n][(i+j)%n])));

            f[i][(i+j)%n] = minF;
        }

    //choose minimum from them
    float res = f[0][n-2];
    for (int i = 1; i < n; i++)
        res = min(res, f[i][(i + n-2)%n]);

    return res;
}
