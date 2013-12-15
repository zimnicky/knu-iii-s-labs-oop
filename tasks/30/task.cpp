#include "task.h"
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

double doubleRand(double a, double b)
{
    return a + ((double)rand()/(double)RAND_MAX)*(b - a);
}

double findMin(int population, int iterations, func f)
{
    srand(clock());
    vector<int> p(population);

    // generating first population
    for (int i = 0; i < population; i++)
        p[i] = rand()%2000 - 1000;


    for (int t = 0; t < iterations; t++)
    {
        vector<double> val(population);

        double middle = 0;
        for (int i = 0; i < p.size(); i++)
        {
            val[i] = f(p[i]);
            middle += val[i];
        }

        middle /= p.size();

        vector<int> tmp;

        // selecting the best
        for (int i = 0; i < p.size(); i++)
        {
            while (middle/val[i] >= 1 && tmp.size() < population)
            {
                tmp.push_back(p[i]);
                val[i] -= 1;
            }

            if (doubleRand(0,1) >= val[i] && tmp.size() < population)
              tmp.push_back(p[i]);
        }

        //crossing
        p.clear();
        for (unsigned int j = 0; j < population/2; j++)
        {
            unsigned int first = rand()%population;
            unsigned int second = rand()%population;

            int t = 0xFFFF;
            int r = 0;
            int r1 = 0;
            int ta = tmp[first];
            int tb = tmp[second];
            while (t > 0)
            {
                if ((t&1) == 0)
                {
                    r += (ta&1);
                    r1 += (tb&1);
                }
                else
                {
                    r += (tb&1);
                    r1 += (ta&1);
                }
                r <<= 1;
                r1 <<= 1;
                ta >>= 1;
                tb >>= 1;
                t >>= 1;
            }

            p.push_back(r);
            p.push_back(r1);
        }

        //mutation
        for (unsigned int j = 0; j < population; j++)
        {
            double chance = doubleRand(0,1);
            if (chance < 0.15)
            {
                int t = 1 << (rand()%31 + 1);
                p[j] ^= t;
            }
        }

    }

    int min = 0;
    for (int i = 0; i < p.size(); i++)
        if (p[i] < p[min])
            min = i;

    return p[min];
}
