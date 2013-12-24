#include "parser.h"

namespace interpreter
{

Parser::Parser()
{
    generateReservedWords();
}


Program * Parser::parseProgram(string s)
{
    curr_str = s;
    curr_index = 0;
    curr_line_index = 0;
    curr_line_num = 1;
    clearErrors();
    curr_prog = new Program();
    parseProgram();
    return curr_prog;
}

void Parser::parseProgram()
{
    Program::Function curr(curr_prog);
    while (skip(" \r\n\t")) {
        curr = getFunction();
        if (skip(" \r\n\t") && currChar() == ')')
            curr_index++;

        if (skip(" \r\n\t") && currChar() == '{') {
            curr_index++;
            curr.root = parseBlock();
            if (skip(" \r\n\t") && currChar() != '}')
                error("'}' missed");
            else
                curr_index++;
            curr_prog->addFunction(curr);
        } else {
            error("'{' missed");
        }
    }
}

Node * Parser::readSingle()
{
    Node * node = 0;
        if (isdigit(currChar())) {
            node =  new NumberNode(getNumber());
            if (skip(" \r\n\t") && (currChar() == '(' || isalpha(currChar()))) {
                error("operator missed");
            }
        } else if (isalpha(currChar())) {
            string literal = getLiteral();
            if (isReservedWord(literal)) {
                error("\""+literal + "\" is reserved word");
            } else if (currChar() == '(') {
                //parse function
                curr_index++;
                node = new FuncCallNode();
                reinterpret_cast<FuncCallNode*>(node)->name = literal;
                if (skip(" \r\n\t") && currChar() != ')') {
                    bool cont = true;
                    while (skip(" \r\n\t") && cont) {
                        reinterpret_cast<FuncCallNode*>(node)->arguments.push_back(parseExpr(0));
                        if (skip(" \r\n\t") && currChar() != ',' && currChar() != ')') {
                            error("not correct function call");
                        } else {
                            cont = currChar() != ')';
                            curr_index++;
                        }
                    }
                } else {
                    curr_index++;
                }
            } else {
                node = new VariableNode(literal);
            }
        } else if (currChar() == '"') {
            node = new StringNode(getString());
            if (skip(" \r\n\t") && (currChar() == '(' || isalnum(currChar()))) {
                error("operator missed");
            }
        } else
            error("there is something wrong");
        return node;
}

ReturnNode * Parser::readReturn()
{
    curr_index += 6; //"return"
    ReturnNode * res = new ReturnNode();
    res->expr = parseExpr(0);
    return res;
}

Node * Parser::readNext()
{
    Node * res;
    if (startsWith("return")) {
        res = readReturn();
    } else if (startsWith("if"))
    {
        res = parseIf();
    }
    else
    {
        res = parseExpr(0);
        if (canContinue() &&
                ((res->type != ntOperation_binary &&
                  res->type != ntFuncCall) ||
                 (res->type == ntOperation_binary &&
                  !isassignment(reinterpret_cast<OperationNode*>(res)->operation)))) {
            warning("statement has no effect");
        }
        if (skip(" \r\n\t") && currChar() != ';') {
            if (currChar() == ')')
                error("extra bracket found");
            else error("';' missed");
        } else
            curr_index++;
    }
    return res;
}

Node * Parser::parseIf()
{
    curr_index += 2;
    if (!skip(" \r\n\t"))
       error("unexpected end of file");
    curr_index++;
    IfNode *res = new IfNode();
    res->expr = parseExpr(0);
    curr_index++;
    if (!skip(" \r\n\t"))
       error("unexpected end of file");
    if (startsWith("{"))
        res->yes = parseBlock();
    else
        res->yes = readNext();
    if ( skip(" \r\n\t;") && startsWith("else"))
    {
        curr_index += 4;
        if (!skip(" \r\n\t"))
           error("unexpected end of file");
        if (startsWith("{"))
            res->no = parseBlock();
        else
            res->no = readNext();
        curr_index++;
    }
    else error("unexpected end of file");
    return res;
}

Node * Parser::parseExpr(int priority)
{
    if (skip(" \r\n\t")) {
        OperationNode * unary = 0;
        if (priority > operations.getMaxPriority()) {
            Node * expr = 0;
            if (isunaryoper(currChar())) {
                unary = new OperationNode(currChar(), true);
                curr_index++;
            }
            if (currChar() == '(') {
                curr_index++;
                expr = parseExpr(0);
                if (skip(" \r\n\t") && currChar() == ')')
                    curr_index++;
                else
                    error("')' missed");
            } else {
                expr = readSingle();
            }
            if (unary != 0) {
                unary->left = expr;
                expr = unary;
            }
            return expr;
        }

        Node * a = parseExpr(priority + 1);
        if (unary != 0) {
            unary->left = a;
            a = unary;
        }

        Node * b = 0;
        string op;
        OperationNode * operation;
        while (skip(" \r\n\t") && isoper(currChar())
                && priority == operations.getPriority(op = getOperation(true))) {
            skip(op);
            if (operations.isAssignment(op) && a->type != ntVariable) {
                error("lvalue required as left operand of assignment");
            } else {
                operation = new OperationNode(op);
                b = parseExpr(priority + 1);
                operation->left = a;
                operation->right = b;
                a = operation;
            }
        }
        return a;
    }
    return 0;
}

Node * Parser::parseBlock()
{
    Node * res = 0;
    Node * current = 0;
    Node * tmp;
    while (skip(" \r\n\t") && currChar() != '}') {
        if (currChar() == ';') {
            warning("extra ';'");
            skip(" \r\n;");
        }
        if (currChar() == '{') {
            curr_index++;
            tmp = parseBlock();
            if (!canContinue() && !thereare_errors)
                error("'}' missed");
            curr_index++;
        } else {
            tmp = readNext();
        }

        if (res == 0) {
            res = current = tmp;
        } else {
            current->next = tmp;
            current = tmp;
            while (current != 0 && current->next != 0)
                current = current->next;
        }
    }
    return res;
}

void Parser::clearErrors()
{
    thereare_errors = false;
}

void Parser::error(string msg)
{
    thereare_errors = true;
    char buf[255];
    sprintf(buf, ": %d,%d", curr_line_num, curr_index - curr_line_index);
    curr_prog->addError(msg + buf);
}

void Parser::warning(string msg)
{
    char buf[255];
    sprintf(buf, ": %d,%d", curr_line_num, curr_index - curr_line_index);
    curr_prog->addWarning(msg + buf);
}


bool Parser::incharset(char c, string set)
{
    unsigned int i = 0;
    bool res = false;
    while (i < set.size() && !res) {
        res = set[i] == c;
        i++;
    }
    return res;
}

bool Parser::isoper(char c)
{
    return incharset(c,"+-*//&|^~!><=");
}

bool Parser::isunaryoper(char c)
{
    return incharset(c,"+-~!");
}

bool Parser::isassignment(string op)
{
    return operations.getPriority("=") == operations.getPriority(op);
}

bool Parser::canContinue()
{
    return (!thereare_errors) && (curr_index < curr_str.length());
}

char Parser::currChar()
{
    return curr_str[curr_index];
}

bool Parser::skip(string wc, int count)
{
    bool s = incharset(currChar(), wc);
    int c = 0;
    while (canContinue() && s) {
        if (currChar() == '\n') {
            curr_line_num++;
            curr_line_index = curr_index + 1;
        }
        curr_index++;
        c++;
        s = c != count && incharset(currChar(), wc);
    }
    return canContinue();
}

double Parser::getNumber()
{
    double res = 0;
    while (canContinue() && isdigit(currChar())) {
        res = res*10 + currChar() - '0';
        curr_index++;
    }
    double p = 0.1;
    if (currChar() == '.') {
        curr_index++;
        while (canContinue() && isdigit(currChar())) {
            res += (currChar() - '0') * p;
            p/=10;
            curr_index++;
        }
    }
    if (isalpha(currChar()))
        error("operator missing");
    return res;
}

string Parser::getLiteral()
{
    string res;
    if (!isalpha(currChar()))
        return res;
    while (canContinue() && (isalnum(currChar()) || currChar() == '_')) {
        res += currChar();
        curr_index++;
    }
    return res;
}

string Parser::getString()
{
    string res;
    skip("\"");
    while (canContinue() && isascii(currChar()) && currChar() != '"') {
        res += currChar();
        curr_index++;
    }
    if (canContinue() && currChar() != '"') {
        error("invalid character");
    } else {
        curr_index++;
    }
    return res;
}

bool Parser::startsWith(string str)
{
    skip(" \r\n\t");
    unsigned int k = curr_str.find(str, curr_index);
    return k == curr_index;
}

string Parser::getOperation(bool dont_move)
{
    string res;
    for (unsigned int i = 0; i < operations.count(); i++)
        if (startsWith(operations.getOperationSorted(i))) {
            if (dont_move)
                return operations.getOperationSorted(i);
            while (canContinue() && isoper(currChar())) {
                res += currChar();
                curr_index++;
            }
            return res;
        }
    return res;
}

Program::Function Parser::getFunction()
{
    if (skip(" \r\n\t") && !startsWith("void")) {
        error("not correct function declaration");
        return Program::Function(0);
    }
    Program::Function res(curr_prog);
    curr_index += 4; //"void"
    skip(" \r\n\t");
    string literal = getLiteral();
    if (isReservedWord(literal)) {
        error("\""+literal + "\" is reserved word");
    } else {
        res.name = literal;
        if (skip(" \r\n\t") && currChar() == '(') {
            Program::FunctionArgument arg;
            while (skip(" \r\n\t") && currChar() != ')') {
                curr_index++;
                if (skip(" \r\n\t")) {
                    if ((arg.ref = currChar() == '&') == true)
                        curr_index++;
                    literal = getLiteral();
                    if (!skip(" \r\n\t") || (currChar() != ')' &&
                                           (currChar() != ',')) ||
                            (literal.empty() && res.arguments.size() > 0)) {
                        error("not correct function argument");
                    } else if (!literal.empty()) {
                        arg.name = literal;
                        res.arguments.push_back(arg);
                    }
                } else {
                    error("not correct function declaration");
                }
            }
        } else {
            error("'(' not found");
        }
    }
    return res;
}


void Parser::generateReservedWords()
{
    reserved_words.clear();
    reserved_words.push_back("void");
    reserved_words.push_back("return");
}

bool Parser::isReservedWord(string str)
{
    for (unsigned int i = 0; i < reserved_words.size(); i++)
        if (reserved_words[i] == str)
            return true;
    return false;
}

}
