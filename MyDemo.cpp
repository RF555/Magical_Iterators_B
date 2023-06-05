#include <iostream>
#include "sources/MagicalContainer.hpp"

using namespace ariel;

int main() {
    cout << "hello world\n" << endl;

    MagicalContainer my_container;
    cout << "my_container: " << my_container << "\t\t\t\tsize: " << my_container.size() << "\n";

    cout << "\tadd 17" << "\n";
    my_container.addElement(17);
    cout << "my_container: " << my_container << "\t\t\t\tsize: " << my_container.size() << "\n";


    return 0;
}