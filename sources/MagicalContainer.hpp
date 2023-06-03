#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <typeinfo>


using namespace std;

namespace ariel {
    class MagicalContainer {
    private:
        vector<int> ascending_container;
        vector<int> cross_container;
        vector<int> prime_container;

        MagicalContainer();

        MagicalContainer(const MagicalContainer &_other);

        MagicalContainer(MagicalContainer &&_other) noexcept;

        ~MagicalContainer();

        MagicalContainer &operator=(const MagicalContainer &_other);

        MagicalContainer &operator=(MagicalContainer &&_other) noexcept;

        void addElement(int element);

        long size() const;

        void removeElement(int element);

        friend std::ostream &operator<<(ostream &output, MagicalContainer &_other);
    };

}
#endif // MAGICAL_CONTAINER_HPP
