#include "intlist.h"

IntList::IntList()
{
    head = nullptr;
}


IntList::~IntList()
{
    Node *tmp;
    while (head != nullptr)
    {
        tmp = head;
        head = head->next();
        delete tmp;
    }
}

void IntList::Node::insert(IntList::Node *node)
{
    node->_next = _next;
    _next = node;
}

IntList::Node* IntList::insertBefore(IntList::Node *node, IntList::Node *new_node)
{
    new_node->_next = nullptr;
    if (node == nullptr) // if list is empty
        head = new_node;
    else
    {
        Node *tmp = head;
        while (tmp->next() != node && tmp->next() != nullptr) //searching node
            tmp = tmp->next();
        tmp->insert(new_node);
    }
    return new_node;
}

IntList::Node* IntList::insertAfter(IntList::Node *node, IntList::Node *new_node)
{
    new_node->_next = nullptr;
    if (node == nullptr) // if list is empty
        head = new_node;
    else
        node->insert(new_node);
    return new_node;
}

IntList::Node* IntList::pushBack(IntList::Node *new_node)
{
    new_node->_next = nullptr;
    if (head == nullptr)
        head = new_node;
    else
    {
        Node *tmp = head;
        while (tmp->next() != nullptr) //searching end of list
            tmp = tmp->next();
        tmp->insert(new_node);
    }

    return new_node;
}

IntList::Node* IntList::insertBefore(IntList::Node *node, int val)
{
    Node *new_node = new Node(val);
    return insertBefore(node, new_node);
}

IntList::Node* IntList::insertAfter(IntList::Node *node, int val)
{
    Node *new_node = new Node(val);
    return insertAfter(node, new_node);
}

IntList::Node* IntList::pushBack(int val)
{
    Node *new_node = new Node(val);
    return pushBack(new_node);
}

bool IntList::deleteNode(IntList::Node *node)
{
    if (node == nullptr)
        return false;
    delete cut(node);
    return true;
}

IntList::Node *IntList::cut(IntList::Node *node)
{
    if (node == nullptr)
        return node;
    if (node == head)
    {
        head = head->next();
        return node;
    }
    Node *tmp = head;
    while (tmp->next() != node && tmp->next() != nullptr) //searching node
        tmp = tmp->next();

    if (tmp->next() != nullptr)
        tmp->_next = node->next();

    return node;
}

IntList *IntList::splitByNumber(int number)
{
    IntList *res = new IntList();
    Node *tmp = head;

    while (tmp != nullptr && tmp->getData() <= number) // check first element
    {
        head = tmp->next();
        res->pushBack(tmp);
        tmp = head;
    }

    Node *tmp1 = tmp;
    if (tmp != nullptr)
        tmp = tmp->next();

    while (tmp != nullptr)
    {
        if (tmp->getData() <= number)
        {
            tmp1->_next = tmp->next(); //cut from the list
            res->pushBack(tmp);
        }

        tmp1 = tmp;
        tmp = tmp->next();
    }

    return res;
}

IntList::Node *IntList::getNode(int number)
{
    Node *tmp = head;
    for (int i = 0; i < number && tmp != nullptr; i++)
        tmp = tmp->next();
    return tmp;
}
