#ifndef BOR_H
#define BOR_H
#include <vector>
#include <string>
#include <map>

using namespace std;

template<class Type>
class Bor
{
private:
    struct Vertex {
        int value_num;
        map<char, int> edges;
        Vertex() {
            value_num = -1;
        }
    };
    vector<Vertex> vertexes;
    vector<Type> values;
    int addVertex(Vertex v);
    void getSubtree(int v, string &curr_str, vector<pair<string, Type> >& res);
public:
    Bor();
    void setValue(string name, Type val);
    Type getValue(string name);
    void clear();
    vector<pair<string, Type> > getAll();
    vector<pair<string, Type> > getSubtree(string prefix);
};


#include "bor.h"

template<class Type>
Bor<Type>::Bor()
{
    addVertex(Vertex());
}

template<class Type>
int Bor<Type>::addVertex(Vertex v)
{
    vertexes.push_back(v);
    return vertexes.size() - 1;
}

template<class Type>
void Bor<Type>::setValue(string name, Type val)
{
    int v = 0;
    char c;
    map<char, int>::iterator it;
    for (unsigned int i = 0; i < name.size(); i++) {
        c = name[i];
        if ((it = vertexes[v].edges.find(c)) == vertexes[v].edges.end()) {
            int v1 = addVertex(Vertex());
            vertexes[v].edges.insert(make_pair(c, v1));
            v = v1;
        } else
            v = it->second;
    }
    if (vertexes[v].value_num == -1) {
        values.push_back(val);
        vertexes[v].value_num = values.size() - 1;
    } else {
        values[vertexes[v].value_num] = val;
    }
}

template<class Type>
Type Bor<Type>::getValue(string name)
{
    int v = 0;
    char c;
    map<char, int>::iterator it;
    for (unsigned int i = 0; i < name.size(); i++) {
        c = name[i];
        if ((it = vertexes[v].edges.find(c)) == vertexes[v].edges.end())
            return Type();
        v = it->second;
    }
    if (vertexes[v].value_num == -1)
        return Type();
    return values[vertexes[v].value_num];
}

template<class Type>
void Bor<Type>::clear()
{
    vertexes.clear();
    values.clear();
    addVertex(Vertex());
}

template<class Type>
void Bor<Type>::getSubtree(int v, string &curr_str, vector<pair<string, Type> > &res)
{
    if (vertexes[v].value_num != -1)
        res.push_back(make_pair(curr_str, values[vertexes[v].value_num]));
    curr_str.resize(curr_str.length() + 1);

    for (map<char, int>::iterator i = vertexes[v].edges.begin(); i != vertexes[v].edges.end(); i++) {
        curr_str[curr_str.length() - 1] = i->first;
        getSubtree(i->second, curr_str, res);
    }
    curr_str.resize(curr_str.length() - 1);
}

template<class Type>
vector<pair<string, Type> > Bor<Type>::getAll()
{
    string s;
    vector<pair<string, Type> > res;
    getSubtree(0, s, res);
    return res;
}

template<class Type>
vector<pair<string, Type> > Bor<Type>::getSubtree(string prefix)
{
    int v = 0;
    char c;
    vector<pair<string, Type> > res;
    map<char, int>::iterator it;
    for (int i = 0; i < prefix.size(); i++) {
        c = prefix[i];
        if ((it = vertexes[v].edges.find(c)) == vertexes[v].edges.end())
            return res;
        v = it->second;
    }
    string s = prefix;
    getSubtree(v, s, res);
    return res;
}

#endif
