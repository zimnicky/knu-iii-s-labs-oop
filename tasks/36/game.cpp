#include "game.h"

Game::Game(int n, int k)
{
    this->n = n;
    this->k = k;
    posType.resize(n+1, vector<int>(k+1,0));
}

bool Game::isWin(int n, int k)
{
    if (posType[n][k] != 0) return posType[n][k] == 1;

    if (n == 0)
    {
        posType[n][k] = 1;
        return true;
    }


    k = min(n, k);

    // try all variants
    for (int i = 1; i <= k; i++)
    {
        if (!isWin(n - i, i+1))
        {
            posType[n][k] = 1;
            return true;
        }
    }

    posType[n][k] = 2;
    return false;
}


bool Game::solve(int &count)
{
    for (int i = 1; i <= k; i++)
        if (!isWin(n-i, i+1))
        {
            count = i;
            return true;
        }

    return false;
}
