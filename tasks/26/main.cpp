#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main()
{

    ifstream in("input.txt");
    vector<string> words;
    int count;
    in >> count;
    words.resize(count);
    if (count > 0)
       getline(in, words[0], '\n');
    for (int i = 0; i < count; i++)
        getline(in, words[i], '\n');
    in.close();

    Graph g(words);

    words = g.getMaxPath();

    for (unsigned int i = 0; i < words.size(); i++)
        cout << words[i] << endl;

    return 0;
}

