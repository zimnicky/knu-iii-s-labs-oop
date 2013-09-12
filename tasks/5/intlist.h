#ifndef INTLIST_H
#define INTLIST_H

class IntList
{
public:
    class Node
    {
        friend class IntList;
    private:
        int data;
        Node *_next;
        void insert(Node *node); //inserts node after this
    public:
        Node(int data){this->data = data; _next = nullptr;}
        int getData() const { return data;}
        void setData(int data){this->data = data;}
        Node *next(){return _next;} // returns next element of the list
    };

    IntList();
    ~IntList();

    Node *insertBefore(Node *node, Node *new_node);
    Node *insertAfter(Node *node, Node *new_node);
    Node *pushBack(Node *new_node);

    Node *insertBefore(Node *node, int val);
    Node *insertAfter(Node *node, int val);
    Node *pushBack(int val);

    bool deleteNode(Node *node); // true if OK
    Node *cut(Node *node); // removes node from the list and returns it

    IntList *splitByNumber(int number);

    Node *getNode(int number); // returns <number>th node

    Node *begin(){ return head;}
private:
    Node *head;
};

#endif // INTLIST_H
