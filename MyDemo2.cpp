#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;

int main() {
    // Create a MagicalContainer and add some elements
    MagicalContainer my_container;
    cout << "my_container: " << my_container << "\t\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 17" << "\n";
    my_container.addElement(17);
    cout << "my_container: " << my_container << "\t\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 2" << "\n";
    my_container.addElement(2);
    cout << "my_container: " << my_container << "\t\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 25" << "\n";
    my_container.addElement(25);
    cout << "my_container: " << my_container << "\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 9" << "\n";
    my_container.addElement(9);
    cout << "my_container: " << my_container << "\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 3" << "\n";
    my_container.addElement(3);
    cout << "my_container: " << my_container << "\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd -2" << "\n";
    my_container.addElement(-2);
    cout << "my_container: " << my_container << "\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 122" << "\n";
    my_container.addElement(122);
    cout << "my_container: " << my_container << "\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd -13" << "\n";
    my_container.addElement(-13);
    cout << "my_container: " << my_container << "\tsize: " << my_container.size() << "\n";

    cout << "\tadd 44" << "\n";
    my_container.addElement(44);
    cout << "my_container: " << my_container << "\tsize: " << my_container.size() << "\n";

    cout << "\tadd 26" << "\n";
    my_container.addElement(26);
    cout << "my_container: " << my_container << "\tsize: " << my_container.size() << "\n";



    // Use AscendingIterator to display elements in ascending order
    std::cout << "Elements in ascending order:\n";
    MagicalContainer::AscendingIterator ascIter(my_container);
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        std::cout << *it << ' ';   // 2 3 9 17 25
    }
    std::cout << "\n\n" << std::endl;



    // Use DescendingIterator to display elements in descending order
    std::cout << "Elements in cross order:\n";
    MagicalContainer::SideCrossIterator crossIter(my_container);
    for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 25 3 17 9
    }
    std::cout << "\n\n" << std::endl;



    // Use PrimeIterator to display prime numbers only
    std::cout << "Prime numbers:\n";
    MagicalContainer::PrimeIterator primeIter(my_container);
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 3 17 
    }
    std::cout << "\n" << std::endl;

    // Remove an element from the my_container and display the size
    my_container.removeElement(9);
    std::cout << "Size of my_container after removing an element: " << my_container.size() << std::endl;

    return 0;
}
