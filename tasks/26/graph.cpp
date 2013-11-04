#include "graph.h"
#include <algorithm>


Graph::Graph(const vector<string> &words)
{
    this->words = words;
    vertices.resize(words.size());

    for (unsigned int i = 0; i < words.size(); i++)
        for (unsigned int j = i + 1; j < words.size(); j++)
            if (isNeighbours(words[i], words[j]))
            {
                vertices[i].push_back(j);
                vertices[j].push_back(i);
            }
}


bool Graph::isNeighbours(const string &a, const string &b)
{
    if (a.size() == b.size()) // check replaced-case
    {
        int replaced = 0;
        for (unsigned int i = 0; i < a.size() && replaced < 2; i++)
            if (a[i] != b[i])
                replaced++;

        if (replaced == 1) return true;
    }

    if (a.size() - b.size() == 1)//check remove-case
    {
        int removed = 0;
        unsigned int i = 0;
        while (i < b.size() && removed < 2)
        {
            if (a[i + removed] != b[i])
                removed++;
            else
                i++;
        }

        if (removed <= 1) return true;
    }

    if (b.size() - a.size() == 1)//check add-case
    {
        int removed = 0;
        unsigned int i = 0;
        while (i < a.size() && removed < 2)
        {
            if (b[i + removed] != a[i])
                removed++;
            else
                i++;
        }

        if (removed <= 1) return true;
    }

    return false;
}

vector<int> Graph::maxPathFromVertex(int v, vector<int> &visited, int currStep)
{
    visited[v] = currStep;

    vector<int> result;

    for (unsigned int i = 0; i < vertices[v].size(); i++)
        if (visited[vertices[v][i]] != currStep)
        {
            vector<int> tmp = maxPathFromVertex(vertices[v][i], visited, currStep); // get path & compare with others
            if (tmp.size() > result.size())
                result = tmp;
        }

    result.push_back(v);

    return result;
}

vector<string> Graph::getMaxPath()
{
    int currStep = 1;
    vector<int> visited;
    visited.resize(vertices.size());
    vector<int> maxPath;
    vector<int> currPath;

    // choose maximal path
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        currPath = maxPathFromVertex(i, visited, currStep++);
        if (currPath.size() > maxPath.size())
            maxPath = currPath;
    }

    // get words
    vector<string> result;
    result.resize(maxPath.size());

    for (unsigned int i = 0; i < maxPath.size(); i++)
        result[i] = words[maxPath[i]];

    return result;
}
