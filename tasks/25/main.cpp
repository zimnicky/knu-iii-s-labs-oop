#include <iostream>
#include <fstream>
#include "palindrome.h"

using namespace std;

int main()
{
    ifstream in("input.txt");
    string str;
    getline(in, str, '\n');
    in.close();

    ofstream out("output.txt");

    out << palindrome(str) << endl;

    out.close();
    return 0;
}

