#include "sort.h"
#include <algorithm>
#include <iostream>

using namespace std;

void heapSort(int arr[], int count)
{
    for(int i = (count >> 1) - 1; i >= 0; i--) //make heap
    {
       heapSift(arr, i, count - 1);
       for (int j = 0; j < count; j++)
           cout << arr[j] << " ";
       cout << endl;
    }

    while (count > 1)
    {
        count--;
        std::swap(arr[0], arr[count]); // remove the largest element
        heapSift(arr, 0, count - 1);   // & rebuild  heap
    }
}


void heapSift(int arr[], int pos, int last)
{
    int leftChild = (pos << 1) + 1;    // children of current element
    int rightChild = leftChild + 1; //

    int nextPos = pos; //left or right child

    // compare pos with children
    if (leftChild  <= last && arr[leftChild] > arr[nextPos])
        nextPos = leftChild;
    if (rightChild  <= last && arr[rightChild] > arr[nextPos])
        nextPos = rightChild;

    if (nextPos != pos)
    {
        std::swap(arr[pos], arr[nextPos]); // move pos to the next level;
        heapSift(arr, nextPos, last);
    }
}
