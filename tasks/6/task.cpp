#include "task.h"

bool getResult(unsigned int n, unsigned int m, unsigned int s, unsigned int k, unsigned int l, vector<CoinState> &result)
{
    vector<bool> reversed(n + m, false);
    result.resize(n+m);

    // reversing coins
    for (unsigned int i = 1; i <= k; i++)
        reversed[(s*i - 1)%(n+m)] = reversed[(s*i - 1)%(n+m)] ^ 1;

    unsigned int countReversed = 0;
    for (unsigned int i = 0; i < n+m; i++)
        countReversed += reversed[i];

    unsigned int countAlternations;         // number of alternation(head, tail, head, tail...)

    unsigned int currentPlace = (s - 1)%(n+m);  // cell, which we turn next
    while (!reversed[currentPlace])
        currentPlace = (currentPlace + s) % (n+m);

    CoinState firstStepState; // what state we need to set on places in first step

    unsigned int countTurns;

    if (n > l)
    { // we need to turn n - l heads
        countTurns = n - l;
        firstStepState = CoinState::HEAD;
    }
    else
    {// we need to turn l-n tails
        countTurns = l - n;
        firstStepState = CoinState::TAIL;
    }

    if (countTurns > k)
        return false;

    countAlternations = countReversed - countTurns;

    if (countAlternations%2 == 1)
        return false;

    if (2*m < countAlternations || 2*n < countAlternations)
        return false;


    unsigned int countCoins[2] = {n,m}; // [0] -- heads, [1] -- tails

    // first step:
    for (unsigned int i = 0; i < countTurns; i++)
    {
        result[currentPlace] = firstStepState;
        countCoins[unsigned(firstStepState) - 1]--;

        currentPlace = (currentPlace + s) % (n+m);
        while (!reversed[currentPlace])
            currentPlace = (currentPlace + s) % (n+m);
    }

    //second step:
    for (unsigned int i = 0; i < countAlternations; i++)
    {
        result[currentPlace] = CoinState((i&1) + 1);
        countCoins[i&1]--;

        currentPlace = (currentPlace + s) % (n+m);
        while (!reversed[currentPlace])
            currentPlace = (currentPlace + s) % (n+m);
    }

    //third step
    for (unsigned int i = 0; i < n+m; i++)
        if (result[i] == CoinState::UNDEFINED)
        {
            if (countCoins[0] > 0)
            {
                countCoins[0]--;
                result[i] = CoinState::HEAD;
            }
            else
                result[i] = CoinState::TAIL;
        }

    return true;
}
