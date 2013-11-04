#include <iostream>
#include "graph.h"

using namespace std;

void read(istream &in, Graph &g)
{
    int n;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        char a = in.get();
        while (a < 'A' || a >'Z')
            a = in.get();

        char c = in.get();
        while (c != '<')
            c = in.get();

        char b = in.get();
        while (b < 'A' || b >'Z')
            b = in.get();

        g.addEdge(b-'A', a - 'A');
    }
}

int main()
{
    Graph g;
    read(cin, g);

    if (!g.isConnected())
        cout << "Not enough information" << endl;
    else
        if (g.hasCycles())
            cout << "Absolutely no" << endl;
    else
            cout << "Yes, it is" <<endl;


    return 0;
}

