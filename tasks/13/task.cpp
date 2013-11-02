#include "task.h"


bool Point::operator ==(const Point& second)
{
    return i == second.i && j == second.j;
}

int getMax(vector<vector<int>> &matrix, Point &leftTop, Point &rightBottom)
{
    leftTop.i = 0;
    leftTop.j = 0;
    rightBottom.i = 0;
    rightBottom.j = 0;
    int maxSum = 0;

    //find first point
    for (unsigned int row = 0; row < matrix.size(); row++)
        for (unsigned int col = 0; col < matrix[row].size(); col++)
            //select point in current row
            for (unsigned int col1 = col + 1; col1 < matrix[row].size(); col1++)
                //select point in current column
                for (unsigned int row1 = row + 1; row1 < matrix.size(); row1++)
                {
                    int sum = matrix[row][col] + matrix[row][col1] + matrix[row1][col] + matrix[row1][col1];
                    // compare sum with current maximum
                    if (leftTop == rightBottom || sum > maxSum)
                    {
                        maxSum = sum;
                        leftTop.i = row;
                        leftTop.j = col;
                        rightBottom.i = row1;
                        rightBottom.j = col1;
                    }
                }
    return maxSum;
}
