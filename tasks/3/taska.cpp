#include "taska.h"
#include <iostream>

using namespace std;

TaskA::TaskA(const string &s)
{
    turns = s;
}

TaskA::~TaskA()
{

}


char TaskA::getEdge(unsigned int number)
{
    unsigned int n = 1 << turns.size();

    // getting  number of turn
    unsigned int tmp = number;
    unsigned int curr = n >> 1;
    unsigned int level = 1;

    unsigned int turnNumber = 0;
    while (curr > 0 && tmp > 0)
    {
        level <<= 1;
        if (tmp >= curr)
            tmp -= curr;
        turnNumber++;
        curr >>= 1;
    }

    //cout << (turnNumber) << " ";

    if (turnNumber == 1)
        return (turns[0] == 'P')?'O':'K';

    //getting number of the edge on the level
    curr = n >> 1;
    unsigned int numberOnLevel = 0;
    unsigned int tLevel = 1;
    while (curr > 0 && number > 0)
    {
        tLevel <<= 1;
        if (number >= curr)
        {
            number -= curr;
            numberOnLevel += (level / tLevel) / 2;
        }
        curr >>= 1;
    }

    //cout << (numberOnLevel) << " ";

    if ((numberOnLevel & 1) == 0)
       return (turns[turnNumber - 1] == 'P')?'K':'O';
    else
       return (turns[turnNumber - 1] == 'P')?'O':'K';

}


unsigned int TaskA::getTurnNumber(unsigned int edge)
{
    unsigned int n = 1 << turns.size();

    unsigned int tmp = edge;
    unsigned int curr = n >> 1;

    unsigned int turnNumber = 0;
    while (curr > 0 && tmp > 0)
    {
        if (tmp >= curr)
            tmp -= curr;
        turnNumber++;
        curr >>= 1;
    }

    return turnNumber;
}
