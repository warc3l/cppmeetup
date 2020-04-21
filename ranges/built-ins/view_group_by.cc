#include <iostream>
#include <range/v3/all.hpp>

typedef struct {
    std::string name;
    std::string city;
} person;

int main(void) {
    std::vector<person> people = {  { "Beth", "Bcn" }, 
                                    { "GoodPerson", "Bcn" }, 
                                    { "A", "Bcn" },
                                    { "Erik", "San Diego" },
                                    { "Another", "San Diego" }, 
                                    { "Unknown", "Germany" } };

    auto rngRngs = people | ranges::view::group_by([](auto a, auto b) { return a.city == b.city;  });
    for ( auto rng: rngRngs  ) {
        for (auto x: rng) {
            std::cout << x.name << " - " << x.city << std::endl;
        }
        std::cout << "-----" << std::endl;
    }

    return 0;
}
