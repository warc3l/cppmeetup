#include <range/v3/all.hpp>
#include <iostream>
#include <random>

namespace view {
    auto moving_average = [](size_t l, size_t h) {
            return (
                ranges::view::sliding(l) |  ranges::view::stride(h) | ranges::view::transform([](const auto& range) {     
                using value_t = ranges::range_value_type_t<decltype(range)>;
                return ranges::accumulate(range, value_t{}) / value_t(ranges::size(range)); 
            }) ); 
        };
}

int main() {
    std::vector<double> numbers = ranges::view::generate( [rnd_gen = std::mt19937{}, dist = std::normal_distribution<>{5,2}]() mutable { return dist(rnd_gen); }) | 
                                  ranges::view::take(50) | ranges::copy;

    for (auto n : numbers | view::moving_average(3, 5) )
        std::cout << n << std::endl; 
    std::cout << std::endl;
}

