#ifndef GRAPHTASK27_H
#define GRAPHTASK27_H

#include "../10/graph.h"
#include "../17/graphtask17.h"

using namespace std;

class GraphTask27: public GraphTask17
{
protected:
    vector<uint> MNumber;
public:
    GraphTask27():GraphTask17(){}

    virtual vector<uint> topsort() override; // topological sorting

    void getNumering(vector<uint> &M, vector<uint> &T); // returns M-numbering & T-numbering
};

#endif // GRAPHTASK27_H
