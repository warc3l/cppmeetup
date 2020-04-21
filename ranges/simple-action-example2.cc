#include <range/v3/all.hpp>
#include <iostream>

int main(void) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };

    for (auto n: ranges::action::drop(numbers, 1) | ranges::view::transform([](auto x) { return x*2; }) )
        std::cout << n << ", ";

    std::cout << "---" << std::endl;

    for (auto n: numbers)
        std::cout << n << ", ";

    std::cout << std::endl;

    return 0;
}
