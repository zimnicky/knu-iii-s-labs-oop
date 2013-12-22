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
        vertices.resize(v1 + 1);
    if (v2 >= vertices.size())
        vertices.resize(v2 + 1);

    vertices[v1].push_back(Edge(v2, length, countEdges));
    vertices[v2].push_back(Edge(v1, length, countEdges));
    countEdges++;
}

int Graph::minDistance(uint from, uint to)
{
    dist.clear(); dist.resize(vertices.size(), INF);
    dist[from] = 0;

    priority_queue<Edge> queue;
    queue.push(Edge(from, 0));

    while (!queue.empty())
    {
        Edge tmp = queue.top();
        queue.pop();

        if (tmp.len == dist[tmp.v])
            for (auto i: vertices[tmp.v])
                if (tmp.len + i.len < dist[i.v])
                {
                    dist[i.v] = tmp.len + i.len;
                    queue.push(Edge(i.v, dist[i.v]));
                }
    }

    return dist[to];
}


vector<uint> Graph::dfsVertices(uint curr, vector<bool> &visited, uint start, uint finish, bool &found)
{
    if (curr == finish)
    {
        found = true;
        return {curr};
    }

    for (Edge i: vertices[curr])
        if (!visited[i.v] && i.v != start)
        {
            if (i.v != finish)
                visited[i.v] = true;
            if (curr != start || i.v != finish || !visited[start])
            {
                auto r = dfsVertices(i.v, visited, start, finish, found);
                if (found)
                {
                    r.push_back(curr);
                    if (!visited[start] && curr == start && i.v == finish)
                        visited[start] = true;
                    return r;
                }
                else
                    visited[i.v] = false;
            }
        }

    found = false;
    return vector<uint>(0);
}

vector<vector<uint> > Graph::differentPathsV(uint start, uint finish)
{
    vector<vector<uint>> res;
    vector<bool> visited(vertices.size(), false);
    bool found = false;
    auto r = dfsVertices(finish, visited, finish, start, found);
    while (found)
    {
        res.push_back(r);
        r = dfsVertices(finish, visited, finish, start, found);
    }

    return res;
}


vector<uint> Graph::dfsEdges(uint curr, vector<bool> &used, uint start, uint finish, bool &found)
{
    if (curr == finish)
    {
        found = true;
        return {curr};
    }

    for (Edge i: vertices[curr])
        if (!used[i.num] && i.v != start)
        {
            used[i.num] = true;
            auto r = dfsEdges(i.v, used, start, finish, found);
            if (found)
            {
                r.push_back(curr);
                return r;
            }
            else
                used[i.num] = false;
        }

    found = false;
    return vector<uint>(0);
}


vector<vector<uint> > Graph::differentPathsE(uint start, uint finish)
{
    vector<vector<uint>> res;
    vector<bool> used(countEdges, false);
    bool found = false;
    auto r = dfsEdges(finish, used, finish, start, found);
    while (found)
    {
        res.push_back(r);
        r = dfsEdges(finish, used, finish, start, found);
    }

    return res;
}
