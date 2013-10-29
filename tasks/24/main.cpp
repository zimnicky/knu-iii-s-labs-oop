#include <iostream>
#include <string>
#include "htree.h"

using namespace std;

int main()
{

    string str = "beep boop beer!";

    HTree tree(str);

    for (unsigned int i = 0; i < str.size(); i++)
    {
        string code = tree.getCode(str[i]);
        cout << str[i] << ": " << code << " -> " << tree.getChar(code) << endl;
    }

    return 0;
}

