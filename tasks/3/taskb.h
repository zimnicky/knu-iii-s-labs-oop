#ifndef TASKB_H
#define TASKB_H

#include <string>

using namespace std;

class TaskB
{
private:
    string edges;
    unsigned int countTurns;
public:
    TaskB(string edges);
    string getTurns();
};

#endif // TASKB_H
