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

    MagicalContainer::MagicalContainer() {}

    MagicalContainer::MagicalContainer(const ariel::MagicalContainer &_other)
            : ascending_container(vector<int>(_other.ascending_container)),
              cross_container(vector<int>(_other.cross_container)),
              prime_container(vector<int>(_other.prime_container)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other) noexcept {}

    MagicalContainer::~MagicalContainer() = default;

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&_other) noexcept {
        return *this;
    }

    void MagicalContainer::addElement(int element) {
        this->ascending_container.push_back(element);
        std::sort(this->ascending_container.begin(), this->ascending_container.end());

        this->cross_container.push_back(element);
        updateCross();

        if (isPrime(element)) {
            this->prime_container.push_back(element);
            std::sort(this->prime_container.begin(), this->prime_container.end());
        }
    }

    long MagicalContainer::size() const {
        return static_cast<long>(this->ascending_container.size());
    }

    void MagicalContainer::removeElement(int element) {
        std::remove(this->ascending_container.begin(), this->ascending_container.end(), element);
        std::remove(this->cross_container.begin(), this->cross_container.end(), element);
        std::remove(this->prime_container.begin(), this->prime_container.end(), element);

    }

    std::ostream &operator<<(ostream &output, MagicalContainer &_other) {
        output << "{ ";
        for (auto element: _other.ascending_container) {
            output << element << " ";
        }
        output << "}";
        return output;
    }


}