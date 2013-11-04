#ifndef GRAPHTASK26_H
#define GRAPHTASK26_H

#include <string>
#include <vector>

using namespace std;

class Graph
{
protected:
    vector<string> words; //dictionary
    vector<vector<int>> vertices; // adjacency list

    bool isNeighbours(const string &a, const string &b); // check if a & b have only 1 symbol difference
    vector<int> maxPathFromVertex(int v, vector<int> &visited, int currStep);

public:
    Graph(const vector<string> &words);
    vector<string> getMaxPath();
};

#endif // GRAPHTASK26_H
