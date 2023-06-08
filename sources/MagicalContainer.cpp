#include "MagicalContainer.hpp"

#include <cmath>

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
            cross_vector(vector<const Element_t *>(_other.cross_vector)),
            prime_vector(vector<const Element_t *>(_other.prime_vector)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other) noexcept {}

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
        Element_t new_element(element);
        bool exists = this->contains(new_element);
        auto inserted = this->og_set.insert(new_element);
        if (!exists && inserted.second) {

            this->updateAscendPrime(new_element._prime);

            this->updateCross();
        }
    }

    void MagicalContainer::updateAscendPrime(bool prime) {
        this->ascend_vector.clear();

        if (prime) {
            this->prime_vector.clear();
        }

        auto ascend_iter = this->og_set.begin();

        for (; ascend_iter != this->og_set.end(); ++ascend_iter) {
            this->ascend_vector.push_back(&(*ascend_iter));
            if (prime && ascend_iter->_prime) {
                this->prime_vector.push_back(&(*ascend_iter));
            }
        }
    }


    void MagicalContainer::updateCross() {
        this->cross_vector.clear();
        if (this->og_set.empty()) {
            return;
        }

        auto ascend_iter = this->og_set.begin();
        auto descend_iter = this->og_set.rbegin();

        while ((*ascend_iter)._element != (*descend_iter)._element) {
            this->cross_vector.push_back(&(*ascend_iter));
            ++ascend_iter;
            this->cross_vector.push_back(&(*descend_iter));
            if (*ascend_iter != *descend_iter) {
                ++descend_iter;
            }
        }

        if (this->og_set.size() % 2 != 0) {
            this->cross_vector.push_back(&(*ascend_iter));
        }
    }

    void MagicalContainer::removeElement(int element) {
        bool exists = this->contains(element);
        if (!exists) {
            throw std::runtime_error("RUNTIME ERROR: Element_t doesn't exist in the container!\n");
        } else {
            Element_t temp(element);
            this->og_set.erase(temp);

            updateAscendPrime(temp._prime);

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
            output << element._element << " ";
        }
        output << "}\t\t\tsize: " << _other.og_set.size() << "\n";

        output << "\tascend_vector: { ";
        for (auto element: _other.ascend_vector)
            cout << element->_element << " ";
        output << "}\t\tsize: " << _other.ascend_vector.size() << "\n";

        cout << "\tcross_vector: { ";
        for (auto element: _other.cross_vector)
            cout << element->_element << " ";
        output << "}\t\tsize: " << _other.cross_vector.size() << "\n";

        cout << "\tprime_vector: { ";
        for (auto element: _other.prime_vector)
            cout << element->_element << " ";
        output << "}\t\tsize: " << _other.prime_vector.size() << "\n";

        return output;
    }

    void MagicalContainer::printVector(vector<const Element_t *> &_vec) {
        cout << "{ ";
        for (auto element: _vec) {
            cout << element->_element << " ";
        }
        cout << "}  size: " << _vec.size() << "\n";
    }

    void MagicalContainer::printOG() {
        cout << "og_set: { ";
        for (auto element: this->og_set) {
            cout << element._element << " ";
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

    bool MagicalContainer::contains(Element_t &element) {
        return this->og_set.contains(element);
    }

    bool MagicalContainer::contains(int element) {
        Element_t temp(element);
        return this->og_set.contains(temp);
    }

}


