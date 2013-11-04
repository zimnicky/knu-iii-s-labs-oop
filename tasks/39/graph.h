#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

class Graph
{
protected:
    vector<vector<int>> vertices; // adjacency list
    vector<int> groups;            // group id for each vertex

    bool markGroups(int v, int group);
public:
    Graph();
    void addEdge(unsigned int v1, unsigned int v2);
    bool getTwoGroups(vector<unsigned int> &first, vector<unsigned int> &second);
};

#endif // GRAPH_H
