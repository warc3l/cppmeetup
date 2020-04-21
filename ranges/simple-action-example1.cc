#include <range/v3/all.hpp>
#include <iostream>

int main(void) {
    std::vector<float> numbers = { 1, 2, 3, 4, 5, 6 };

    std::cout << "Before Transform" << std::endl;
    for (auto n: numbers)
        std::cout << n << ", ";
    std::cout << std::endl;

    ranges::action::transform(numbers, [](float n) { return sqrt(n); });

    std::cout << "After Transform" << std::endl;
    for (auto n: numbers)
        std::cout << n << ", ";
    std::cout << std::endl;

    return 0;
}
