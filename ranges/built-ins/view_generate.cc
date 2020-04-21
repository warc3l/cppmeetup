#include <iostream>
#include <range/v3/all.hpp>
#include <random>

int main(void) {

    std::vector<double> noise = ranges::view::generate( [rnd_gen = std::mt19937{}, dist = std::normal_distribution<>{5,2}]() mutable { return dist(rnd_gen); }) | 
                                  ranges::view::take(50) | ranges::copy;
    for ( auto n: noise )
        std::cout << n << ", ";
    std::cout << std::endl;

    return 0;
}
