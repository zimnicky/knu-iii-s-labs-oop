#include "graph.h"

Graph::Graph()
{
}

void Graph::addEdge(unsigned int v1, unsigned int v2)
{
    if (v1 >= vertices.size())
    {
        vertices.resize(v1 + 1);
        countIn.resize(v1 + 1);
    }
    if (v2 >= vertices.size())
    {
        vertices.resize(v2 + 1);
        countIn.resize(v2 + 1);
    }

    vertices[v1].push_back(v2);
    countIn[v2]++;
}


bool Graph::hasCycles(unsigned int v, vector<int> &visited)
{
    visited[v] = 1; // gray vertex
    bool res = false;

    for (unsigned int i = 0; i < vertices[v].size() && !res; i++)
        if (visited[vertices[v][i]] == 0)
            res = hasCycles(vertices[v][i], visited);
        else if (visited[vertices[v][i]] == 1)
            res = true;
    visited[v] = 2; //black vertex
    return res;
}

bool Graph::hasCycles()
{
    vector<int> visited;
    visited.resize(vertices.size());

    // find vertex without parent
    unsigned int v = 0;
    for (; v < vertices.size() && countIn[v] > 0; v++);

    if (countIn[v] > 0)
        return false;

    return hasCycles(v, visited);
}

int Graph::isConnected()
{
    vector<int> visited;
    visited.resize(vertices.size());

    // find vertex without parent
    unsigned int v = 0;
    for (; v < vertices.size() && countIn[v] > 0; v++);

    if (countIn[v] > 0)
        return false;

    hasCycles(v, visited);

    for (unsigned int i = 0; i < visited.size(); i++)
        if (visited[i] == 0)
            return false;

    return true;
}
