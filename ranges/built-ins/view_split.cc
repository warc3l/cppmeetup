#include <iostream>
#include <range/v3/all.hpp>

int main(void) {
    std::vector<std::string> world = {
        // Europe
        "Spain",
        "France",
        "Germany",
        "Italy",
        "-", // delimeter
        // America
        "California",
        "New York",
        "Washington",
        "-", // delimeter
        // Africa
        "Niger",
        "Sudan",
        "Botsuana"
        "-", // delimeter
        // ... blabla
    };
    for ( auto continent: world | ranges::view::split("-") ) {
        for (auto country_state: continent) 
            std::cout << country_state << ",";
        std::cout << std::endl << "----" << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
