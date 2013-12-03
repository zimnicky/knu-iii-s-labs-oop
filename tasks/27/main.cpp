#include <iostream>
#include <fstream>
#include "graphtask27.h"

using namespace std;


void read(istream &in, GraphTask27 *g)
{
    uint u, v;

    while (in >> v)
    {
        in >> u;
        g->addEdge(v, u);
    }
}

int main()
{
    GraphTask27 *g = new GraphTask27();

    ifstream in("input.txt");
    read(in, g);
    in.close();

    vector<uint> m,t,n, topsort;

    g->getNumering(m,t);
    topsort = g->topsort();
    n.resize(topsort.size());

    for (uint i = 0; i < topsort.size(); i++)
        n[topsort[i]] = i+1;

    ofstream out("output.txt");
    for (uint i = 0; i < m.size(); i++)
    {
        out << i << " "<< m[i] << " " << n[i] << " " << t[i] << endl;
    }
    out.close();

    return 0;
}
