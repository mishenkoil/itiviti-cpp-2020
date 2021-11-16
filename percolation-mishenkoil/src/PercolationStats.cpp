#include <random>
#include "Percolation.h"
#include "PercolationStats.h"

PercolationStats::PercolationStats(size_t dimension, size_t trials) : dimension(dimension), trials(trials)
{
    results.resize(trials);
    execute();
}

double PercolationStats::get_mean() const
{
    double sum = 0;
    for (auto element : results)
    {
        sum += element;
    }

    return sum / results.size();
}

double PercolationStats::get_standard_deviation() const
{
    double sum = 0;
    double mean = get_mean();
    for (auto element : results)
    {
        sum += ((element - mean) * (element - mean));
    }

    return sqrt(sum / (results.size() - 1));
}

double PercolationStats::get_confidence_low() const
{
    double mean = get_mean();
    double deviation = get_standard_deviation();

    return mean - (1.96 * deviation) / sqrt(results.size());
}

double PercolationStats::get_confidence_high() const
{
    double mean = get_mean();
    double deviation = get_standard_deviation();

    return mean + (1.96 * deviation) / sqrt(results.size());
}

void PercolationStats::execute()
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<size_t> random_num(0,dimension - 1); // guaranteed unbiased

    for (size_t i = 0; i < trials; ++i) {
        Percolation experiment(dimension);
        while (!experiment.has_percolation())
        {
            size_t row = random_num(rng);
            size_t column = random_num(rng);
            // if the cell is already open, open() will do nothing
            experiment.open(row, column);
        }
        // calculate and save p*
        results[i] = (static_cast<double>(experiment.get_numbet_of_open_cells()) / dimension) / dimension;
    }
}
