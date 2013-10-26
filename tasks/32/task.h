#ifndef TASK_H
#define TASK_H

#include <string>
#include <memory.h>

using namespace std;

int encodeChar(char c)
{
    if (c < 'a')
        return c - 'A';
    else
        return c - 'a' + 26;
}

char decodeChar(int x)
{
    if (x >= 26)
        return x - 26 + 'a';
    return x + 'A';
}

string maxCommon(const string &a, const string &b)
{

    int lettersA[52], lettersB[52]; // counters for letters

    memset(lettersA, 0, sizeof lettersA);
    memset(lettersB, 0, sizeof lettersB);

    for (unsigned int i = 0; i < a.size(); i++) // count letters in a
        lettersA[encodeChar(a[i])]++;

    for (unsigned int i = 0; i < b.size(); i++) // count letters in b
        lettersB[encodeChar(b[i])]++;

    string res;

    for (unsigned int i = 0; i < 52; i++) // generate result string
    {
        int m = min(lettersA[i], lettersB[i]);
        for (int j = 0; j < m; j++)
            res.push_back(decodeChar(i));
    }

    return res;

}

#endif
