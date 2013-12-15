#ifndef TASK_H
#define TASK_H

typedef double (*func)(int);

double findMin(int population, int iterations, func f);

#endif // TASK_H
