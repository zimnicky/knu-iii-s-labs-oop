#ifndef GRAPHTASK9_H
#define GRAPHTASK9_H

#include <vector>
#include "../27/graphtask27.h"


using namespace std;

class GraphTask9: public GraphTask27
{
protected:
    vector<bool> isBackEdge;
    void dfsSkeletonBackEdges(uint v, vector<uint> &vcolors);
    void markGray(uint v, vector<int> &color);
public:
    GraphTask9();
    vector<uint> getMaxAlt(uint startV);
    vector<vector<uint>> RMF();     // relation of the mandatory forwardingg
    bool isReducable();
};

#endif // GRAPHTASK9_H
