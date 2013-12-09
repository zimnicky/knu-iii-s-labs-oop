#include "graphtask9.h"

GraphTask9::GraphTask9()
{
}

void GraphTask9::markGray(uint v, vector<int> &color)
{
    if (color[v] == 0)
        color[v] = 1;
    else
        return;
    for (auto e: vertices[v])
        markGray(edges[e].to, color);
}

vector<uint> GraphTask9::getMaxAlt(uint startV)
{
    const int BLACK = 0;
    const int GRAY = 1;
    vector<int> color(vertices.size(), BLACK);

    markGray(startV, color);

    bool changed = true;
    while (changed)
    {
        changed = false;
        // all vertices, which have black parent are black
        for (uint v = 0; v < vertices.size(); v++)
        {
            if (color[v] == GRAY && v != startV)
            {
                if (redges[v].size() > 0 && color[edges[*redges[v].begin()].from] == BLACK)
                {
                    color[v] = BLACK;
                    changed = true;
                }
            }
        }
    }

    vector<uint> res;
    res.push_back(startV);
    for (uint v = 0; v < vertices.size(); v++)
       if (color[v] == GRAY)
           res.push_back(v);

    return res;
}

vector<vector<uint>> GraphTask9::RMF()
{
   vector<vector<uint>> res(vertices.size());
   for (uint i = 0; i < vertices.size(); i++)
   {
        vector<uint> tmp = getMaxAlt(i);
        for (auto v: tmp)
                res[v].push_back(i);
   }

   return res;
}


void GraphTask9::dfsSkeletonBackEdges(uint v, vector<uint> &vcolors)
{
    vcolors[v] = 1;
    for (auto e: vertices[v])
    {
        uint u = edges[e].to;
        switch (vcolors[u])
        {
            case 0: {
                isBackEdge[e] = false;
                dfsSkeletonBackEdges(u, vcolors);
                break;
            }
            case 1:{ // this is a cycle -- e is back-edge
                isBackEdge[e] = true;
                break;
            }
            default:{
                isBackEdge[e] = false;
            }
        }
    }
    vcolors[v] = 2;
}


bool GraphTask9::isReducable()
{
    vector<uint> vcolors(vertices.size());
    isBackEdge.resize(edges.size(), false);
    dfsSkeletonBackEdges(0, vcolors);

    auto rmf = RMF();

    bool res = true;
    for (uint e = 0; e < edges.size() && res; e++)
        if (isBackEdge[e])
        {
            bool endIsForwardingToBegin = false;
            for (auto v: rmf[edges[e].from])
                if (v == edges[e].to)
                    endIsForwardingToBegin = true;

            res = endIsForwardingToBegin;
        }

    return res;
}
