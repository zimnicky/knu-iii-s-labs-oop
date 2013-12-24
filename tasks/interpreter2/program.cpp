#include "program.h"

namespace interpreter
{

Program::Program()
{
    in = &cin;
    out = &cout;
    err = &cerr;
    FunctionArguments args;
    args.resize(1);
    addStdFunction("print", stdfunc_print, args);

    args.resize(1);
    args[0].ref = true;
    addStdFunction("get", stdfunc_input, args);
}

bool Program::hasErrors()
{
    return errors.size() > 0;
}

vector<string> Program::getErrors()
{
    return errors;
}

bool Program::hasWarnings()
{
    return warnings.size() > 0;
}

vector<string> Program::getWarnings()
{
    return warnings;
}

void Program::addError(string msg)
{
    errors.push_back(msg);
}

void Program::addWarning(string msg)
{
    warnings.push_back(msg);
}

void Program::addFunction(Function func)
{
    functions.push_back(func);
}


Value Program::assignValue(OperationNode *node, Variables &variables)
{
    Value val = calcExpr(node->right, variables);
    if (val.getType()== valError)
        return val;
    Value var = calcExpr(node->left, variables);
    if (var.getType() == valError)
        return var;
    switch (node->operation[0]) {
    case '+':
        var = var + val;
        break;
    case '-':
        var = var - val;
        break;
    case '*':
        var = var * val;
        break;
    case '/':
        var = var / val;
        break;
    case '=':
        var = val;
        break;
    default:
        var = Value::error("unknown operator '" + node->operation + "'");
        break;
    }
    if (var.getType() != valError)
        variables.setValue(reinterpret_cast<VariableNode*>(node->left)->name, var);
    return var;
}

Value Program::calcOperationUnary(OperationNode *node, Variables &variables)
{
    if (node->left == 0)
        return Value::error("operand for unary operation missed");
    Value val = calcExpr(node->left, variables);
    if (val.getType() == valError)
        return val;
    switch (node->operation[0]) {
    case '+':
        return val;
    case '-':
        return -val;
    case '!':
        return !val;
    default:
        return Value::error("unknown operator '" + node->operation + "'");
    }
}

Value Program::calcOperationBinary(OperationNode *node, Variables &variables)
{
    if (node->left == 0 || node->right == 0)
        return valError;
    Value a = calcExpr(node->left, variables);
    Value b = calcExpr(node->right, variables);
    if (a.getType() == valError)
        return a;
    if (b.getType() == valError)
        return b;
    if (node->right->type == ntVariable && a.getType() == valUndefined)
        addError("Variable \"" +reinterpret_cast<VariableNode*>(node->right)->name + "\" is undefined"/*, node->right*/);

    if (operations.isAssignment(node->operation)) {
        return assignValue(node, variables);
    } else if (node->left->type == ntVariable && a.getType() == valUndefined) {
        addError("Variable \"" +reinterpret_cast<VariableNode*>(node->left)->name + "\" is undefined"/*, node->left*/);
    }
    if (node->operation == "+")
        return a + b;
    if (node->operation == "-")
        return a - b;
    if (node->operation == "*")
        return a * b;
    if (node->operation == "/")
        return a / b;
    if (node->operation == ">")
        return a > b;
    if (node->operation == ">=")
        return a >= b;
    if (node->operation == "<=")
        return a <= b;
    if (node->operation == "<")
        return a > b;
    if (node->operation == "!=")
        return a != b;
    if (node->operation == "==")
        return a == b;


    return Value::error("unknown operator '" + node->operation + "'");
}


Value Program::calcExpr(Node *node, Variables &variables)
{
    Value val;
    switch (node->type) {
    case ntNumber:
        val = reinterpret_cast<NumberNode*>(node)->val;
        break;
    case ntString:
        val = reinterpret_cast<StringNode*>(node)->val;
        break;
    case ntVariable: {
        val = variables.getValue(reinterpret_cast<VariableNode*>(node)->name);
        break;
    }
    case ntFuncCall: {
        Function func = getFuctionByName(reinterpret_cast<FuncCallNode*>(node)->name);
        if (!func.empty())
            val = func.exec(reinterpret_cast<FuncCallNode*>(node)->arguments, variables);
        else
            val = Value::error("unknown function");
        break;
    }
    case ntOperation_unary: {
        val = calcOperationUnary(reinterpret_cast<OperationNode*>(node), variables);
        break;
    }
    case ntOperation_binary: {
        val = calcOperationBinary(reinterpret_cast<OperationNode*>(node), variables);
        break;
    }
    default:
        break;
    }
    if (!hasErrors() && val.getType() == valError)
        addError(val.toString()/*, node*/);
    return val;
}

Program::Function Program::getFuctionByName(string name)
{
    for (int i = functions.size() - 1; i >= 0; i--)
        if (functions[i].name == name)
            return functions[i];
    return Function(0);
}

int Program::getFuctionNumberByName(string name)
{
    for (int i = functions.size() - 1; i >= 0; i--)
        if (functions[i].name == name)
            return i;
    return -1;
}

Value Program::Function::exec(vector<Node*> args, Variables &variables)
{
    if (args.size() > arguments.size())
        return Value::error("too much arguments for function '" + name + "'");
    vector<Value> arg;
    Value val;
    bool error = false;
    for (unsigned int i = 0; i < args.size() && !error; i++) {
        if (arguments[i].ref && args[i]->type != ntVariable) {
            return Value::error("argument for function '" + name + "' '" + arguments[i].name + "' must be a variable");
        }
        val = program->calcExpr(args[i], variables);
        error = (val.getType() == valError);
        arg.push_back(val);
    }
    if (!error) {
        val = exec(arg);
        for (unsigned int i = 0; i < arguments.size(); i++) {
            if (arguments[i].ref) {
                variables.setValue(reinterpret_cast<VariableNode*>(args[i])->name, arg[i]);
            }
        }
    }
    return val;
}

Value Program::Function::exec(vector<Value> &args)
{
    bool correct = arguments.size() >= args.size();
    for (unsigned int i = args.size(); i < arguments.size() && correct; i++) {
        correct = arguments[i].isdef_val;
        args.push_back(arguments[i].def_val);
    }
    if (!correct)
        return Value::error("not correct arguments for function '" + name + "'");

    if (standart)
        return stdfunc(program, args);

    Variables variables;
    for (unsigned int i = 0; i < args.size(); i++) {
        variables.setValue(arguments[i].name, args[i]);
    }

    Node *node = root;
    Value returnVal;
    bool finish = false;
    while (node != 0 && !finish) {
        switch (node->type) {
        case ntReturn:
            returnVal =  program->calcExpr(reinterpret_cast<ReturnNode*>(node)->expr, variables);
            finish = true;

            break;
        case ntIf:
        {
            IfNode *tmp = reinterpret_cast<IfNode*>(node);
            if (program->calcExpr(tmp->expr, variables).toInt() != 0)
                node = tmp->yes;
            else
                node = tmp->no;
            break;
        }
        default:
            program->calcExpr(node, variables);
            node = node->next;
            break;
        }
    }

    for (unsigned int i = 0; i < arguments.size(); i++) {
        if (arguments[i].ref)
            args[i] = variables.getValue(arguments[i].name);
    }
    return returnVal;
}

void Program::addStdFunction(string name, StdFunc func, FunctionArguments &arguments)
{
    Function f(this);
    f.name = name;
    f.standart = true;
    f.stdfunc = func;
    f.arguments = arguments;
    functions.push_back(f);
}

Value Program::stdfunc_print(Program *pr, vector<Value> &args)
{
    for (unsigned int i = 0; i < args.size(); i++) {
        switch (args[i].getType()) {
        case valNumber:
            (*(*pr).out) << args[i].toDouble() << endl;
            break;
        case valString:
            (*(*pr).out) << args[i].toString() << endl;
            break;
        case valError:
            (*(*pr).err) << args[i].toString() << endl;
            break;
        case valUndefined:
            (*(*pr).out) << "<undefined>" << endl;
            break;
        default:
            break;
        }
    }
    return Value();
}

Value Program::stdfunc_input(Program *pr, vector<Value> &args)
{
    for (unsigned int i = 0; i < args.size(); i++) {
        string tmp;
        (*(*pr).in) >> tmp;
        int intval = 0;
        bool can = true;
        int t = 0;
        while (can && tmp.size() > t)
        {
            can = tmp[t] >= '0' && tmp[t] <= '9';
            if (can)
                intval = intval*10 + tmp[t] - '0';
            t++;
        }
        if (can)
            args[i] = intval;
        else
            args[i] = tmp;

    }
    return Value();
}

void Program::setStdin(istream *i)
{
    in = i;
}

void Program::setStdOut(ostream *o)
{
    out = o;
}

void Program::setStdErr(ostream *e)
{
    err = e;
}

int Program::execute()
{
    vector<Value> args;
    return getFuctionByName("main").exec(args).toInt();
}

void Program::print()
{
    for (unsigned int i = 0; i < functions.size(); i++) {
        if (!functions[i].standart) {
            cout << functions[i].name << "(";
            if (functions[i].arguments.size() > 0) {
                cout << functions[i].arguments[0].name;
                for (unsigned int j = 1; j < functions[i].arguments.size(); j++)
                    cout << "," << functions[i].arguments[j].name;
            }
            cout << ")" << endl;
            print(functions[i].root, 0);
            cout << endl;
        }
    }
}

void Program::print(Node *node, int level)
{
    if (node == 0)
        return;
    for (int i = 1; i <= level; i++)
        cout << "    ";
    while (node != 0) {
        switch (node->type) {
        case ntOperation_binary:
            cout << reinterpret_cast<OperationNode*>(node)->operation << endl;
            print(reinterpret_cast<OperationNode*>(node)->left, level + 1);
            print(reinterpret_cast<OperationNode*>(node)->right, level + 1);
            break;
        case ntOperation_unary:
            cout << reinterpret_cast<OperationNode*>(node)->operation << endl;
            print(reinterpret_cast<OperationNode*>(node)->left, level + 1);
            break;
        case ntNumber:
            cout << reinterpret_cast<NumberNode*>(node)->val << endl;
            break;
        case ntString:
            cout << '"' << reinterpret_cast<StringNode*>(node)->val << '"' << endl;
            break;
        case ntVariable:
            cout << reinterpret_cast<VariableNode*>(node)->name << endl;
            break;
        case ntFuncCall:
            cout << "func " << reinterpret_cast<FuncCallNode*>(node)->name << endl;
            for (unsigned int i = 0; i < reinterpret_cast<FuncCallNode*>(node)->arguments.size(); i++)
                print(reinterpret_cast<FuncCallNode*>(node)->arguments[i], level + 2);
            break;
        case ntReturn:
            cout << "return ";
            print(reinterpret_cast<ReturnNode*>(node)->expr, level);
            break;
        default:
            break;
        }
        node = node->next;
        if (node != 0)
            cout << ";" << endl;
    }
}

bool Program::checkRecursion()
{
    dfs_visited.resize(functions.size());
    return checkRecursion_dfs(getFuctionNumberByName("main"));
}

bool Program::checkRecursion_dfs(int func)
{
    if (dfs_visited[func] == true)
        return true;
    dfs_visited[func] = true;
    Node* node = functions[func].root;
    while (node != 0)
    {
        if (node->type == ntFuncCall)
        {
            if (checkRecursion_dfs(getFuctionNumberByName(reinterpret_cast<FuncCallNode*>(node)->name)))
                return true;
        }
        else if (node->type == ntReturn)
                    return  checkRecursion(reinterpret_cast<ReturnNode*>(node)->expr);
        else if (checkRecursion(node))
                return true;
        node = node->next;
    }
    return false;
}

bool Program::checkRecursion(Node *node)
{
    if (node->type == ntFuncCall)
    {
        if (checkRecursion_dfs(getFuctionNumberByName(reinterpret_cast<FuncCallNode*>(node)->name)))
            return true;
    }
    else if (node->type == ntOperation_binary)
    {
        bool t = checkRecursion(reinterpret_cast<OperationNode*>(node)->left);
        if (!t)
            t = checkRecursion(reinterpret_cast<OperationNode*>(node)->right);
        if (t)
            return true;
    }
    else if (node->type == ntOperation_unary)
    {
        return checkRecursion(reinterpret_cast<OperationNode*>(node)->left);
    }
    return false;
}

}
