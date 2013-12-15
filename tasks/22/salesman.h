#ifndef SALESMAN_H
#define SALESMAN_H

#include <vector>
#include <cmath>

using namespace std;

class Salesman
{
public:
    struct Point
    {
        double x, y;
        Point(double _x=0, double _y=0){x = _x; y = _y;}
        double distance(const Point &second) const { return ((x-second.x)*(x-second.x) + (y-second.y)*(y-second.y));}
    };
private:

    vector<Point> cities;
    vector<vector<unsigned int>> population;

    void generatePopulation(unsigned int count);            // generates population whith count paths
    bool isDublicate(const vector<unsigned int> &path);     // checks if path already in population

    double fitness(unsigned int num);                       // calculates length of path
    void mutation(unsigned int num);                        // mutates  path
    void crossing(vector<vector<unsigned int>> &population, unsigned int a, unsigned int b);

    double doubleRand(double a, double b);
public:
    Salesman();
    void addCity(Point p);
    vector<unsigned int> run(unsigned int populationSize, unsigned int iterations, double chanceOfCrossing, double chanceOfMutation);
};

#endif // SALESMAN_H
