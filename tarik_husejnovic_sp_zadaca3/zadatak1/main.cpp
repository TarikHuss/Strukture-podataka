#include "DoubleLinkedList.hpp"
#include <iostream>
#include <cassert>
#include <functional>

int main() {
    // Test default constructor
    DoubleLinkedList<int> list;
    assert(list.empty());
    assert(list.size() == 0);

    // Test push_back and push_front
    int a = 1, b = 2, c = 0;
    list.push_back(a);
    list.push_back(b);
    list.push_front(c);
    assert(list.size() == 3);
    assert(list.front() == 0);
    assert(list.back() == 2);

    // Test pop_front and pop_back
    list.pop_front();
    assert(list.front() == 1);
    list.pop_back();
    assert(list.back() == 1);
    assert(list.size() == 1);

    // Test copy constructor
    DoubleLinkedList<int> list2 = list;
    assert(list2.size() == list.size());
    assert(list2.front() == list.front());
    assert(list2.back() == list.back());

    //Test copy assignment operator
    DoubleLinkedList<int> list22;
    list22=list2;
    assert(list22.size() == list2.size());
    assert(list22.front() == list2.front());
    assert(list22.back() == list2.back());

    // Test move constructor
    DoubleLinkedList<int> list3 = std::move(list);
    assert(list3.size() == 1);
    assert(list.size() == 0);  

    //Test move assignment operator
    list2.push_front(10);
    list22 = std::move(list2);
    assert(list22.size() == 2);
    assert(list2.size() == 0);

    // Test push_back with rvalue
    list3.push_back(3);
    list3.push_front(2);
    assert(list3.front() == 2);
    assert(list3.back() == 3);

    // Test clear
    list3.clear();
    assert(list3.empty());
    assert(list3.size() == 0);

    //Test iterators
    list3.push_back(1);
    list3.push_back(2);
    list3.push_back(3);
    auto it = list3.begin();
    auto itEnd = list3.end();
    auto cit = list3.cbegin();
    auto citEnd = list3.cend();
    assert(itEnd == nullptr);
    assert(*it == 1);
    assert(*cit == 1);
    assert(citEnd == nullptr);

    //Test insert and erase
    ++it;
    list3.insert(it, 4);
    assert(list3.size() == 4);
    it = list3.begin();
    ++it;
    assert(*it == 4);
    list3.erase(it);
    assert(list3.size() == 3);

    // Test remove_if
    list3.push_back(4);
    list3.push_back(5);
    list3.push_back(6);
    list3.remove_if([](const int &value) { return value % 2 == 0; });
    for (auto it = list3.begin(); it != list3.end(); ++it) {
        assert(*it % 2 != 0);
    }

  DoubleLinkedList<int> list4;

    // Test reverse
    list4.push_back(1);
    list4.push_back(2);
    list4.push_back(3);
    list4.reverse();
    it = list4.begin();
    auto rit = list4.rbegin();
    auto ritEnd = list4.rend();
    auto rcit = list4.rcbegin();
    auto rcitEnd = list4.rcend();
    it = rit;
    assert(rit == it);
    assert(it != ritEnd);
    assert(rit == rcit);
    assert(ritEnd == rcitEnd);
    assert(*rit == 1);
    --rit;
    assert(*rit == 2);

    // Test find
    auto find_it = list3.find(3);
    assert(find_it != list3.end());
    assert(*find_it == 3);
    find_it = list3.find(77);
    assert(find_it == list3.end());

    std::cout << "Svi testovi su uspjesno prosli!" << std::endl;

    return 0;
}
