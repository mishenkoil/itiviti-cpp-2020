#include "../include/utils.h"
#include <iostream>
#include <cmath>

namespace utils {
    std::uniform_real_distribution<> get_real_distribution()
    {
        // produces random floating-point values uniformly distributed on the interval
        return std::uniform_real_distribution<>(0.0, 1.0);
    }

    std::mt19937_64 get_random_generator()
    {
        // non-deterministic random number generator using hardware entropy source
        std::random_device random_device;
        // seeding Mersenne Twister with a non-deterministic value
        return std::mt19937_64(random_device());
    }

    struct humanoid
    {
        // false == allele A, true == allele B
        bool first;
        bool second;
    };

    void start_new_simulation(unsigned int &population_size, double edited_dominant_chance,
                              double edited_recessive_chance, unsigned int &dominant_wins,
                              std::function<double()> &generator)

    {
        humanoid parent1;
        humanoid parent2;
        humanoid child;
        unsigned int dominant_alleles_children = 0;
        unsigned int recessive_alleles_children = 0;
        while (true)
        {
            dominant_alleles_children = 0;
            recessive_alleles_children = 0;

            for (unsigned int j = 0; j < population_size; ++j)
            {
                parent1.first = generator() < edited_dominant_chance;
                parent1.second = generator() < edited_dominant_chance;
                parent2.first = generator() < edited_dominant_chance;
                parent2.second = generator() < edited_dominant_chance;
                child.first = generator() < 0.5 ? parent1.first : parent1.second;
                child.second = generator() < 0.5 ? parent2.first : parent2.second;

                child.first ? ++dominant_alleles_children :
                ++recessive_alleles_children;
                child.second ? ++dominant_alleles_children :
                ++recessive_alleles_children;
            }


            edited_dominant_chance = static_cast<double> (dominant_alleles_children) / (2 * population_size);
            edited_recessive_chance = 1 - edited_dominant_chance;
            if (recessive_alleles_children == 0)
            {
                dominant_wins++;
                break;
            }
            if (dominant_alleles_children == 0)
            {
                break;
            }
        }
    }

    std::pair<double, double> get_fixation_extinction_probability(std::function<double()> generator,
                                                                  unsigned int number_of_iterations,
                                                                  unsigned int population_size,
                                                                  double recessive_chance,
                                                                  double dominant_chance)
    {
        if (population_size == 0 || number_of_iterations == 0)
        {
            std::cerr << "Wrong input, division by zero" << '\n';
            abort();
        }
        unsigned int dominant_wins = 0;

        for (unsigned int i = 0; i < number_of_iterations; ++i)
        {
            start_new_simulation(population_size, dominant_chance, recessive_chance, dominant_wins, generator);
        }

        double extenction_p = static_cast<double> (dominant_wins) / number_of_iterations;
        double fixation_p = 1 - extenction_p;
        return {fixation_p, extenction_p};
    }
}