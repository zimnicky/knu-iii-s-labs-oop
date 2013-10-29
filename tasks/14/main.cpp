#include <iostream>
#include <fstream>
#include "sort.h"

using namespace std;

int* read(ifstream &in, int &count)
{
    in >> count;
    int *res = new int[count];
    for (int i = 0; i < count; i++)
        in >> res[i];
    return res;
}


void write(ofstream &out, int a[], int count)
{
    for (int i = 0; i < count; i++)
        out << a[i] << " ";
}

int main()
{
    ifstream in("input.txt");
    int count = 0;
    int *a = read(in, count);

    heapSort(a, count);

    in.close();

    ofstream out("output.txt");
    write(out, a, count);
    out.close();

    return 0;
}

