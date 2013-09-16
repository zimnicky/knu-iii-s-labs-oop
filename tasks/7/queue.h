#ifndef QUEUE_H
#define QUEUE_H

template <class Type>
class Queue
{
    struct Node
    {
        Type data;
        Node *next, *prev;
        Node(const Type &val){ data = val; next = prev = nullptr;}
    };

    Node *head, *tail;

    void insertionSort(bool (*cmp)(const Type &a, const Type &b));
    void qSort(Node *l, Node* r, bool (*cmp)(const Type &a, const Type &b));

public:
    enum class SortMethod{QSORT, INSERTION};
    Queue() { head = tail = nullptr; }
    ~Queue(){ while (head != nullptr) pop();}

    void push(const Type &val);
    Type top() const { return (head == nullptr)? Type(): head->data;}
    void pop();
    bool isEmpty() const {return tail == nullptr;}

    //sorts the queue. params: method, compare function
    void sort(SortMethod method, bool (*cmp)(const Type &a, const Type &b) = nullptr);
};

//****************************************************************************

template <class Type>
void Queue<Type>::push(const Type &val)
{
    Node *new_node = new Node(val);
    if (tail == nullptr) // queue is empty
        head = tail = new_node;
    else
    {
        tail->next = new_node;
        new_node->prev = tail;
        tail = tail->next;
    }
}

template <class Type>
void Queue<Type>::pop()
{
    Node *tmp = head;
    if (head != nullptr)
    {
        head = head->next;
        if (tail == tmp) // it is last element
            tail = nullptr;
        else
            head->prev = nullptr;
        delete tmp;
    }
}

template <class Type>
void Queue<Type>::sort(SortMethod method, bool (*cmp)(const Type &a, const Type &b))
{
    if (cmp == nullptr)
        cmp = [](const Type &a, const Type &b){return a < b;}; // standart compare function
    switch (method) {
    case SortMethod::INSERTION:
        insertionSort(cmp);
        break;
    case SortMethod::QSORT:
        qSort(head, tail, cmp);
        break;
    default:
        break;
    }
}

template <class Type>
void Queue<Type>::insertionSort(bool (*cmp)(const Type &a, const Type &b))
{
    for (Node *i = head; i != nullptr; i = i->next)
    {
        Node *j = i;
        Type el = i->data;
        while (j != head && cmp(el, j->prev->data)) // searching place
        {
            j->data = j->prev->data;
            j = j->prev;
        }
        j->data = el; // insert
    }
}

template <class Type>
void Queue<Type>::qSort(Node *l, Node* r, bool (*cmp)(const Type &a, const Type &b))
{
    // compare function for pointers
    bool (*eqless)(Node *, Node *) = [](Node *a, Node *b){return a == b || a->next == b;};

    if (r == nullptr || l == nullptr || eqless(r, l))
        return;

    Node *i = l->prev, *j = r;
    Type et = r->data; // reference element
    Type tmp;

    for (;;)
    {
        do {i = (i)?i->next:l;}
        while(cmp(i->data, et) == true);

        do {j = j->prev; if (j == l) break;}
        while (cmp(j->data, et) == false);

        if (eqless(j, i)) break;

        //swap i, j
        tmp = i->data;
        i->data = j->data;
        j->data = tmp;
    }

    //swap i, r
    tmp = i->data;
    i->data = r->data;
    r->data = tmp;

    qSort(l, i->prev, cmp);
    qSort(i->next, r, cmp);

}

#endif // QUEUE_H
