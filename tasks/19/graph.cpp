#include "graph.h"
#include "disjointset.h"
#include <algorithm>
#include <queue>

Graph::Graph(const vector<Edge> &edges)
{
    this->edges = edges;
    for (unsigned int i = 0; i < edges.size(); i++)
    {
        if (edges[i].v1 >= vertices.size())
            vertices.resize(edges[i].v1 + 1);

        if (edges[i].v2 >= vertices.size())
            vertices.resize(edges[i].v2 + 1);

        vertices[edges[i].v1].push_back(i);
        vertices[edges[i].v2].push_back(i);
    }
}

vector<Graph::Edge> Graph::kruskals()
{
    DisjointSet set(vertices.size());

    auto edgesCopy = edges;

    sort(edgesCopy.begin(), edgesCopy.end(), [](Edge a, Edge b){return a.len <= b.len;});
    vector<Edge> res;

    for (unsigned int i = 0; i < edgesCopy.size() && res.size() < vertices.size(); i++)
    {
        if (set.getNumberOfSet(edgesCopy[i].v1) != set.getNumberOfSet(edgesCopy[i].v2)) // if vertices are in different sets
        {
            res.push_back(edgesCopy[i]);             // add to the answer
            set.join(edgesCopy[i].v1, edgesCopy[i].v2);
        }
    }

    return res;
}


vector<Graph::Edge> Graph::prims()
{
    vector<int> dist; // distance from the tree to each vertex
    dist.resize(vertices.size(), 1000000000);
    dist[0] = 0;
    vector<bool> inTree; // if vertex already in tree
    inTree.resize(vertices.size(), false);
    inTree[0] = true;

    priority_queue<Edge> q;
    vector<Edge> result;

    // add neighbours of 0 to the queue
    for (unsigned int i = 0; i < vertices[0].size(); i++)
    {
        Edge tmp = edges[vertices[0][i]];
        int v2 = max(tmp.v1, tmp.v2);
        q.push(tmp);
        dist[v2] = tmp.len;
    }

    while (!q.empty())
    {
        // extract the best
        Edge e = q.top();
        q.pop();
        int v = e.v1;
        if (inTree[v])
            v = e.v2;

        if (e.len <= dist[v])
        {
            result.push_back(e);
            inTree[v] = true;

            // add his edges to the queue
            for (unsigned int i = 0; i < vertices[v].size(); i++)
            {
                Edge tmp = edges[vertices[v][i]];
                int v2 = tmp.v1;
                if (v2 == v)
                    v2 = tmp.v2;

                if (tmp.len < dist[v2])
                {
                    dist[v2] = tmp.len;
                    q.push(tmp);
                }
            }
        }
    }

    return result;
}
