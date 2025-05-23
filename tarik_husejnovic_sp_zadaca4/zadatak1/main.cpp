#include <iostream>
#include <string>
#include "heap.hpp" 

int main() {
    Heap<int> h;

    h.insert(1);
    h.insert(40);
    h.insert(25);
    h.insert(10);
    h.insert(20);

    std::cout << "Trenutno stanje heap-a: ";
    std::cout<< h <<std::endl;

    std::cout << "Najveci element: " << h.max() << std::endl;
    std::cout << "Uklanjanje najveceg elementa: " << h.removeMax() << std::endl;
    std::cout << "Novi najveci element: " << h.max() << std::endl;

    std::cout << "Trenutna veličina: " << h.size() << std::endl;
    std::cout << "Trenutni kapacitet: " << h.capacity() << std::endl;

    std::cout << "Heap je pun: " << (h.full() ? "Da" : "Ne") << std::endl;
    std::cout << "Heap je prazan: " << (h.empty() ? "Da" : "Ne") << std::endl;

    std::cout << "Ispisivanje heap-a: ";
    std::cout << h << std::endl;

    h.clear();
    std::cout << "Heap je prazan nakon clear(): " << (h.empty() ? "Da" : "Ne") << std::endl;

    return 0;
}
