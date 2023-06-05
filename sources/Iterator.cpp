#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {
    MagicalContainer::Iterator::Iterator() {}

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer &my_container) :
            _container(my_container) {}

    MagicalContainer::Iterator::Iterator(const ariel::MagicalContainer::Iterator &_other) {}

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer::Iterator &&_other) {}


}
