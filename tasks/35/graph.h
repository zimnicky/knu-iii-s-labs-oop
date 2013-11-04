#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Graph
{
protected:
    vector<vector<int>> vertices; // adjacency list
    vector<int> countIn; // number of incoming edges for eacg vertex
    bool hasCycles(unsigned int v, vector<int> &visited);
public:
    Graph();
    void addEdge(unsigned int v1, unsigned int v2);
    bool hasCycles();
    int isConnected();
};

#endif // GRAPH_H
