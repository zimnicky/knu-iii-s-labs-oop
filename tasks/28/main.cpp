#include <iostream>
#include "sort.h"
#include <time.h>

using namespace std;

vector<int> generate(int count, int min, int max)
{
    srand(clock());
    vector<int> res;
    res.resize(count);
    for (int i = 0 ;i < count; i++)
    {
        res[i] = rand()%(max - min) + min;
    }
    return res;
}

int main()
{
    int n;
    int min = 0, max = 100;
    int countBuckets = 2;
    cin >> n >> countBuckets;
    vector<int> t = generate(n, min,max);
    cout << "array: ";
    for (auto i: t)
        cout << i << " ";
    cout << endl << "Sorted: ";
    bucketSort(t, countBuckets, min, max);
    for (auto i: t)
        cout << i << " ";
    cout << endl;
    return 0;
}

