#include <iostream>
#include <fstream>
#include <ctime>
#include "graph.h"

using namespace std;


int main()
{
    ifstream in("input.txt");
    Graph *g = new Graph();
    uint n;
    in >> n;
    for (uint i = 0; i < n; i++)
    {
        uint v1, v2;
        int len;
        in >> v1 >> v2 >> len;
        g->addEdge(v1,v2,len);
    }
    uint v1, v2, countThreads;

    in >> v1 >> v2 >> countThreads;

    in.close();


    cout << "Classic algorithm:" << endl;
    clock_t t = clock();
    auto res = g->minPath(v1, v2, countThreads);
    t = clock() - t;

    cout << "Distance = "<< res.second << endl;
    cout << "Path: " << endl;
    for (auto i = res.first.rbegin(); i != res.first.rend(); i++)
        cout << *i << " ";
    cout << endl;
    cout << "Time:" << ((float)t)/CLOCKS_PER_SEC << endl;

    cout << "Multithread algorithm:" << endl;

    t = clock();
    res = g->minPath(v1, v2, countThreads);
    t = clock() - t;

    cout << "Distance = "<< res.second << endl;
    cout << "Path: " << endl;
    for (auto i = res.first.rbegin(); i != res.first.rend(); i++)
        cout << *i << " ";
    cout << endl;
    cout << "Time:" << ((float)t)/CLOCKS_PER_SEC << endl;

    delete g;
    return 0;
}

