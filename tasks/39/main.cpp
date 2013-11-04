#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main()
{
    ifstream in("input.txt");

    int n;
    in >> n;

    Graph g;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n ; j++)
    {
           int t;
           in >> t;
           if (t == 1)
               g.addEdge(i,j);
    }

    in.close();

    vector<unsigned int> groups[2];

    if (!g.getTwoGroups(groups[0], groups[1]))
    {
        cout << "It is impossible" << endl;
        return 0;
    }


    for (int t = 0; t < 2; t++)
    {
        cout << "Group " << t << endl;
        for (unsigned int i = 0; i < groups[t].size(); i++)
            cout << groups[t][i] << " ";
        cout << endl;
    }


    return 0;
}

