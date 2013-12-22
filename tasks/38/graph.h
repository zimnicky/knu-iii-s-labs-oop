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
    vector<int> dist;                   // distance for each vertex
    uint countEdges;

    vector<uint> dfsVertices(uint curr, vector<bool> &visited, uint start, uint finish, bool &found);
    vector<uint> dfsEdges(uint curr, vector<bool> &used, uint start, uint finish, bool &found);
public:
    Graph();
    void addEdge(uint v1, uint v2, int length);
    int minDistance(uint from, uint to);
    vector<vector<uint>> differentPathsV(uint start, uint finish);
    vector<vector<uint>> differentPathsE(uint start, uint finish);
};

#endif // GRAPH_H
