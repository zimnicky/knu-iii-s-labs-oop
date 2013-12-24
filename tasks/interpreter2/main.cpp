#include <iostream>
#include <fstream>
#include "parser.h"

using namespace std;
using namespace interpreter;

int main()
{
    //freopen("input.txt","r", stdin);
    //freopen("output.txt","w", stdout);
    string s;
    string program;

    ifstream in("input.txt");
    getline(in, s, '\n');
    while (!in.eof()) {
        program += s + '\n';
        getline(in, s, '\n');
    }
    Parser p;
    Program *prog = p.parseProgram(program);
    if (!prog->hasErrors())
    {
        cout << "no errors" << endl;
        prog->execute();
    }
    else
    {
        vector<string> t = prog->getErrors();
        for (int i = 0; i < t.size(); i++)
            cout << t[i] << endl;
    }
    return 0;
}

