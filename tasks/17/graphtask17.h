#ifndef GRAPHTASK17_H
#define GRAPHTASK17_H

#include "../10/graph.h"


class GraphTask17: public Graph
{
protected:
    vector<list<uint>>  redges;   // reversed edges for each vertex
public:
	GraphTask17():Graph(){}

	void addEdge(uint v1, uint v2);

    virtual vector<uint> topsort(); // topological sorting

    virtual vector<vector<uint>> bicomponents(); // returns bicomponents of this graph
};

#endif // GRAPHTASK17_H
