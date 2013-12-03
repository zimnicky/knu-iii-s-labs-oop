#include <iostream>
#include "task.h"

using namespace std;

int main()
{
    int n,m,l,k,s;
    cin >>n >> m >> l >> k >> s;
    vector<CoinState> res;
    bool r = getResult(n,m,s,k,l,res);
    for (int i = 0; i < res.size(); i++)
        switch (res[i])
        {
        case CoinState::HEAD: cout << "H"; break;
        case CoinState::TAIL: cout << "T"; break;
        default: cout << "U";
        }
    cout << endl;
    return 0;
}

