#include <iostream>
#include <range/v3/all.hpp>

int main(void) {
    std::string supercalifragilespialidoso = "supercalifragilespialidoso";
    
    for ( auto c: supercalifragilespialidoso | ranges::view::reverse ) {
        std::cout << c;
    }
    std::cout << std::endl;

    return 0;
}
