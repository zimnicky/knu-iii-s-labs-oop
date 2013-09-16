#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <time.h>
#include "queue.h"

using namespace  std;

void help()
{
    cout << "Commands:" << endl
         << "help: shows this message"  << endl
         << "push <value>: adds <value> to the queue" << endl
         << "pop: removes element from the queue" << endl
         << "top: returns top element" << endl
         << "sort <type>: sorts queue (type={0: insertion sort, 1: quick sort})" << endl
         << "test: compare speeds of sorting algorithms" << endl
         << "finish: finishes editing" << endl
         << "-----------" << endl;
}

void test()
{
    srand(time(0));
    cout << "10000 float values:" << endl;
    Queue<float> *q1, *q2;
    clock_t midtime1 = 0;
    clock_t midtime2 = 0;

    for (int t = 0; t < 10; t++)
    {
        q1 = new Queue<float>();
        q2 = new Queue<float>();
        cout << "Test" << t << endl;
        for (int i = 0; i < 10000; i++)
        {
            float x = rand();
            q1->push(x);
            q2->push(x);
        }
        clock_t time = clock();
        q1->sort(Queue<float>::SortMethod::INSERTION);
        time = clock() - time;
        midtime1 += time;
        cout << "Insertion: " << (double)time/CLOCKS_PER_SEC << "s" << endl;

        time = clock();
        q2->sort(Queue<float>::SortMethod::INSERTION);
        time = clock() - time;
        midtime2 += time;
        cout << "Quick: " <<  (double)time/CLOCKS_PER_SEC << "s" << endl << endl;

        delete q1;
        delete q2;
    }

    cout << "Average time:" << endl;
    cout << "Insertion: " <<  (double)midtime1/10/CLOCKS_PER_SEC << "s" << endl;
    cout << "Quick: " << (double)midtime2/10/CLOCKS_PER_SEC << "s" << endl << endl;

}

void menu()
{
    bool finish = false;
    Queue<int> queue;

    while (!finish)
    {
        cout << "Enter command" << endl;
        string command;
        cin >> command;
        if (command == "help")
            help();
        else if (command == "sort")
        {
            int t;
            cin >> t;
            queue.sort(Queue<int>::SortMethod(t));
            cout << "queue was sorted" << endl;
        }
        else if (command == "finish")
                finish = true;
        else if (command == "push")
        {
            int t;
            cin >> t;
            queue.push(t);
            cout << "element was added" << endl;
        }
        else if (command == "pop")
        {
            cout << "last element: " << queue.top();
            queue.pop();
            cout << " was removed" << endl;
        }
        else if (command == "top")
             cout << "last element: " << queue.top() << endl;
        else if (command == "test")
            test();

    }

    cout << endl << "Goodbye!" << endl;
}

#endif // MENU_H
