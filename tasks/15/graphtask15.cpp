#include "graphtask15.h"


vector<uint> GraphTask15::shortestPath(uint from, uint to)
{
    queue<pair<uint, uint>> q; // pair<vertex, length of path>
    vector<bool> visited(vertexes.size());      // visited vertexes
    vector<uint> prev(vertexes.size());         // previous vertex in path

    bool finished = false;
    q.push(make_pair(to, 0u)); // go from the end(for easier search of path)

    while (!q.empty() && !finished)
    {
        uint v = q.front().first;
        uint step = q.front().second;
        for (auto edge: vertexes[v]) // add all connected vertexes to the queue
        {
            uint t = ((uint)edges[edge].from == v)? edges[edge].to: edges[edge].from;

            if (!visited[t])
            {
                prev[t] = v;
                visited[t] = true;
                if (t == from) // finished search
                {
                    finished = true;
                    break;
                }
               q.push(make_pair(t, step + 1));
            }
        }
        q.pop();
    }

    vector<uint> res;

    if (!finished) // no path
        return res;

    uint v = from;

    while (v != to) // go to the end, using information about previous vertex
    {
        res.push_back(v);
        v = prev[v];
    }
    res.push_back(to);

    return res;
}
