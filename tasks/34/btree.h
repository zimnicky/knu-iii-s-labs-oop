#ifndef BTREE_H
#define BTREE_H

#include <vector>
#include <iostream>

using namespace std;

typedef unsigned int uint;

class BTree
{
protected:
    struct Node{
    protected:
        vector<int> keys;
        vector<Node*> children;
    public:
        bool isLeaf() const { return children.size() == 0;}
        Node* child(int i) { return children[i];}
        void appendChild(Node* child){ children.push_back(child);}
        void insertChild(Node* child, int place){children.insert(children.begin()+place, child);}
        void removeChildren(uint count){children.resize((children.size() > count)?children.size() - count:0);}
        void removeChild(uint num){children.erase(children.begin()+num);}
        int countChildren()const{return children.size();}

        int countKeys() const { return keys.size();}
        void insertKey(int key, int place){keys.insert(keys.begin()+place, key);}
        void removeKeys(uint count){keys.resize((keys.size() > count)?keys.size() - count:0);}
        void removeKey(uint num){keys.erase(keys.begin()+num);}
        int& key(int i) { return keys[i];}
        void appendKey(int key){keys.push_back(key);}
    };


    Node* root;
    int power;         // minimal power of node
    int fullPower;      // maximal power of node


    void splitChild(Node* node, uint childNum);      // splits child(must have 2*power - 1 keys) to 2 nodes(with power - 1 keys)
    void insertToIncomplete(Node* node, int key);   // inserts key to node(mast be incomplete)

    pair<Node*, uint> find(Node* node, int key); // returns node & number of key in it

    void remove(Node* node, int key);               // removes key from the tree

    int minKey(Node* node);        // returns minimum key in subtree
    int maxKey(Node* node);        // returns maximum key in subtree

    void mergeNodes(Node* a, int middleKey, Node* b);  // merges a, middleKey & b, result is a

    void print(ostream &out, Node* node, int level);
public:
    BTree();
    void setPower(uint power);
    void insert(int key);
    void remove(int key);
    bool find(int key);
    void print(ostream &out);
};

#endif // BTREE_H
