#ifndef TASK_H
#define TASK_H
#include <vector>

using namespace std;

struct Point
{
  int i, j;
  bool operator ==(const Point& second);
};

// returns 2 diagonal point from the target rectangle & sum of it
int getMax(vector<vector<int>> &matrix, Point &leftTop, Point &rightBottom);


#endif // TASK_H
