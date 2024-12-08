#include "datagenerator.h"

#include <random>

DataGenerator::DataGenerator(Distribution distr, QObject *parent) :
    QObject {parent}
{
    distribution = distr;
    gen          = std::mt19937(std::random_device()());
    poisson      = std::poisson_distribution<>(4);
}

int
DataGenerator::generate(int i)
{
    if(distribution == Distribution::Poisson)
    {
        return poisson(gen);
    }
    else
    {
        return 1;
    }
}
