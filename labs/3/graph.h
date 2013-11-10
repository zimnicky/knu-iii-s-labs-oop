#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>

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
      Edge(uint vNum, int edgeLen):v(vNum),len(edgeLen){}
      Edge():v(0),len(INF){}
      bool operator <(const Edge &b) const{
          return len > b.len;
      }
    };

    // for each vertex
    vector<vector<Edge>> vertices;      // adjacency list
    vector<int> dist;                   // distance for each vertex
    vector<uint> prev;                  // previous vertex in path
    vector<bool> needUpdate;            // distance for vertex was changed
    vector<int> newDistance;            // new distance to the vertex

    uint usedVertex;                    // minimum of minimums

    //for each thread
    vector<bool> minFound;              // if minimum of each group was found
    vector<Edge> minVertex;             // minimum of each group
    vector<bool> updateDistancesNow;    // if true -- it's time for updating distances
    vector<bool> finished;              // if thread was finished

    // mutexes
    mutex minFoundMutex;                // data: minFound, minVertex
    mutex updateMutex;                  // data: updateDistanceNow, usedVertex, needUpdate, newDistance
    mutex threadFinishedMutex;          // data: finished

    //condition variables
    condition_variable updateDistances;
    condition_variable nextMinimumFound;

    void threadFunc(uint id, uint vStart, uint vFinish); // main function of each threads
    static void threadFuncStatic(Graph *ref,uint id, uint vStart, uint vFinish); // a little cheat
public:
    Graph();
    void addEdge(uint v1, uint v2, int length);
    pair<vector<uint>, int> minPath(uint from, uint to, uint countThreads);
    pair<vector<uint>, int> minPath(uint from, uint to);                    // one thread
};

#endif // GRAPH_H
