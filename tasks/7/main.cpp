#include <iostream>
#include "queue.h"

using namespace std;

bool cmp(const int &a, const int &b)
{
    return a > b;
}

int main()
{
    Queue<int> q;
    for (int i = 10; i >= 0; i--)
        q.push(i);
    for (int i = 0; i < 5; i++)
    {
        cout << q.top() << " ";
        q.pop();
    }
    q.sort(Queue<int>::SortMethod::QSORT,
           &cmp
    );

    cout << endl;
    while (!q.isEmpty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
    return 0;
}

