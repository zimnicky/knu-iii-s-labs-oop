#ifndef GRAPHTASK15_H
#define GRAPHTASK15_H

#include "../10/graph.h"

#include <queue>

class GraphTask15:public Graph
{
public:
    GraphTask15():Graph(){}

    vector<uint> shortestPath(uint from, uint to);
};

#endif // GRAPHTASK15_H
