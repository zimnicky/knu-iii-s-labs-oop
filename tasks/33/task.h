#ifndef TASK_H
#define TASK_H

#include <vector>

using namespace std;

//solves: sum(coefs[i]*xi) = gcd(coefs[i])
int gcd(vector<int> &coefs, vector<int> &result);

//solves: sum(sum(coefs[i]*xi)) = rightVal
vector<int> solve(vector<int> &coefs, int rightVal);

#endif // TASK_H
