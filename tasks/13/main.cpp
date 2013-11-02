#include <iostream>
#include <fstream>
#include <vector>
#include "task.h"

using namespace std;

void read(istream &in, vector<vector<int>> &matrix)
{
    int m,n;
    in >> m >> n;
    matrix.resize(m);
    for (int i = 0; i < m; i++)
    {
        matrix[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            in >> matrix[i][j];
        }
    }
}

int main()
{
    vector<vector<int>> matrix;
    ifstream in("input.txt");
    read(in, matrix);
    in.close();

    Point a;
    Point b;

    cout << "Max is " << getMax(matrix, a, b) << endl;
    cout << "Points" << endl
         << a.i << " " << a.j << endl
         << a.i << " " << b.j << endl
         << b.i << " " << b.j << endl
         << b.i << " " << a.j << endl;

    return 0;
}

