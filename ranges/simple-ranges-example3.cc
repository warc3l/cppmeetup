#include <range/v3/all.hpp>
#include <iostream>

int main(void) {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };

    ranges::copy(numbers | 
        ranges::view::transform([](int n) { return n*2; } ), 

        ranges::ostream_iterator<int>(std::cout, ", ")
    );
    return 0;
}
