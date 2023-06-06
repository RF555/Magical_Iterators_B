#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;

int main() {
    cout << "\n\n";
    // Create a MagicalContainer and add some elements
    MagicalContainer my_container;
    cout << my_container << "\n";

    my_container.addElement(17);
    cout << my_container << "\n";

    my_container.addElement(2);
    cout << my_container << "\n";

    my_container.addElement(25);
    cout << my_container << "\n";

    my_container.addElement(9);
    cout << my_container << "\n";

    my_container.addElement(3);
    cout << my_container << "\n";

    my_container.addElement(-2);
    cout << my_container << "\n";

    my_container.addElement(122);
    cout << my_container << "\n";

    my_container.addElement(-13);
    cout << my_container << "\n";

    my_container.addElement(44);
    cout << my_container << "\n";

    my_container.addElement(26);
    cout << my_container << "\n";


    // Use AscendingIterator to display elements in ascending order
    std::cout << "Elements in ascending order:\n";
    MagicalContainer::AscendingIterator ascIter(my_container);
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        std::cout << *it << ' ';   // -13 -2 2 3 9 17 25 26 44 122
    }
    std::cout << "\n\n" << std::endl;



    // Use DescendingIterator to display elements in descending order
    std::cout << "Elements in cross order:\n";
    MagicalContainer::SideCrossIterator crossIter(my_container);
    for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
        std::cout << *it << ' ';  // -13 122 -2 44 2 26 3 25 9 17
    }
    std::cout << "\n\n" << std::endl;

    // Use PrimeIterator to display prime numbers only
    std::cout << "Prime numbers:\n";
    MagicalContainer::PrimeIterator primeIter(my_container);
    auto begin_it = primeIter.begin();
    auto end_it = primeIter.end();
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 3 17 
    }
    std::cout << "\n" << std::endl;

    // Remove an element from the my_container and display the size
    my_container.removeElement(9);
    std::cout << "Size of my_container after removing an element: " << my_container.size() << std::endl;

    return 0;
}
