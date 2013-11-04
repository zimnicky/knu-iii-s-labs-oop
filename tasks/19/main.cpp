#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main()
{
    ifstream in("input.txt");
    int c;
    in>> c;
    vector<Graph::Edge> edges;
    for (int i = 0; i < c; i++)
    {
        Graph::Edge t;
        in >> t.v1 >> t.v2 >> t.len;
        edges.push_back(t);
    }
    in.close();

    Graph g(edges);
    cout << "Kruskal's:" << endl;
    edges = g.kruskals();

    for (auto i: edges)
        cout << i.v1 << " " << i.v2 << " " << i.len << endl;

    cout << "----------------" << endl;

    cout << "Prim's:" << endl;
    edges = g.prims();

    for (auto i: edges)
        cout << i.v1 << " " << i.v2 << " " << i.len << endl;

    return 0;
}

