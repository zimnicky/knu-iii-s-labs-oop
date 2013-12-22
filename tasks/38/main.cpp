#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

void read(istream &in, Graph &g)
{
    uint u, v;
    int l;

    while (in >> v)
    {
        in >> u;
        in >> l;
        g.addEdge(v, u, l);
    }
}

int main()
{
    Graph g;

    ifstream in("input.txt");
    read(in, g);
    in.close();

    uint f, s;
    cin >> f >> s;


    int dist = g.minDistance(f,s);
    cout << "min distance:" <<  dist << endl;
    cout << "Unique vertices:" << endl;
    auto r = g.differentPathsV(f,s);
    for (auto i: r)
    {
        for (auto j: i)
            cout << j << " ";
        cout << endl;
    }

    cout << "Unique edges:" << endl;
    r = g.differentPathsE(f,s);
    for (auto i: r)
    {
        for (auto j: i)
            cout << j << " ";
        cout << endl;
    }

    return 0;
}

