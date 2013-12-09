#include <iostream>
#include <fstream>
#include "graphtask9.h"

using namespace std;

void read(istream &in, GraphTask9 *g)
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
    GraphTask9 *g = new GraphTask9();

    ifstream in("input");
    read(in, g);
    in.close();

    if (g->isReducable())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;

    return 0;
}
