#ifndef AVLTREE_H
#define AVLTREE_H

#include <cmath>

using namespace std;


template<class Type>
class AvlTree
{
private:
    struct Node{
        Node *left;
        Node *right;
        int h;
        Type key;
        Node()
        {
            left = nullptr;
            right = nullptr;
            h = 0;
            key = Type();
        }
        Node(Type data)
        {
            left = nullptr;
            right = nullptr;
            h = 1;
            this->key = data;
        }
        int getBalance() // distance between children's heights
        {
            int hl = (left == nullptr)?0:left->h;
            int hr = (right == nullptr)?0:right->h;
            return hr - hl;
        }
        void calcHeight()
        {
            int hl = (left == nullptr)?0:left->h;
            int hr = (right == nullptr)?0:right->h;
            h = max(hl, hr)+1;
        }
    };

    Node *createChild(const Type &val, Node* parent)
    {
        Node *node = new Node(val);
        if (root == nullptr)
            root = node;
        node->left = node->right = nullptr;
        if (parent == nullptr)
            return node;

        if(val < parent->key)
            parent->left = node;
        else
            parent->right = node;

        return node;
    }

    Node* rotateRight(Node *tree)
    {
        Node *t = tree->left;
        tree->left = t->right;
        t->right = tree;
        tree->calcHeight();
        t->calcHeight();
        return t;
    }

    Node* rotateLeft(Node *tree)
    {
        Node *t = tree->right;
        tree->right = t->left;
        t->left = tree;
        tree->calcHeight();
        t->calcHeight();
        return t;
    }

    void balance(Node* &t)
    {
        t->calcHeight();
        if (t->getBalance() == 2) // right subtree is higher
        {
            if (t->right == nullptr || t->right->getBalance() < 0) // if needs big rotation
                t->right = rotateRight(t->right);
            t = rotateLeft(t);
        }

        if (t->getBalance() == -2) // left subtree is higher
        {
            if (t->left == nullptr || t->left->getBalance() > 0)
                t->left = rotateLeft(t->left);
            t = rotateRight(t);
        }
    }

    Node* findNode(Type val)
    {
        Node * curr = root;
        bool found = false;
        while (!found && curr != nullptr)
        {
            if (curr->key == val)
                found = true;
            else
            {
                if (val < curr->key)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
        }
        return curr;
    }

    void insertNode(Type key)
    {
        Node *current = root, *parent = nullptr, *node;

        while (current != nullptr) // find parent of new node
        {
            parent = current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        node = createChild(key, parent); //insert

        balance(node);
    }

    Node * removeMin(Node *t) // removes minimal value from tree
    {
        if (t->left == nullptr) return t->right;
        t->left = removeMin(t->left);

        balance(t);
        return t;
    }

    Node * deleteNode(Node *t, Type val)
    {
        if (t == nullptr) return t;

        if (val == t->key)
        {
            Node *l = t->left;
            Node *r = t->right;
            delete t;

            if (r == nullptr) return l;

            Node * min = r;
            while (min->left != nullptr)
                min = min->left;
            min->right = removeMin(r);
            min->left = l;

            balance(min);
            return min;
        }

        if (val < t->key)
            t->left = deleteNode(t->left, val);
        else
            t->right = deleteNode(t->right, val);

        balance(t);
        return t;
    }

    void print(Node* t, int level)
    {
        for (int i = 0; i < level; i++)
            cout << "    ";

        if (t == 0)
        {
            cout << "0" << endl;
            return;
        }

        cout << t->key << endl;
        print(t->left, level + 1);
        print(t->right, level + 1);
    }

    Node *root;

public:

    AvlTree()
    {
        root = nullptr;
    }
    void insert(Type val)
    {
        if (findNode(val) == nullptr)
            insertNode(val);
    }
    bool find(Type val)
    {
        return findNode(val) != nullptr;
    }
    void remove(Type val)
    {
        root = deleteNode(root, val);
    }
    void print()
    {
        print(root,0);
    }
};

#endif // AVLTREE_H
