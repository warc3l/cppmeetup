#include <iostream>
#include <range/v3/all.hpp>

int main(void) {
    for (auto n: ranges::view::iota(1) | ranges::view::filter( [] (auto n) { return n%3 == 0; } ) | ranges::view::take(100) )
        std::cout << n << ",";
    std::cout << std::endl;
    return 0;
}
