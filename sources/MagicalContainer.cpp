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
            prime_vector(vector<int>(_other.prime_vector)) {}

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
        for (auto it: this->og_set) {
            this->ascend_vector.push_back(it);
        }
    }

    void MagicalContainer::updateCross() {
        this->cross_vector.clear();
        auto ascend_iter = this->og_set.begin();
        auto descend_iter = this->og_set.rbegin();

        while (*ascend_iter != *descend_iter) {
            this->cross_vector.push_back(*ascend_iter);
            ++ascend_iter;
            this->cross_vector.push_back(*descend_iter);
            if (*ascend_iter != *descend_iter) {
                ++descend_iter;
            }
        }

        if (this->og_set.size() % 2 != 0) {
            this->cross_vector.push_back(*ascend_iter);
        }
    }

    void MagicalContainer::removeElement(int element) {
        bool exists = this->og_set.contains(element);
        if (!exists) {
            throw std::runtime_error("RUNTIME ERROR: Element doesn't exist in the container!\n");
        }else{
            this->og_set.erase(element);
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
        output << "MagicalContainer:\n";

        output << "\tog_set: { ";
        for (auto element: _other.og_set) {
            output << element << " ";
        }
        output << "}\t\t\tsize: " << _other.og_set.size() << "\n";

        output << "\tascend_vector: { ";
        for (auto element: _other.ascend_vector)
            cout << element << " ";
        output << "}\t\tsize: " << _other.ascend_vector.size() << "\n";

        cout << "\tcross_vector: { ";
        for (auto element: _other.cross_vector)
            cout << element << " ";
        output << "}\t\tsize: " << _other.cross_vector.size() << "\n";

        cout << "\tprime_vector: { ";
        for (auto element: _other.prime_vector)
            cout << element << " ";
        output << "}\t\tsize: " << _other.prime_vector.size() << "\n";

        return output;
    }

    ostream &streamVector(ostream &output, vector<int> &_vec) {
        output << "{ ";
        for (auto element: _vec) {
            cout << element << " ";
        }
        output << "}  size: " << _vec.size() << "\n";
        return output;
    }

    void MagicalContainer::printVector(vector<int> &_vec) {
        cout << "{ ";
        for (auto element: _vec) {
            cout << element << " ";
        }
        cout << "}  size: " << _vec.size() << "\n";
    }

    void MagicalContainer::printOG() {
        cout << "og_set: { ";
        for (auto element: this->og_set) {
            cout << element << " ";
        }
        cout << "}  size: " << this->og_set.size() << "\n";
    }

    void MagicalContainer::printAscend() {
        cout << "ascend_vector: ";
        printVector(this->ascend_vector);
    }

    void MagicalContainer::printCross() {
        cout << "cross_vector: ";
        printVector(this->cross_vector);
    }

    void MagicalContainer::printPrime() {
        cout << "prime_vector: ";
        printVector(this->prime_vector);
    }


}






