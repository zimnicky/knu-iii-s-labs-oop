#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <stack>

using namespace std;

typedef unsigned int uint;

class Graph
{
protected:
    struct Edge
    {
        int from, to;
        bool deleted;
        Edge(int f = -1, int t = -1):from(f), to(t), deleted(false){}
    };

    vector<list<uint>> vertexes; // adjacency list,  vertex: numbers of edges
    vector<Edge> edges;

public:
    Graph(){}

    uint countVertexes()const {return vertexes.size();}
    uint countEdges() const {return edges.size();}

    void addIncedenceRelation(uint edgeNum, uint vertexNum); // adds relation between edge & vertex

    vector<uint> eulerianPath(); // returns eulerian path if exists
};

#endif // GRAPH_H
