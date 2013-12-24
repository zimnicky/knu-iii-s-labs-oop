#ifndef PARSETREE_H
#define PARSETREE_H

#include <string>
#include <vector>

#include "value.h"
#include "operations.h"
#include "variablestorage.h"

using namespace std;


namespace interpreter {

typedef Variable_Storage<Value> Variables;

class ParseTree
{
public:
    enum NodeType {ntUndefined, ntOperation_binary, ntOperation_unary, ntNumber,
                   ntString, ntVariable, ntReturn, ntFuncCall
                  };
    struct Node {
        NodeType type;
        Node * next;
        Node() {
            type = ntUndefined;
            next = 0;
        }
    };
    struct NumberNode: public Node {
        double val;
        NumberNode() {
            val = 0;
            type = ntNumber;
        }
        NumberNode(double number) {
            val = number;
            type = ntNumber;
        }
    };
    struct StringNode: public Node {
        string val;
        StringNode() {
            type = ntString;
        }
        StringNode(string str) {
            val = str;
            type = ntString;
        }
    };
    struct VariableNode: public Node {
        string name;
        VariableNode() {
            type = ntVariable;
        }
        VariableNode(string s) {
            name = s;
            type = ntVariable;
        }
    };
    struct OperationNode:public Node {
        Node *left, *right;
        string operation;
        OperationNode(bool unary = false) {
            type = unary?ntOperation_unary:ntOperation_binary;
            operation[0] = operation[1] = 0;
            left = right = 0;
        }
        OperationNode(string op, bool unary = false) {
            type = unary?ntOperation_unary:ntOperation_binary;
            operation = op;
            left = right = 0;
        }
        OperationNode(char op, bool unary = false) {
            type = unary?ntOperation_unary:ntOperation_binary;
            operation = op;
            left = right = 0;
        }
    };
    struct ReturnNode:public Node {
        Node * expr;
        ReturnNode() {
            type = ntReturn;
        }
    };
    struct FuncCallNode: public Node {
        vector<Node*> arguments;
        string name;
        FuncCallNode() {
            type = ntFuncCall;
        }
    };

    bool thereare_errors;
    string error_msg;

    void clearErrors();
    void error(string msg, Node *node);
    string getErrorMesage();


    typedef Value (*FuncExecuter)(ParseTree::FuncCallNode *);
    FuncExecuter execute = 0;
    Operations *operations;
    ParseTree(FuncExecuter, Operations*);
    Value assignValue(OperationNode *node, Variables &variables);
    Value calcOperationUnary(OperationNode *node, Variables &variables);
    Value calcOperationBinary(OperationNode *node, Variables &variables);
    Value calcExpr(Node *node, Variables &variables);
};

};

#endif // PARSETREE_H
