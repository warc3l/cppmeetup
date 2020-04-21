#include <range/v3/all.hpp>
#include <vector>
#include <iostream>

int main(void ) {
    auto infinite_range = ranges::view::iota(1); // std::vector<int> v{0,1,2,3,4,5};
    ranges::sort(infinite_range);

}