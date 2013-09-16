#include <iostream>
//#include "avltree.h"
#include "rbtree.h"

using namespace std;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin >> n;
    RBTree<int> tree;
    for (int i = 0; i< n; i++)
    {
        int t = rand()%(n*10);
        cout << "add " << t << endl;
        tree.insert(t);
        tree.print();
        cout << "-----------" << endl;
    }
    cout << endl;
    tree.print();
    for (int i = 1; i< n; i+=2)
    {
        int t = i;
        cout << "add " << t << endl;
        tree.insert(t);
        tree.print();
        cout << "-----------" << endl;
    }

    for (int i = 1; i< n; i+=2)
    {
        cout << i << " ";
        tree.insert(i);
    }
    cout << endl;

    tree.print();

    cout << "find 1..n:" << endl;
    for (int i = 1; i < n ; i++)
        cout << tree.find(i);

    cout << endl << "-----------" << endl;

    cout << "remove odd in [1..n]" << endl;
    for (int i = 1; i< n; i+=2)
    {
        tree.remove(i);
    }

    tree.print();
    return 0;
}

