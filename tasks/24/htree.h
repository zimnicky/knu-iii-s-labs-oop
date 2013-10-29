#ifndef HTREE_H
#define HTREE_H

#include <string>

using namespace std;

class HTree
{
protected:
    struct Node
    {
        char symbol;
        Node* left;
        Node* right;
        Node(char s = 0):symbol(s),left(nullptr),right(nullptr){}
    };

    Node* root;

    bool getCode(Node* node, char target, string &code);
public:
    HTree(const string &str);

    string getCode(char c);             //returns code of symbol or
    char getChar(const string &code) throw(const char *);   // returns symbol by code
};

#endif // HTREE_H
