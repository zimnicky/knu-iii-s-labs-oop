#ifndef GAME_H
#define GAME_H

#include <vector>

using namespace std;

class Game
{
private:
    int n;
    int k;

    vector<vector<int>> posType; // posType[n][k] -- type of situation with n matches, when max size of next move is k
                                  // 0 -- undefined, 1 -- win, 2 -- loss

    bool isWin(int n, int k);    // checks type of situation(true -- win)
public:
    Game(int n, int k);
    bool solve(int &count); // returns true, if win is possible & count -- solution for task

};


#endif // GAME_H
