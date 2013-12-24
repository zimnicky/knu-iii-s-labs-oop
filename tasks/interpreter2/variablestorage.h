#ifndef VARIABLESTORAGE_H_INCLUDED
#define VARIABLESTORAGE_H_INCLUDED

#include <fstream>
#include <string>
#include <locale>
#include <cstring>
#include <iostream>
#include <vector>
#include "bor.h"

namespace interpreter
{

using namespace std;

template<class Type>
class Variable_Storage
{
private:
    typedef Bor<Type> Container;
    Container variables;
    string filename;
    void read();
    void write();
public:
    Variable_Storage() {}
    Variable_Storage(string filename) {
        this->filename = filename;
        read();
    }
    void setFilename(string filename) {
        this->filename = filename;
        read();
    }
    void setValue(string var, Type val);
    Type getValue(string var);
    vector<pair<string, Type> > getNamespace(string ns);
};

template<class Type>
void Variable_Storage<Type>::read()
{
    if (filename.empty())
        return;
    ifstream f(filename.c_str());
    if (f.fail())
        return;
    variables.clear();
    string t1;
    Type t2;
    while (!f.eof()) {
        getline(f,t1,'=');
        f >> t2;
        if (!t1.empty())
            variables.setValue(t1, t2);
    }
    f.close();
}

template<class Type>
void Variable_Storage<Type>::write()
{
    if (filename.empty())
        return;
    ofstream f(filename.c_str());

    vector<pair<string, Type> > tmp;
    tmp = variables.getAll();
    typename vector<pair<string, Type> >::iterator it = tmp.begin();

    f << it->first << "=" << it->second;
    it++;
    for (; it != tmp.end(); it++)
        f << endl << it->first << "=" << it->second;
    f.close();
}

template<class Type>
void Variable_Storage<Type>::setValue(string var, Type val)
{
    if (var.find("::") == string::npos)
        var = "main::" + var;
    variables.setValue(var, val);
    write();
}

template<class Type>
Type Variable_Storage<Type>::getValue(string var)
{
    if (var.find("::") == string::npos)
        var = "main::" + var;
    return variables.getValue(var);
}

template<class Type>
vector<pair<string, Type> > Variable_Storage<Type>::getNamespace(string ns)
{
    return variables.getSubtree(ns);
}



}

#endif // VARIABLESTORAGE_H_INCLUDED
