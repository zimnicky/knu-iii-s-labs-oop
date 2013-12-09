#ifndef TASKA_H
#define TASKA_H

#include <string>
#include <vector>

using namespace std;

class TaskA
{
private:
    string turns; // side of turn for each edge

public:
    TaskA(const string &s);
    ~TaskA();
    char getEdge(unsigned int number);
    unsigned int getTurnNumber(unsigned int edge);
};

#endif // TASKA_H
