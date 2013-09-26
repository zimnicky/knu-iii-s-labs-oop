#include <iostream>
#include <fstream>
#include "graphtask15.h"

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
    GraphTask15 g;
    ifstream in("input.txt");
    read(in, g);
    in.close();

    uint a, b;
    cin >> a >> b;

    auto path = g.shortestPath(a, b);

    write(cout, path);

    return 0;
}

