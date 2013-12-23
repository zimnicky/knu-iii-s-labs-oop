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

    cout << "Number of hammocks:" << g.countHammocks() << endl;
    return 0;
}

