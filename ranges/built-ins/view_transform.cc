#include <iostream>
#include <range/v3/all.hpp>

int main(void) {
    std::string little = "little";
    
    for ( char x: little | ranges::view::transform( [](char c) { return ::toupper(c); } ) ) {
        std::cout << x;
    }
    std::cout << std::endl;

    return 0;
}
