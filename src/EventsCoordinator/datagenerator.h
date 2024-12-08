#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

// #include <boost/math/distributions/pareto.hpp>
#include <random>

#include <QObject>

enum class Distribution
{
    Pareto,
    Poisson
};

class DataGenerator : public QObject
{
    Q_OBJECT

public:
    explicit DataGenerator(Distribution distr, QObject *parent = nullptr);

    int generate(int i);

Q_SIGNALS:

private:
    Distribution                   distribution;

    std::mt19937                   gen;
    std::poisson_distribution<int> poisson;
};

#endif    // DATAGENERATOR_H
