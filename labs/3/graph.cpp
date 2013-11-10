#include "graph.h"

Graph::Graph()
{}

void Graph::addEdge(uint v1, uint v2, int length)
{
    if (v1 >= vertices.size())
        vertices.resize(v1 + 1);
    if (v2 >= vertices.size())
        vertices.resize(v2 + 1);

    vertices[v1].push_back(Edge(v2, length));
    vertices[v2].push_back(Edge(v1, length));
}


pair<vector<uint>, int> Graph::minPath(uint from, uint to, uint countThreads)
{
    uint vertexOnThread = vertices.size() / countThreads;

    // initializing variables
    dist.clear(); dist.resize(vertices.size(), INF);
    dist[from] = 0;
    prev.clear(); prev.resize(dist.size(), 0);
    needUpdate.clear(); needUpdate.resize(dist.size(), 0);
    newDistance.clear(); newDistance.resize(dist.size(), INF);

    minFound.clear(); minFound.resize(countThreads, false);
    minVertex.resize(countThreads);
    updateDistancesNow.clear(); updateDistancesNow.resize(countThreads, false);
    finished.clear(); finished.resize(countThreads, false);

    vector<thread*> threads;

    // creatting threads
    for (uint i = 0; i < countThreads; i++)
    {
        uint vStart = i*vertexOnThread;
        uint vFinish = vStart + vertexOnThread;
        if (i == countThreads - 1) vFinish = vertices.size();
        thread *t = new thread(threadFuncStatic, this, i, vStart, vFinish);
        threads.push_back(t);
    }

    bool countFinished = 0; // count of finished threads
    do
    {
        unique_lock<std::mutex> locker(minFoundMutex);
        bool allMinimumsFound = false;

        do   // waiting while threads are searching minimums
        {
            // check if all threads already have been found minimum
            countFinished = 0;
            allMinimumsFound = true;
            threadFinishedMutex.lock();
            for (uint i = 0; i < countThreads; i++)
                if (!finished[i])
                {
                    countFinished++;
                    allMinimumsFound &= minFound[i];
                }
            threadFinishedMutex.unlock();

            if (!allMinimumsFound)
                nextMinimumFound.wait(locker); // waiting for the next minimum

        }
        while (!allMinimumsFound); // all minimums were found or all threads were finished

        if (countFinished > 0) // some thread is working
        {
            // select minimum from all
            Edge minAll(0,0);
            bool thereIsMin = false;

            threadFinishedMutex.lock();
            for (uint i = 0; i < countThreads; i++)
                if (!finished[i])
                {
                    if (!thereIsMin || minAll.len > minVertex[i].len)
                    {
                        minAll = minVertex[i];
                        thereIsMin = true;
                    }
                    minFound[i] = false;
                }
            threadFinishedMutex.unlock();

           // notify all threads about updating
           updateMutex.lock();
           for (auto i: vertices[minAll.v])
           {
               needUpdate[i.v] = true;
               newDistance[i.v] = minAll.len + i.len;
           }
           usedVertex = minAll.v;

           for (uint i = 0; i < countThreads; i++)
               updateDistancesNow[i] = true;

           updateDistances.notify_all();
           updateMutex.unlock();
        }

    }
    while (countFinished > 0);  // any thread is working

    // getting path
    pair<vector<uint>, int> res;
    res.second = dist[to];
    uint current = to;
    while (current != from)
    {
        res.first.push_back(current);
        current = prev[current];
    }
    res.first.push_back(from);

    return res;
}


void Graph::threadFunc(uint id, uint vStart, uint vFinish)
{
    priority_queue<Edge> queue;
    for (uint i = vStart; i != vFinish; i++)
        if (dist[i] < INF)
            queue.push(Edge(i, dist[i]));

    if (queue.empty())
        queue.push(Edge(vStart, dist[vStart]));

    while (!queue.empty())
    {
        Edge tmp = queue.top();
        if (tmp.len == dist[tmp.v]) // minimum was found
        {

            // sending minimum to the main thread
            minFoundMutex.lock();
            minFound[id] = true;
            minVertex[id] = tmp;
            nextMinimumFound.notify_one();
            minFoundMutex.unlock();

            vector<Edge> changed; // list of changed vertices

            uint currV = 0; // current used vertex

            {   // receiving update-signal from the main thread
                unique_lock<std::mutex> locker(updateMutex);

                while (!updateDistancesNow[id])
                    updateDistances.wait(locker);

                for (uint i = vStart; i != vFinish; i++)
                    if (needUpdate[i] == true)         // looking for changed vertices
                    {
                        changed.push_back(Edge(i, newDistance[i]));
                        needUpdate[i] = false;
                    }

                currV = usedVertex;

                updateDistancesNow[id] = false;
            }

            for (auto i: changed) //updating distances
                if (i.len < dist[i.v])
                {
                    dist[i.v] = i.len;
                    prev[i.v] = usedVertex;
                    queue.push(i);
                }

            if (currV == tmp.v) // current minimum was used, remove it from the queue
                queue.pop();
        }
        else
            queue.pop();
    }

    // notifying other threads about finishing
    unique_lock<std::mutex> locker(threadFinishedMutex);
    finished[id] = true;
    nextMinimumFound.notify_all();
}


pair<vector<uint>, int> Graph::minPath(uint from, uint to)
{
    dist.clear(); dist.resize(vertices.size(), INF);
    dist[from] = 0;
    prev.clear(); prev.resize(dist.size(), 0);

    priority_queue<Edge> queue;
    queue.push(Edge(from, 0));

    while (!queue.empty())
    {
        Edge tmp = queue.top();
        queue.pop();

        if (tmp.len == dist[tmp.v])
            for (auto i: vertices[tmp.v])
                if (tmp.len + i.len < dist[i.v])
                {
                    dist[i.v] = tmp.len + i.len;
                    prev[i.v] = tmp.v;
                    queue.push(Edge(i.v, dist[i.v]));
                }
    }

    // getting path
    pair<vector<uint>, int> res;
    res.second = dist[to];
    uint current = to;
    while (current != from)
    {
        res.first.push_back(current);
        current = prev[current];
    }
    res.first.push_back(from);

    return res;
}

void Graph::threadFuncStatic(Graph *ref,uint id, uint vStart, uint vFinish)
{
    ref->threadFunc(id, vStart, vFinish);
}
