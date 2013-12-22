#include "tree.h"
#include <algorithm>

Tree::Tree()
{
    root = new Node();
    root->num = 0;
}

Tree::~Tree()
{
    erase(root);
}

void Tree::erase(Node* node)
{
    for (auto i: node->children)
        erase(i);
    delete node;
}

bool Tree::isEqual(Node *first, Node *second)
{
    if (first == nullptr && second == nullptr)
        return true;
    else if (first == nullptr || second == nullptr)
        return false;

    if (first->children.size() == 0 && second->children.size() == 0)
        return true;

    if (first->children.size() != second->children.size())
        return false;

    vector<int> order(first->children.size());

    for (size_t i = 0; i < order.size(); i++)
        order[i] = i;

    bool equal;
    do
    {
        equal = true;
        for (unsigned int i = 0; i < order.size() && equal; i++)
            equal = isEqual(first->children[i], second->children[order[i]]);
    }
    while (!equal && next_permutation(order.begin(), order.end()));

    return equal;
}


int Tree::countIsomorphicSubtrees(Node *curr, Node *second)
{
    int count = 0;
    if (isEqual(curr, second))
        return 1;

    for (Node* i: curr->children)
        count += countIsomorphicSubtrees(i, second);

    return count;
}

int Tree::countIsomorphicSubtrees(Tree &second)
{
    return countIsomorphicSubtrees(root, second.root);
}

Tree::Node * Tree::find(Node* node, unsigned int num)
{
    if (node->num == num)
        return node;

    for (Node* i: node->children)
    {
        Node *res = find(i, num);
        if (res != nullptr)
            return res;
    }

    return nullptr;
}

void Tree::addChild(unsigned int parent, unsigned int child)
{
    Node *node = find(root, parent);
    Node *node2 = new Node();
    node2->num = child;
    node->children.push_back(node2);
}
