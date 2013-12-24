#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace interpreter
{

class Operations
{
protected:
    vector<vector<string> > priorities;
    vector<string> sorted;
    static bool sort_cmp(string a, string b){ return a.length() > b.length();}
public:
    int getPriority(string operation);
    bool isAssignment(string operation);
    int getMaxPriority();
    string getOperationSorted(int number);
    unsigned int count();
    Operations();
};

}
#endif // OPERATIONS_H
