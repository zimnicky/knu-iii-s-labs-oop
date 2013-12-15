#include "salesman.h"
#include <algorithm>
#include <time.h>

Salesman::Salesman()
{
}

bool Salesman::isDublicate(const vector<unsigned int> &path)
{
    for (auto i:  population)
    {
        bool dublicate = false;
        for (unsigned int j = 0; j < path.size() && !dublicate; j++)
            dublicate |= i[j] != path[j];
        if (dublicate)
            return true;
    }
    return false;
}

void Salesman::generatePopulation(unsigned int count)
{
    population.clear();

    vector<unsigned int> path(cities.size());
    for (unsigned int i = 0; i < cities.size(); i++)
        path[i] = i;

    srand(clock());
    for (unsigned int i = 0; i < count; i++)
    {
        random_shuffle(path.begin(), path.end());
        while (isDublicate(path))
            random_shuffle(path.begin(), path.end());

        population.push_back(path);
    }
}


double Salesman::fitness(unsigned int num)
{
    double res;
    for (unsigned int i = 0; i < cities.size() - 1; i++)
        res += cities[population[num][i]].distance(cities[population[num][i+1]]);
    return res;
}


void Salesman::mutation(unsigned int num)
{
    unsigned int pos = rand()%cities.size();
    unsigned int newPos = rand()%cities.size();
    unsigned int city = population[num][pos];

    population[num].erase(population[num].begin() + pos);
    population[num].insert(population[num].begin() + newPos, city);
}


void Salesman::crossing(vector<vector<unsigned int>> &population, unsigned int a, unsigned int b)
{
    vector<unsigned int> linksA(cities.size());
    vector<unsigned int> linksB(cities.size());

    for (unsigned int i = 0; i < cities.size() - 1; i++)
    {
        linksA[population[a][i]] = population[a][i+1];
        linksB[population[b][i]] = population[b][i+1];
    }
    linksA[population[a][cities.size()-1]] = population[a][cities.size()-1];
    linksB[population[b][cities.size()-1]] = population[b][cities.size()-1];

    vector<unsigned int> linksRes(cities.size());

    for (unsigned int i = 0; i < cities.size() - 1; i++)
    {
        if ((i&1) == 0)
            linksRes[i] = linksA[i];
        else
            linksRes[i] = linksB[i];
    }


    vector<unsigned int> res;

    unsigned int curr = 0;
    if (linksRes[curr] == curr)
        curr++;

    while (linksRes[curr] != curr)
        res.push_back(linksRes[curr++]);
    res.push_back(curr);

    population.push_back(res);
}

double Salesman::doubleRand(double a, double b)
{
    return a + ((double)rand()/(double)RAND_MAX)*(b - a);
}

vector<unsigned int> Salesman::run(unsigned int populationSize, unsigned int iterations, double chanceOfCrossing, double chanceOfMutation)
{
    generatePopulation(populationSize);

    for (unsigned int i = 0; i < iterations; i++)
    {
        // calculating fitness-function
        vector<double> length(population.size());
        double middle = 0;
        for (unsigned int j = 0; j < population.size(); j++)
        {
            length[j] = fitness(j);
            middle += length[j];
        }

        middle /= population.size();

        // selecting the best
        vector<vector<unsigned int>> tmpPopulation;
        for (unsigned int j = 0; j < populationSize; j++)
        {
            while (middle/length[j] >= 1 && tmpPopulation.size() < populationSize)
            {
                tmpPopulation.push_back(population[j]);
                length[j] -= 1;
            }

            if (doubleRand(0,1) >= length[j] && tmpPopulation.size() < populationSize)
              tmpPopulation.push_back(population[j]);
        }

        // crossing
        population.clear();
        for (unsigned int j = 0; j < populationSize/2; j++)
        {
            unsigned int first = rand()%populationSize;
            unsigned int second = rand()%populationSize;

            double chance = doubleRand(0, 1);

            if (chanceOfCrossing <= chance)
            {
                crossing(tmpPopulation, first, second);
                crossing(tmpPopulation, second, first);
            }
            else
            {
                population.push_back(tmpPopulation[first]);
                population.push_back(tmpPopulation[second]);
            }
        }

        // mutation
        for (unsigned int j = 0; j < populationSize; j++)
        {
            double chance = doubleRand(0,1);
            if (chance < chanceOfMutation)
                mutation(j);
        }
    }

    unsigned int minNum = 0;
    vector<double> length(population.size());
    for (unsigned int j = 0; j < population.size(); j++)
    {
        length[j] = fitness(j);
        if (length[j] < length[minNum])
            minNum = j;
    }

    return population[minNum];
}


void Salesman::addCity(Point p)
{
    cities.push_back(p);
}
