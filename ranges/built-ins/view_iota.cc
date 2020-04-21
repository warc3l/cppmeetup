#include <iostream>
#include <range/v3/all.hpp>

int main(void) {

    for (auto n: ranges::view::iota(1,10))
        std::cout << n << ", ";

    std::cout << std::endl << "----" << std::endl;

    for (auto n: ranges::view::iota(1) | ranges::view::take(50) )
        std::cout << n << ", ";
    std::cout << std::endl;

    return 0;
}
