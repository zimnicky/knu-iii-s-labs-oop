#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

typedef unsigned int uint;
const int INF = 1e9;

class Graph
{
protected:
    struct Edge
    {
      uint v;
      int len;
      int num;
      Edge(uint vNum, int edgeLen, int edgeNum = 0):v(vNum),len(edgeLen),num(edgeNum){}
      Edge():v(0),len(INF),num(0){}
      bool operator <(const Edge &b) const{
          return len > b.len;
      }
    };

    vector<vector<Edge>> vertices;      // adjacency list
    vector<int> countIn;
    uint countEdges;

    bool hasCycles(unsigned int v, vector<int> &visited, uint mask);
    bool hasCycles(uint mask);
public:
    Graph();

    int countHammocks();
    void addEdge(uint v1, uint v2, int length);
};

#endif // GRAPH_H
