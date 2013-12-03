#ifndef TASK_H
#define TASK_H

#include <vector>

using namespace std;

enum class CoinState{UNDEFINED, HEAD, TAIL};


bool getResult(unsigned int n, unsigned int m, unsigned int s, unsigned int k, unsigned int l, vector<CoinState> &result);



#endif // TASK_H
