#include <range/v3/all.hpp>
#include <vector>
#include <iostream>

int main(void ) {
    std::vector<int> v{-13,1,214,12,5,13};

    std::cout << "Before Ranges::Sort" << std::endl;
    for (auto i : v) 
        std::cout << i << " ";
    std::cout << std::endl;

    ranges::sort(v);
    
    std::cout << "After Ranges::Sort" << std::endl;
    for (auto i : v) 
        std::cout << i << " ";
    std::cout << std::endl;
}