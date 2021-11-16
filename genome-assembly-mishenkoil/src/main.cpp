#include "genome.h"

#include <iostream>
#include <string>
#include <vector>


int main()
{
    const std::vector<std::string> reads = {};
    const std::size_t k = 0;

    std::cout << genome::assembly(k, reads);
    return 0;
}
