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



    return 0;
}