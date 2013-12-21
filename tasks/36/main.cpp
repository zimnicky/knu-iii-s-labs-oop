#include <iostream>
#include "game.h"

using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;

    Game g(n,k);
    int t;
    if (g.solve(t))
        cout << "res: " << t << endl;
    else
        cout << " no answer" << endl;
    return 0;
}

