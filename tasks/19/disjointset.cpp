#include "disjointset.h"

DisjointSet::DisjointSet(unsigned int count)
{
    sets.resize(count);
    for (unsigned int i = 0; i < count; i++)
        sets[i] = i;
}


int DisjointSet::getNumberOfSet(unsigned int element)
{
    if (element != sets[element])
        sets[element] = getNumberOfSet(sets[element]);
    return sets[element];
}

void DisjointSet::join(unsigned int el1, unsigned int el2)
{
    int p1 = getNumberOfSet(el1);
    int p2 = getNumberOfSet(el2);
    sets[p2] = p1;
}
