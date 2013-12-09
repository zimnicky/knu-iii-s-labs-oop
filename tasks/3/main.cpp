#include <iostream>
#include <fstream>
#include "taska.h"
#include "taskb.h"

int main()
{
    fstream in("input.txt");
    string str;
    getline(in, str, '\n');
    TaskA a(str);
    int count = (1 << str.size()) - 1;

    for (int i = 0; i < count; i++)
    {
        cout << a.getEdge(i+1);
    }
    cout << endl;
    getline(in, str, '\n');
    TaskB b(str);
    cout << b.getTurns() << endl;
    in.close();
    return 0;
}

