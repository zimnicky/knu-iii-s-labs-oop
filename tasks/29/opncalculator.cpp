#include "opncalculator.h"

#include <stack>
#include <string>

using namespace std;


OPNCalculator::OPNCalculator(const string &expr):expression(expr)
{
    // need to check if expr is correct
}

OPNCalculator::LexemeType OPNCalculator::readLexeme(unsigned int &pos, string &lexeme)
{
    lexeme.clear();

    if (expression[pos] == '+' || expression[pos] == '-' ||
            expression[pos] == '*' || expression[pos] == '/')
    {
        lexeme.push_back(expression[pos++]);
        return LexemeType::Operation;
    }

    if (expression[pos] == '(' || expression[pos] == ')')
    {
        lexeme.push_back(expression[pos++]);
        return LexemeType::Bracket;
    }

    while (expression[pos] >= '0' && expression[pos] <= '9')
    {
        lexeme.push_back(expression[pos++]);
    }

    return LexemeType::Number;
}

int OPNCalculator::priority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 3;
}

string OPNCalculator::postfixForm()
{
    stack<string> st;

    string res;

    unsigned int i = 0;

    while (i < expression.size())
    {
        string lex;

        LexemeType type = readLexeme(i, lex); // read next element in string

        switch (type)
        {
        case LexemeType::Number:{ // it's a number
            res += ' ' + lex;
            break;
        }
        case LexemeType::Operation:{ //it's an operation

            while (!st.empty() && st.top()[0] != '(' &&
                   priority(st.top()[0]) >= priority(lex[0]) ) // pop all opeartions with higher priority from the stack
            {
                res += st.top();
                st.pop();
            }
            st.push(lex);
            break;
        }
        case LexemeType::Bracket:{ // it's a bracket
            if (lex[0] == ')')
            {
                lex = st.top();
                st.pop();
                while (lex[0] != '(' && !st.empty()) // pop all from stack until '('
                {
                    res += lex;
                    lex = st.top();
                    st.pop();
                }
            }
            else // it's '('
                st.push(lex);
            break;
        }
        }
    }

    while (!st.empty()) // can rest some operations in stack
    {
        string tmp = st.top();
        st.pop();
        res += tmp;
    }

    return res;
}


int OPNCalculator::calculate()
{
    string expr = postfixForm();
    stack<int> numbers;

    unsigned int i = 0;

    while (i < expr.size())
    {
        if (expr[i] != ' ')
        {
            LexemeType type = LexemeType::Operation;
            // try to read number
            int number = 0;
            while (expr[i] >= '0' && expr[i] <= '9')
            {
                type = LexemeType::Number;
                number = number * 10 + expr[i++] - '0';
            }

            if (type == LexemeType::Number)
                numbers.push(number);
            else // it's an operation
            {
                int a = numbers.top();
                numbers.pop();
                int b = numbers.top();
                numbers.pop();
                switch (expr[i]) {
                case '+':
                    numbers.push(a+b);
                    break;
                case '-':
                    numbers.push(a-b);
                    break;
                case '*':
                    numbers.push(a*b);
                    break;
                case '/':
                {
                    if (b == 0)
                        throw "Division by zero";
                    numbers.push(a/b);
                    break;
                }
                default:
                    break;
                }
                i++;
            }
        }
        else
            i++;
    }
    return numbers.top();
}
