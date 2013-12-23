#include "graph.h"
#include <queue>
#include <list>

Graph::Graph()
{
    countEdges = 0;
}

void Graph::addEdge(uint v1, uint v2, int length)
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


    vertices[v1].push_back(Edge(v2, length, countEdges));
    countIn[v2]++;
    countEdges++;
}

bool Graph::hasCycles(uint v, vector<int> &visited, uint mask)
{
    visited[v] = 1; // gray vertex
    bool res = false;

    for (uint i = 0; i < vertices[v].size() && !res; i++)
        if (((1 << vertices[v][i].num) & mask) != 0)
        {
            if (visited[vertices[v][i].v] == 0)
                res = hasCycles(vertices[v][i].v, visited, mask);
            else if (visited[vertices[v][i].v] == 1)
                res = true;
        }
    visited[v] = 2; //black vertex
    return res;
}

bool Graph::hasCycles(uint mask)
{
    vector<int> visited;
    visited.resize(vertices.size());

    // find vertex without parent
    unsigned int v = 0;
    for (; v < vertices.size() && countIn[v] > 0; v++);

    if (countIn[v] > 0)
        return false;

    return hasCycles(v, visited, mask);
}

int Graph::countHammocks()
{
    unsigned int maxCount = (1 << countEdges) - 1;

    int res = 0;

    for (unsigned int i = 0; i < maxCount; i++)
        if (!hasCycles(i))
            res++;
    return res;
}
