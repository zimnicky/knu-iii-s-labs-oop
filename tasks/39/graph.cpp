#include "graph.h"
#include <queue>

Graph::Graph()
{
}

void Graph::addEdge(unsigned int v1, unsigned int v2)
{
    if (v1 >= vertices.size())
    {
        vertices.resize(v1 + 1);
        groups.resize(v1 + 1);
    }
    if (v2 >= vertices.size())
    {
        vertices.resize(v2 + 1);
        groups.resize(v2 + 1);
    }

    vertices[v1].push_back(v2);
    vertices[v2].push_back(v1);
}

bool Graph::markGroups(int v, int group)
{
    groups[v] = group;
    group = 3 - group;

    bool res = true;

    for (unsigned int i = 0; i < vertices[v].size() && res; i++)
    {
        if (groups[vertices[v][i]] == 0)                // undefined group
            res = markGroups(vertices[v][i], group);
        else
            if (groups[vertices[v][i]] != group)       // wrong group
                return false;
    }

    return res;
}


bool Graph::getTwoGroups(vector<unsigned int> &first, vector<unsigned int> &second)
{
    bool res = true;

    //mark unmarked vertices
    for (unsigned int i = 0; i < vertices.size() && res; i++)
    {
        if (groups[i] == 0)
            res &= markGroups(i, 1);
    }

    if (!res) return false;

    for (unsigned int i = 0; i < vertices.size() && res; i++)
    {
        if (groups[i] == 1)
            first.push_back(i);
        else
            second.push_back(i);
    }

    return true;
}
