#include "MagicalContainer.hpp"

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
            prime_set(set<int>(_other.prime_set)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other) noexcept {}

    MagicalContainer::~MagicalContainer() = default;

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        if (this != &_other) {
            this->og_set = _other.og_set;
            this->cross_vector = _other.cross_vector;
            this->prime_set = _other.prime_set;
        }
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&_other) noexcept {
        if (this != &_other) {
            this->og_set = _other.og_set;
            this->cross_vector = _other.cross_vector;
            this->prime_set = _other.prime_set;
        }
        return *this;
    }

    void MagicalContainer::addElement(int element) {
        bool clear_cross = this->og_set.contains(element);
        this->og_set.insert(element);
        if (isPrime(element)) {
            this->prime_set.insert(element);
        }
        if (clear_cross) {
            this->updateCross();
        }
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

    long MagicalContainer::size() const {
        return static_cast<long>(this->og_set.size());
    }

    void MagicalContainer::removeElement(int element) {
        bool clear_cross = this->og_set.contains(element);
        this->og_set.erase(element);
        this->prime_set.erase(element);
        if (clear_cross) {
            this->updateCross();
        }
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