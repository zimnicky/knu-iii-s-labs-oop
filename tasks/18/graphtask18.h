#ifndef GRAPHTASK18_H
#define GRAPHTASK18_H

#include "../10/graph.h"

class GraphTask18: public Graph
{
public:
    GraphTask18():Graph(){}
    vector<vector<uint>> fundamentalCycles();
};

#endif // GRAPHTASK18_H
