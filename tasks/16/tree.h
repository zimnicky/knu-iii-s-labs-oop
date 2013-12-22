#ifndef TREE_H
#define TREE_H

#include <vector>

using namespace std;

class Tree
{
protected:
    struct Node
    {
        unsigned int num;
        vector<Node*> children;
    };
    Node *root;

    int countIsomorphicSubtrees(Node *curr, Node *second);
    Node *find(Node *node, unsigned int num);
    void erase(Node* node);
    static bool isEqual(Node *first, Node *second);
public:
    Tree();
    ~Tree();
    int countIsomorphicSubtrees(Tree &second);
    void addChild(unsigned int parent, unsigned int child);
};

#endif // TREE_H
