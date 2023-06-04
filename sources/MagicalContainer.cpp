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
            : ascending_vector(vector<int>(_other.ascending_vector)),
              cross_vector(vector<int>(_other.cross_vector)),
              prime_vector(vector<int>(_other.prime_vector)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other) noexcept {}

    MagicalContainer::~MagicalContainer() = default;

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&_other) noexcept {
        return *this;
    }

    void MagicalContainer::addElement(int element) {
        this->ascending_vector.push_back(element);
        std::sort(this->ascending_vector.begin(), this->ascending_vector.end());

        this->cross_vector.push_back(element);
        updateCross();

        if (isPrime(element)) {
            this->prime_vector.push_back(element);
            std::sort(this->prime_vector.begin(), this->prime_vector.end());
        }
    }

    long MagicalContainer::size() const {
        return static_cast<long>(this->ascending_vector.size());
    }

    void MagicalContainer::removeElement(int element) {
        std::remove(this->ascending_vector.begin(), this->ascending_vector.end(), element);
        std::remove(this->cross_vector.begin(), this->cross_vector.end(), element);
        std::remove(this->prime_vector.begin(), this->prime_vector.end(), element);

    }

    std::ostream &operator<<(ostream &output, MagicalContainer &_other) {
        output << "{ ";
        for (auto element: _other.ascending_vector) {
            output << element << " ";
        }
        output << "}";
        return output;
    }


}