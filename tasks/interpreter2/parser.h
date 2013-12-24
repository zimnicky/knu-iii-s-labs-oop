#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "tree.h"
#include "program.h"
#include "operations.h"

namespace interpreter
{
    using std::string;
class Parser
{
public:
    Parser();
    Program * parseProgram(string s);
private:
    Program *curr_prog;
    string curr_str;
    unsigned int curr_index;
    unsigned int curr_line_num;
    unsigned int curr_line_index;
    Operations operations;
    vector<string> reserved_words;

    bool thereare_errors;
    string error_msg;
    vector<string> warnings;

    void clearErrors();
    void error(string msg);
    void warning(string msg);

    void generateReservedWords();
    bool isReservedWord(string str);

    Node * readSingle();
    ReturnNode * readReturn();
    Node * readNext();
    Node * parseExpr(int priority);
    Node * parseIf();
    Node * parseBlock();
    void parseProgram();

    bool isoper(char c);
    bool isunaryoper(char c);
    bool incharset(char c, string set);
    bool isassignment(string op);

    // additional
    bool canContinue();
    char currChar();
    bool skip(string wc, int count = 0);
    double getNumber();
    string getLiteral();
    string getString();
    string getOperation(bool dont_move = false);
    Program::Function getFunction();
    bool startsWith(string str);

};

}

#endif // PARSER_H
