#include "task.h"
#include <algorithm>
#include <ctime>


int gcd(vector<int> &coefs, vector<int> &result)
{
    result.resize(coefs.size(), 0);
    result[0] = 1;

    int a = coefs[0];

    //gcd(coefs[i]) = gcd(...gcd(gcd(coefs[0],coefs[1]), coefs[3])...)
    for (int i = 1; i < coefs.size(); i++)
    {
        // getting vector of next value(coefs[] is a system of axes)
        vector<int> curr(coefs.size(), 0);
        curr[i] = 1;

        int b = coefs[i];

        //calculate gcd(a,b) & vector for it
        while (b != 0)
        {
            int tmp;
            // getting vectors of new a & b
            for (int j = 0; j < coefs.size(); j++)
            {
                tmp = curr[j];
                curr[j] = result[j] - (a/b)*curr[j];
                result[j] = tmp;
            }

            // getting new a & b
            tmp = b;
            b = a%b;
            a = tmp;
        }
    }

    return a;
}

vector<int> solve(vector<int> &coefs, int rightVal)
{
    vector<int> res;
    int g = gcd(coefs, res);

    if (rightVal % g != 0)
        return vector<int>(0);

    rightVal /= g;

    for (int &i: res)
        i *= rightVal;

    return res;
}
