#ifndef TASK_H
#define TASK_H

double abs(double x)
{
    if (x > 0)
        return x;
    return -x;
}

const double PI = 3.14159265359;

double cos(double x, double eps)
{
    double sum = 1;
    double prevSum = 0;
    double operand = 1;
    int i = 1;

    bool finish = false;

    while(!finish)
    {
        prevSum = sum;
        operand *= (x*x)/( (2*i)*(2*i-1));
        if (i % 2 == 1)
            sum -= operand;
        else
            sum += operand;
        i++;
        finish = abs(sum - prevSum) < eps;
    }

    return sum;

}



#endif // TASK_H
