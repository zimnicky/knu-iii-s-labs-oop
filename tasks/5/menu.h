#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include "intlist.h"

using namespace  std;

void help()
{
    cout << "Commands:" << endl
         << "help: shows this message"  << endl
         << "add <value>: adds <value> to the end of list" << endl
         << "del <number>: removes element with number <number> from the list" << endl
         << "show: shows elements of the list" << endl
         << "finish: finishes editing" << endl
         << "-----------" << endl;
}

void show(IntList *list)
{
    cout << "Elements:" << endl;
    for (auto i = list->begin(); i != nullptr; i = i->next())
        cout << i->getData() << " ";
    cout << endl;
}



void menu()
{
    bool finish = false;
    IntList *list = new IntList();

    while (!finish)
    {
        cout << "Enter command" << endl;
        string command;
        cin >> command;
        if (command == "help")
            help();
        else if (command == "show")
            show(list);
        else if (command == "finish")
                finish = true;
        else if (command == "add")
        {
            int t;
            cin >> t;
            list->pushBack(t);
            cout << "element was added" << endl;
        }
        else if (command == "del")
        {
            int t;
            cin >> t;
            if (list->deleteNode(list->getNode(t)))
                cout << "element was deleted" << endl;
            else
                cout << "element wasn't deleted" << endl;
        }
    }

    cout << "Enter N" << endl;
    int n;
    cin >> n;
    IntList *list2 = list->splitByNumber(n);
    cout << "list was splitted" << endl;
    cout << "LIST 1: elements > " << n << endl;
    show(list);
    cout << "LIST 2: elements <= " << n << endl;
    show(list2);
    delete list;
    delete list2;
    cout << endl << "Goodbye!" << endl;
}

#endif // MENU_H
