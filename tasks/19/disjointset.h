#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include <vector>

using namespace std;


class DisjointSet
{
    vector<unsigned int> sets;
public:
    DisjointSet(unsigned int count);

    int getNumberOfSet(unsigned int element); // returns number of set, which contains element
    void join(unsigned int el1, unsigned int el2); // joins two sets, which contain el1 & el2
};

#endif // DISJOINTSET_H
