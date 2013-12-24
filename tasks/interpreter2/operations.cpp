#include "operations.h"

namespace interpreter
{

Operations::Operations()
{
    vector<string> line;
#define add(a) line.push_back(a)
#define newline priorities.push_back(line); line.clear()
    add("!");
    add("~");
    newline;
    add("*");
    add("/");
    newline;
    add("+");
    add("-");
    newline;
    add("<<");
    add(">>");
    newline;
    add("<=");
    add(">=");
    add("<");
    add(">");
    newline;
    add("==");
    add("!=");
    newline;
    add("&");
    newline;
    add("^");
    newline;
    add("|");
    newline;
    add("&&");
    newline;
    add("||");
    newline;
    add("=");
    add("+=");
    add("-=");
    add("*=");
    add("/=");
    add("<<=");
    add(">>=");
    add("&=");
    add("|=");
    add("^=");
    newline;

    for (unsigned int i = 0; i < priorities.size(); i++)
        for (unsigned int j = 0; j < priorities[i].size(); j++)
            sorted.push_back(priorities[i][j]);
    sort(sorted.begin(), sorted.end(),  &sort_cmp);

#undef add
#undef newline
}

int Operations::getPriority(string operation)
{
    for (unsigned int i = 0; i < priorities.size(); i++)
        for (unsigned int j = 0; j < priorities[i].size(); j++)
            if (priorities[i][j] == operation)
                return priorities.size() - i - 1;
    return priorities.size();
}

bool Operations::isAssignment(string operation)
{
    return getPriority(operation) == getPriority("=");
}

int Operations::getMaxPriority()
{
    return priorities.size() - 1;
}

string Operations::getOperationSorted(int number)
{
    return sorted[number];
}

unsigned int Operations::count()
{
    return sorted.size();
}

}
