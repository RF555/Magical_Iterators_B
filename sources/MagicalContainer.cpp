#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>
#include <typeinfo>

namespace ariel {

    bool isPrime(int num) {
        if (num <= 1) {
            return false;
        }

        if (num <= 3) {
            return true;
        }

        if (num % 2 == 0 || num % 3 == 0) {
            return false;
        }

        for (int i = 5; i * i <= num; i = i + 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }

        return true;
    }

    MagicalContainer::MagicalContainer() = default;

    MagicalContainer::MagicalContainer(const ariel::MagicalContainer &_other) :
            og_set(_other.og_set),
            cross_vector(vector<int>(_other.cross_vector)),
            prime_vector(set<int>(_other.prime_vector)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other)

    noexcept {
    }

    MagicalContainer::~MagicalContainer() = default;

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        if (this != &_other) {
            this->og_set = _other.og_set;
            this->cross_vector = _other.cross_vector;
            this->prime_vector = _other.prime_vector;
        }
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&_other) noexcept {
        if (this != &_other) {
            this->og_set = _other.og_set;
            this->cross_vector = _other.cross_vector;
            this->prime_vector = _other.prime_vector;
        }
        return *this;
    }

    void MagicalContainer::addElement(int element) {
        bool exists = this->og_set.contains(element);
        this->og_set.insert(element);
        if (!exists) {
            updateAscend();

            if (isPrime(element)) {
                this->prime_vector.push_back(element);
                std::sort(this->prime_vector.begin(), this->prime_vector.end());
            }

            this->updateCross();
        }
    }

    void MagicalContainer::updateAscend() {
        this->ascend_vector.clear();
        copy(this->og_set.begin(), this->og_set.end(), this->ascend_vector.begin());
    }

    void MagicalContainer::updateCross() {
        this->cross_vector.clear();
        auto ascend_iter = this->og_set.begin();
        auto descend_iter = this->og_set.end();
        while (ascend_iter != descend_iter) {
            this->cross_vector.push_back(*ascend_iter);
            ++ascend_iter;
            this->cross_vector.push_back(*descend_iter);
            --descend_iter;
        }
    }

    void MagicalContainer::removeElement(int element) {
        bool exists = this->og_set.contains(element);
        this->og_set.erase(element);
        if (!exists) {
            std::remove(this->ascend_vector.begin(), this->ascend_vector.end(), element);

            if (isPrime(element)) {
                std::remove(this->prime_vector.begin(), this->prime_vector.end(), element);
            }

            this->updateCross();
        }
    }

    unsigned long MagicalContainer::size() const {
        return this->og_set.size();
    }

    std::ostream &operator<<(ostream &output, MagicalContainer &_other) {
        output << "{ ";
        for (auto element: _other.og_set) {
            output << element << " ";
        }
        output << "}";
        return output;
    }


}






