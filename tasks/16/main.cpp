#include <iostream>
#include <fstream>
#include "tree.h"

using namespace std;

void read(istream &in, Tree &tree)
{
    int count;
    in >> count;

    for (int i = 0; i < count; i++)
    {
        int t1, t2;
        in >> t1 >> t2;
        tree.addChild(t1, t2);
    }
}

int main()
{
    ifstream in("input.txt");
    Tree t1, t2;

    read(in, t1);
    read(in, t2);

    in.close();

    cout << "Contains " << t1.countIsomorphicSubtrees(t2) << " isomorphic to the second tree subtrees" << endl;
    return 0;
}

