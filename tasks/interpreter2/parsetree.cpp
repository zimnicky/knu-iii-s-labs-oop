#include "parsetree.h"

namespace interpreter
{

ParseTree::ParseTree(FuncExecuter ex, Operations* op)
{
    execute = ex;
    operations = op;
}

void ParseTree::clearErrors()
{
    thereare_errors = false;
    error_msg = "no errors";
}

void ParseTree::error(string msg, Node *node)
{
    if (thereare_errors)
        return;
    thereare_errors = true;
    error_msg = msg;
}

string ParseTree::getErrorMesage()
{
    return error_msg;
}

Value ParseTree::assignValue(OperationNode *node, Variables &variables)
{
    Value val = calcExpr(node->right, variables);
    if (val.getType() == valError)
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

Value ParseTree::calcOperationUnary(OperationNode *node, Variables &variables)
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

Value ParseTree::calcOperationBinary(ParseTree::OperationNode *node, Variables &variables)
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
        error("Variable \"" +reinterpret_cast<VariableNode*>(node->right)->name + "\" is undefined", node->right);

    if (operations->isAssignment(node->operation)) {
        return assignValue(node, variables);
    } else if (node->left->type == ntVariable && a.getType() == valUndefined) {
        error("Variable \"" +reinterpret_cast<VariableNode*>(node->left)->name + "\" is undefined", node->left);
    }
    if (node->operation == "+")
        return a + b;
    if (node->operation == "-")
        return a - b;
    if (node->operation == "*")
        return a * b;
    if (node->operation == "/")
        return a / b;
    return Value::error("unknown operator '" + node->operation + "'");
}


Value ParseTree::calcExpr(ParseTree::Node *node, Variables &variables)
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
        /*Function func = getFuctionByName(reinterpret_cast<FuncCallNode*>(node)->name);
        if (!func.empty())
            val = func.exec(reinterpret_cast<FuncCallNode*>(node)->arguments, variables);
        else
            val = Value::error("unknown function");
        break;*/
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
    if (!thereare_errors && val.getType() == valError)
        error(val.toString(), node);
    return val;
}


}
