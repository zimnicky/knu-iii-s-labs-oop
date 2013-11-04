#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Graph
{
public:
    struct Edge
    {
        unsigned int v1, v2;
        int len;
        bool operator <(const Edge &b) const
        {
            return len > b.len;
        }
    };
protected:
    vector<vector<int>> vertices; // adjacency list
    vector<Edge> edges;
public:
    Graph(const vector<Edge> &edges);

    vector<Edge> kruskals();
    vector<Edge> prims();
};

#endif // GRAPH_H
