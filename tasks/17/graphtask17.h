#ifndef GRAPHTASK17_H
#define GRAPHTASK17_H

#include "../10/graph.h"


class GraphTask17: public Graph
{
public:
	GraphTask17():Graph(){}

	void addEdge(uint v1, uint v2);

	vector<uint> topsort(); // topological sorting

	vector<vector<uint>> bicomponents(); // returns bicomponents of this graph
};

#endif // GRAPHTASK17_H
