#include <iostream>
#include <range/v3/all.hpp>

int main(void) {
    std::vector<int> points = {3, 5, 1, 7, 8, 9};
    std::string little = "little";
    for ( auto x: ranges::view::zip(points, little) ) {
        std::cout << std::get<0>(x) << " - > " << std::get<1>(x) << std::endl; 
    }

    return 0;
}
