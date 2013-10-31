#include "sort.h"

void bucketSort(vector<int> &numbers, int countBuckets, int rangeStart, int rangeFinish)
{
    if (numbers.size() <= 1)
        return;

    // one bucket for each range
    vector<vector<int>> buckets;
    buckets.resize(countBuckets);

    rangeFinish -= rangeStart;

    //allocate numbers to the buckets
    for (auto i:numbers)
    {
        buckets[countBuckets*(i-rangeStart)/rangeFinish].push_back(i);
    }

    numbers.clear();
    //sort buckets & merge to the target array
    for (int i = 0; i < countBuckets; i++)
        if (buckets[i].size() > 0)
        {
            insertionSort(buckets[i]);
            numbers.insert(numbers.end(), buckets[i].begin(), buckets[i].end());
        }
}


void insertionSort(vector<int> &numbers)
{
    for (unsigned int i = 0; i < numbers.size(); i++)
    {
        int j = i;
        int el = numbers[i];
        while (j > 0 && el < numbers[j - 1]) // searching place
        {
            numbers[j] = numbers[j - 1];
            j--;
        }
        numbers[j] = el; // insert
    }
}
