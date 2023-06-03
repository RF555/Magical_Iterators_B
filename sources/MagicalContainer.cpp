#include "MagicalContainer.hpp"

namespace ariel {
    MagicalContainer::MagicalContainer() {}

    MagicalContainer::MagicalContainer(const ariel::MagicalContainer &_other)
            : ascending_container(vector<int>(_other.ascending_container)),
              cross_container(vector<int>(_other.cross_container)),
              prime_container(vector<int>(_other.prime_container)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other) noexcept {}

    MagicalContainer::~MagicalContainer() {}
}