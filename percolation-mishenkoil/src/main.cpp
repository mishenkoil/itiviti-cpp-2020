#include <iostream>

#include "Percolation.h"
#include "PercolationStats.h"

int main()
{
    const size_t dimension = 10;
    const size_t trials = 500;
    PercolationStats percolation_stats(dimension, trials);
//    for (auto a : percolation_stats.results) {
//        std::cout << a << std::endl;
//    }

    return 0;
}
