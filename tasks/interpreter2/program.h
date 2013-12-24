#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <string>

#include "value.h"
#include "tree.h"
#include "variablestorage.h"
#include "operations.h"


namespace interpreter
{

using std::vector;
using std::string;

class Program
{
public:
    struct FunctionArgument {
        string name;
        Value def_val;
        bool isdef_val;
        bool ref;
    };
    typedef Value (*StdFunc)(Program *, vector<Value> &);
    typedef vector<FunctionArgument> FunctionArguments;
    typedef Variable_Storage<Value> Variables;
    struct Function
    {
        Program *program;
        Node* root;
        string name;
        FunctionArguments arguments;
        bool standart;
        Program::StdFunc stdfunc;
        Value exec(vector<Node*>, Variables&);
        Function(Program *program) {
            root = 0;
            this->program = program;
            standart = false;
        }
        bool empty() {
            return root == 0 && !standart;
        }
        Value exec(vector<Value> &args);
    };
    Program();
    int execute();
    bool hasErrors();
    bool hasWarnings();
    vector<string> getErrors();
    vector<string> getWarnings();
    void addError(string msg);
    void addWarning(string msg);
    void addFunction(Function func);
    bool checkRecursion();
    void print();
    void print(Node *node, int level);
private:
        vector<string> errors;
        vector<string> warnings;
        Operations operations;
        vector<Function> functions;

        istream *in;
        ostream *out;
        ostream *err;

        vector<bool> dfs_visited;

        Value assignValue(OperationNode *node, Variables &variables);
        Value calcOperationUnary(OperationNode *node, Variables &variables);
        Value calcOperationBinary(OperationNode *node, Variables &variables);
        Value calcExpr(Node *node, Variables &variables);

        Function getFuctionByName(string name);
        int getFuctionNumberByName(string name);

        static Value stdfunc_print(Program *pr, vector<Value> &args);
        static Value stdfunc_input(Program *pr, vector<Value> &args);
        void addStdFunction(string name, StdFunc func, FunctionArguments &arguments);

        void setStdin(istream *i);
        void setStdOut(ostream *o);
        void setStdErr(ostream *e);

        bool checkRecursion_dfs(int func);
        bool checkRecursion(Node *node);
};

}

#endif // PROGRAM_H
