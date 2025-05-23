#include <iostream>
#include "map.hpp"

int main() {
    Map<int, std::string> myMap;

    std::cout << "Is map empty? " << (myMap.empty() ? "Yes" : "No") << std::endl;

    myMap.insert(3, "Three");
    myMap.insert(1, "One");
    myMap.insert(2, "Two");

    std::cout << "Map size after insertions: " << myMap.size() << std::endl;

    try {
        std::cout << "Element with key 2: " << myMap.at(2) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    auto found = myMap.find(3);
    if (found) {
        std::cout << "Found element with key 3: " << *found << std::endl;
    } else {
        std::cout << "Element with key 3 not found." << std::endl;
    }

    myMap[4] = "Four";
    std::cout << "Element with key 4: " << myMap[4] << std::endl;

    if (myMap.erase(3)) {
        std::cout << "Element with key 3 erased." << std::endl;
    } else {
        std::cout << "Failed to erase element with key 2." << std::endl;
    }

    std::cout << "Map contents:" << std::endl;
    myMap.print();

    myMap.clear();
    std::cout << "Map size after clearing: " << myMap.size() << std::endl;

    return 0;
}
