#include "btree.h"

BTree::BTree()
{
    root = new Node();
    power = 2;
    fullPower = 3;
}

void BTree::setPower(uint power)
{
    this->power = power;
    fullPower = 2*power - 1;
}

pair<BTree::Node*, uint> BTree::find(Node* node, int key)
{
    int i;
    for (i = 0; i < node->countKeys() && key > node->key(i); i++)
    {}


    if (i < node->countKeys() && key == node->key(i))               // key was found
        return make_pair(node, i);

    if (node->isLeaf())                  // key wasn't found
        return make_pair(nullptr, 0);

    return find(node->child(i), key);
}


void BTree::splitChild(Node* node, uint childNum)
{
    Node* child = node->child(childNum);
    Node* newNode = new Node();

    for (int i = power; i < fullPower; i++)  // move power - 1 back keys from the child to the newNode
        newNode->appendKey(child->key(i));

    if (!child->isLeaf())
        for (int i = power; i <= fullPower; i++)  // move power - 1 back children from the child to the newNode
            newNode->appendChild(child->child(i));

    child->removeKeys(power);
    child->removeChildren(power);

    node->insertChild(newNode, childNum+1);               // move median-child to the parent
    node->insertKey(child->key(power - 1), childNum);   // move median-key   to the parent

}


void BTree::insert(int key)
{
    if (find(key))
        return;

    if (root->countKeys() == fullPower) // root is complete, grow up the tree
    {
        Node* newNode = new Node();
        newNode->appendChild(root);
        root = newNode;
        splitChild(root, 0);
    }

    insertToIncomplete(root, key);
}


void BTree::insertToIncomplete(Node* node, int key)
{
    int place;
    for (place = node->countKeys() - 1; place >= 0 && key < node->key(place); place--) {} // finding place of key

    place++;

    if (node->isLeaf())
        node->insertKey(key, place);
    else
    {
        if (node->child(place)->countKeys() == fullPower)
        {
            splitChild(node, place);
            if (key > node->key(place)) // select child for inserting
                place++;
        }

        insertToIncomplete(node->child(place), key);
    }
}


void BTree::print(ostream &out, Node* node, int level)
{
    for (int i = 0; i < level; i++)
        out << "    ";

    out << "keys: ";

    for (int i = 0; i < node->countKeys(); i++)
        out << node->key(i) << " ";

    out << endl;

    for (int i = 0; i < level; i++)
        out << "    ";

    if (node->isLeaf())
    {
        out << "leaf" << endl;
        return;
    }

    out << "children: " << endl;

    for (int i = 0; i < node->countChildren(); i++)
    {
        print(out, node->child(i), level + 1);
        for (int j = 0; j < level; j++)
            out << "    ";
        out << "------------" << endl;
    }

    out << endl;

}

void BTree::print(ostream &out)
{
    print(out, root, 0);
}


int BTree::maxKey(Node* node)
{
    if (node->isLeaf())
        return node->key(node->countKeys() - 1);
    return maxKey(node->child(node->countChildren() - 1));
}

int BTree::minKey(Node* node)
{
    if (node->isLeaf())
        return node->key(0);
    return minKey(node->child(0));
}

void BTree::mergeNodes(Node* a, int middleKey, Node* b)
{
    a->appendKey(middleKey);
    for (int i = 0; i < b->countKeys(); i++)
    {
        a->appendKey(b->key(i));
        if (!b->isLeaf())
            a->appendChild(b->child(i));
    }

    if (!b->isLeaf())
        a->appendChild(b->child(b->countChildren() - 1));
}

void BTree::remove(Node* node, int key)
{
    int i;
    for (i = 0; i < node->countKeys() && key > node->key(i); i++)
    {}

    if (key == node->key(i))
    {
        if (node->isLeaf())
        {
            node->removeKey(i);
            return;
        }

        Node *prev = node->child(i);
        Node *next = (i < node->countKeys() - 1)?node->child(i+1):nullptr;

        if (prev->countKeys() >= power) // can remove from left neighbour
        {
            int k1 = maxKey(prev);
            remove(prev, k1);
            node->key(i) = k1;
            return;
        }

        if (next && next->countKeys() >= power) // can remove from  right neighbour
        {
            int k1 = minKey(next);
            remove(next, k1);
            node->key(i) = k1;
            return;
        }

        // prev & next nodes has only power-1 keys, merge to 1 node
        mergeNodes(prev, node->key(i), next);
        node->removeChild(i+1);
        node->removeKey(i);
        delete next;

        remove(prev, key);
    }
    else
    {
        Node* child = node->child(i);
        if (child->countKeys() >= power) //can remove right now
        {
            remove(child, key);
            return;
        }

        Node *prev = (i > 0)?node->child(i-1):nullptr;
        Node *next = (i < node->countKeys() - 1)?node->child(i+1):nullptr;

        if (prev && prev->countKeys() >= power)
        {
            // right-rotation
            child->insertKey(node->key(i-1), 0);
            child->insertChild(prev->child(prev->countChildren() - 1), 0);

            node->key(i-1) = prev->key(prev->countKeys() - 1);

            prev->removeKey(prev->countKeys() - 1);
            prev->removeChild(prev->countChildren() - 1);

            remove(child, key);
            return;
        }

        if (next && next->countKeys() >= power)
        {
            // left-rotation
            child->appendKey(node->key(i));
            child->appendChild(next->child(0));

            node->key(i) = next->key(0);

            next->removeKey(0);
            next->removeChild(0);

            remove(child, key);
            return;
        }

        // no neighbours with excess key
        if (prev)
        {
            mergeNodes(prev, node->key(i-1), child);
            node->removeChild(i);
            node->removeKey(i-1);
            delete child;

            remove(prev, key);
        }
        else
        {
            mergeNodes(child, node->key(i), next);
            node->removeChild(i+1);
            node->removeKey(i);
            delete next;

            remove(child, key);
        }
    }
}


void BTree::remove(int key)
{
    if (find(key))
        remove(root, key);
}

bool BTree::find(int key)
{
    return find(root, key).first != nullptr;
}
