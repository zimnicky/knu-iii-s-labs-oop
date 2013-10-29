#ifndef PALINDROME_H
#define PALINDROME_H

#include <string>
#include <vector>

using namespace std;

string palindrome(const string &str)
{
    vector<vector<int> > lenMatrix; // length of substring

    int strLen = str.size();

    lenMatrix.resize(strLen + 1);

    for (int i = 0; i <= strLen; i++)
        lenMatrix[i].resize(strLen + 1);

    // find max subsequence of str and reversed str
    for (int i = 1; i <= strLen; i++)
        for (int j = 1; j <= strLen; j++)
            if (str[i - 1] == str[strLen - j]) // symbols are equal
                lenMatrix[i][j] = lenMatrix[i-1][j-1] + 1;
            else // else select max
                lenMatrix[i][j] = max(lenMatrix[i-1][j], lenMatrix[i][j-1]);

    //recover result
    int i = strLen;
    int j = strLen;
    string res;

    while (i != 0 && j != 0)
    {
        if (str[i - 1] == str[strLen - j]) // if symbols are equal, add it to result
        {
            res.push_back(str[i - 1]);
            i--; j--;
        }
        else if (lenMatrix[i-1][j] > lenMatrix[i][j - 1])
            i--;
        else
            j--;
    }

    return res;

}

#endif // PALINDROME_H
