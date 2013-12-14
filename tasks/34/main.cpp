#include <iostream>
#include <fstream>
#include "btree.h"

using namespace std;

int main()
{
    BTree t;
    ofstream out("output.txt");
    for (int i = 0; i < 10; i++)
         t.insert(i);
     out << "...." << endl;
     t.print(out);

     out << "..." << endl;
     t.remove(5);
     t.remove(8);
     t.remove(6);
     t.print(out);
    out.close();
    return 0;
}

