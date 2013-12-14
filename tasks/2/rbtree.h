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

    Node *createChild(const Type &val, Node* parent);

    void rotateLeft(Node *x);

    void rotateRight(Node *x);

    void balanceInsertion(Node *x);

    void balanceDeletion(Node *x);

    void insertNode(Type key);

    Node * removeMin(Node *t); // removes minimal value from tree

    void deleteNode(Node *t);


    void print(Node* t, int level);

    Node* findNode(Type val);

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
       insertNode(val);
    }
    bool find(Type val)
    {
        return findNode(val) != nullptr;
    }
    void remove(Type val)
    {
        deleteNode(findNode(val));
    }
    void print()
    {
        print(root,0);
    }
};

//-------------------

template<class Type>
typename RBTree<Type>::Node *RBTree<Type>::createChild(const Type &val, Node* parent)
{
    Node *node = new Node(val, parent);
    if (root == nil)
    {
        root = node;
        node->color = BLACK;
    }
    node->left = node->right = nil;
    if (parent == nullptr)
    {
        node->parent = nil;
        return node;
    }

    if(val < parent->key)
        parent->left = node;
    else
        parent->right = node;

    return node;
}

template<class Type>
void RBTree<Type>::rotateLeft(Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != nil)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nil)
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

template<class Type>
void RBTree<Type>::rotateRight(Node *x)
{
    Node *y = x->left;

    x->left = y->right;
    if (y->right != nil)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == nil)
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

template<class Type>
void RBTree<Type>::balanceInsertion(Node *x)
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

template<class Type>
void RBTree<Type>::balanceDeletion(Node *x)
{
    // deleted node was BLACK => black-height was changed, fix it
    // count x like 2 BLACK nodes

    while (x != root && x->color == BLACK)
    {
        if (x->isLeftChild())
        {
            Node* brother = x->parent->right;

            if (brother->color == RED)
            {
                // make brother BLACK-colored
                brother->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                brother = x->parent->right;
            }

            if (brother->left->color == BLACK &&
                brother->right->color == BLACK)
            {
                // make brother RED, it doesn't need be BLACK
                // & remove virtual BLACK-color from x
                brother->color = RED;
                // go up or (make parent BLACK & finish)
                x = x->parent;
            }
            else
            {
                if (brother->right->color == BLACK)
                {
                    // make brother BLACK with RED right child
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rotateRight(brother);
                    brother = x->parent->right;
                }

                // brother is BLACK with RED right child
                // remove virtual BLACK-color from x
                brother->color = x->parent->color;
                x->parent->color = BLACK;
                brother->right->color = BLACK;
                rotateLeft(x->parent);

                x = root; // finish

            }
        }
        else // x -- right-child
        {
            Node* brother = x->parent->left;

            if (brother->color == RED)
            {
                brother->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                brother = x->parent->left;
            }

            if (brother->left->color == BLACK &&
                brother->right->color == BLACK)
            {
                brother->color = RED;
                x = x->parent;
            }
            else
            {
                if (brother->left->color == BLACK)
                {
                    brother->right->color = BLACK;
                    brother->color = RED;
                    rotateLeft(brother);
                    brother = x->parent->left;
                }

                brother->color = x->parent->color;
                x->parent->color = BLACK;
                brother->left->color = BLACK;

                rotateRight(x->parent);
                x = root;
            }
        }
    }

    x->color = BLACK;
}

template<class Type>
void RBTree<Type>::insertNode(Type key)
{
    Node *current = root, *parent = nullptr, *node;

    while (current != nil) // find parent of new node
    {
        parent = current;
        if (key == current->key)
            return;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    node = createChild(key, parent); //insert

    balanceInsertion(node);
}

template<class Type>
void RBTree<Type>::deleteNode(Node *t)
{

    Node *deleted = t;

    if (t->left != nil && t->right != nil)
    {
        Node* pred = t->right;
        while (pred->left != nil) // finding node with nil-child
            pred = pred->left;
    }


   Node *child;

   // t has only 1 child
   if (deleted->left == nil)
       child = deleted->right;
    else
       child = deleted->left;

   child->parent = deleted->parent; // for case, when child is nil

   if (deleted->parent == nil)
       root = child;
   else if (deleted->isLeftChild())
        deleted->parent->left = child;
   else
        deleted->parent->right = child;

   if (t != deleted)
       t->key = deleted->key;


    if (deleted->color == BLACK)    // restore RB-properties
        balanceDeletion(child);

    delete deleted;


}


template<class Type>
void RBTree<Type>::print(Node* t, int level)
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

template<class Type>
typename RBTree<Type>::Node * RBTree<Type>::findNode(Type val)
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

#endif // RBTREE_H
