#include <range/v3/all.hpp>
#include <vector>
#include <iostream>

int main(void ) {
    std::vector<int> v{0,1,2,3,4,5};
    auto even = [](int i){ return 0 == i % 2; };
    auto square = [](int i) { return i * i; };
    
    for (int i : v | ranges::view::filter(even) | ranges::view::transform(square)) {
        std::cout << i << ' ';
    }
}