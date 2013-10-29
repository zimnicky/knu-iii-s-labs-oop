#include <iostream>
#include <fstream>
#include <string>
#include "opncalculator.h"

using namespace std;

int main()
{
    ifstream in("expression.txt");
    string expr;
    getline(in, expr, '\n');
    in.close();

    OPNCalculator c(expr);

    cout << "Postfix form:" << c.postfixForm() << endl;
    cout << "Result:" << c.calculate() << endl;
    return 0;
}

