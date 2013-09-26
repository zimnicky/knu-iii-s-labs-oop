#include <iostream>
#include <cstdio>
#include "graph.h"

using namespace std;

void read(istream &in, Graph &g)
{
    uint e, v;

    while ( in >> e >> v)
        g.addIncedenceRelation(e, v);
}

void write(ostream &out, const vector<uint> &data)
{
    for (uint i: data)
        out << i << " ";
    out << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    Graph g;
    read(cin, g);

    auto path = g.eulerianPath();

    write(cout, path);

    return 0;
}

