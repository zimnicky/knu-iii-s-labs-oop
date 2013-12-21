#include <iostream>
#include "task.h"

int main()
{
    int c;
    vector<int> coefs;
    cin >> c;
    coefs.resize(c);
    for(int i=0; i < c; i++)
        cin >> coefs[i];
    int r;
    cin >> r;

    vector<int> res = solve(coefs, r);

    cout << "solution:" << endl;
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    return 0;
}
