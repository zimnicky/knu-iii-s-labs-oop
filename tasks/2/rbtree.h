#ifndef RBTREE_H
#define RBTREE_H

using namespace std;


template<class Type>
class RBTree
{
private:
    enum Color{RED, BLACK};
    struct Node{
        Node *left;
        Node *right;
        Node * parent;
        Color color;
        Type key;
        Node(Node *parent = nullptr)
        {
            left = nullptr;
            right = nullptr;
            color = RED;
            this->parent = parent;
            key = Type();
        }
        Node(const Type &data, Node *parent = nullptr)
        {
            left = nullptr;
            right = nullptr;
            color = RED;
            this->parent = parent;
            key = data;
        }
        Node *grandFather()
        {
            if (parent != nullptr)
                return parent->parent;
            return nullptr;
        }
        Node *uncle()
        {
            if (parent == nullptr || parent->parent == nullptr)
                return nullptr;
            Node *t =  parent->parent;
            if (parent == t->left)
                return t->right;
            return t->left;
        }

        bool isLeftChild()
        {
            return (parent != nullptr && parent->left == this);
        }

    };

    Node *root;
    Node *nil;

    Node *createChild(const Type &val, Node* parent)
    {
        Node *node = new Node(val, parent);
        if (root == nil)
        {
            root = node;
            node->color = BLACK;
        }
        node->left = node->right = nil;
        if (parent == nullptr)
            return node;

        if(val < parent->key)
            parent->left = node;
        else
            parent->right = node;

        return node;
    }

    void rotateLeft(Node *x)
    {
        Node *y = x->right;

        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else
        {
            if (x->isLeftChild())
                x->parent->left = y;
            else
                x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node *x)
    {
        Node *y = x->left;

        x->left = y->right;
        if (y->right != nil)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else
        {
            if (x->isLeftChild())
                x->parent->left = y;
            else
                x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }

    void balance(Node *x)
    {
        while (x != root && x->parent->color == RED)
        {
            // parent can't be red, fix it

            if (x->uncle()->color == RED)
            {
                x->parent->color = BLACK;
                x->uncle()->color = BLACK;
                x->grandFather()->color = RED;

                x = x->grandFather(); //grandfather can have red parent, check
            }
            else // uncle is BLACK
            {
                if (x->parent->isLeftChild())
                {
                   if (!x->isLeftChild())
                       rotateLeft(x); //make it left-child

                   //children of RED-node must be BLACK: recolor & rotate
                   x->parent->color = BLACK;
                   x->grandFather()->color = RED;
                   rotateRight(x->grandFather());
                }
                else // parent is right child
                {
                    if (x->isLeftChild())
                        rotateRight(x); // make it right-child

                    x->parent->color = BLACK;
                    x->grandFather()->color = RED;
                    rotateLeft(x->grandFather());
                }
            }
        }
        root->color = BLACK;
    }

    void insertNode(Type key)
    {
        Node *current = root, *parent = nullptr, *node;

        while (current != nil) // find parent of new node
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


    void print(Node* t, int level)
    {
        for (int i = 0; i < level; i++)
            cout << "    ";

        if (t == nil || t == nullptr)
        {
            cout << "0" << endl;
            return;
        }

        if (t->color == RED)
            cout << "r";
        else
            cout << "b";
        cout << "(" << t->key << ",";
        if (t->parent)
            cout << t->parent->key;
        else
            cout << 0;
        cout << ")" << endl;
        print(t->left, level + 1);
        print(t->right, level + 1);
    }

    Node* findNode(Type val)
    {
        Node * curr = root;
        bool found = false;
        while (!found && curr != nil && curr != nullptr)
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
        if (curr == nil)
            curr = nullptr;
        return curr;
    }

public:

    RBTree()
    {
        nil = new Node();
        nil->color = BLACK;
        nil->left = nil->right = nil;
        root = nil;
    }
    void insert(Type val)
    {
        //if (findNode(val) == nullptr)
            insertNode(val);
    }
    bool find(Type val)
    {
        return findNode(val) != nullptr;
    }
    void remove(Type val)
    {
        //root = deleteNode(root, val);
    }
    void print()
    {
        print(root,0);
    }
};

#endif // RBTREE_H
