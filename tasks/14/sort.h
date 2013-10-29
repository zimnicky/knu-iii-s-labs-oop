#ifndef SORT_H
#define SORT_H

void heapSort(int arr[], int count);


/* sift element(pos) to the right place, if end of arr is heap */
void heapSift(int arr[], int pos, int last);

#endif // SORT_H
