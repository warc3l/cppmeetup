#include <iostream>
#include <range/v3/all.hpp>

int main(void) {
    auto firstRange = ranges::view::iota(1,15);
    auto secondRange = ranges::view::iota(50, 75);
    std::vector<int> container = {1,3,5,7,9,11, -1};
    for (auto n: ranges::view::concat(firstRange, container, secondRange))
        std::cout << n << ",";
    std::cout << std::endl;

    return 0;
}
