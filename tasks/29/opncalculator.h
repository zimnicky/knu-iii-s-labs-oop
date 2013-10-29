#ifndef OPNCALCULATOR_H
#define OPNCALCULATOR_H

#include <string>

using namespace std;

class OPNCalculator
{
protected:
    enum class LexemeType{Number, Operation, Bracket};

    string expression;

    virtual LexemeType readLexeme(unsigned int &pos, string &lexeme);
    int priority(char op);
public:
    OPNCalculator(const string &expr);
    virtual string postfixForm();

    int calculate();
};

#endif // OPNCALCULATOR_H
