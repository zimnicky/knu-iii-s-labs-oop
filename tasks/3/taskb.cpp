#include "taskb.h"
#include "taska.h"

TaskB::TaskB(string edges)
{
    this->edges = edges;
    // getting number of turns
    countTurns = 0;
    unsigned int t = edges.size();
    while (t > 0)
    {
        countTurns++;
        t >>= 1;
    }
}

string TaskB::getTurns()
{
    string s;
    s.resize(countTurns);
    for (unsigned int i = 0; i < countTurns; i++)
        s[i] = 'P';
    TaskA a(s);
    for (unsigned int i = 0; i < edges.size(); i++)
        if (edges[i] != a.getEdge(i+1))
            s[a.getTurnNumber(i+1) - 1] = 'Z';

    return s;
}
