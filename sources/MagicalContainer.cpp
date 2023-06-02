#include "MagicalContainer.hpp"

namespace ariel {


    bool MagicalContainer::is_prime(int num) {
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


    MagicalContainer::MagicalNode::MagicalNode(int val) :
            _value(val),
            _prime(is_prime(val)),
            _location(-1),
            next_prime(-1) {}

    bool operator>(const MagicalContainer::MagicalNode &_node1, const MagicalContainer::MagicalNode &_node2) {
        return _node1._value > _node2._value;
    }

    int MagicalContainer::MagicalNode::getValue() const { return _value; }

    bool MagicalContainer::MagicalNode::isPrime() const { return _prime; }

    long MagicalContainer::MagicalNode::getLocation() const { return _location; }

    long MagicalContainer::MagicalNode::getNextPrime() const { return next_prime; }

    void MagicalContainer::MagicalNode::setLocation(long location) { _location = location; }

    void MagicalContainer::MagicalNode::setNextPrime(long nextPrime) { next_prime = nextPrime; }

    bool operator==(const MagicalContainer::MagicalNode &_node1, const MagicalContainer::MagicalNode &_node2) {
        return _node1._value == _node2._value;
    }

    bool operator!=(const MagicalContainer::MagicalNode &_node1, const MagicalContainer::MagicalNode &_node2) {
        return _node1._value != _node2._value;
    }


    MagicalContainer::MagicalContainer() :
            _size(0),
            first_prime(-1) {}

    MagicalContainer::MagicalContainer(const MagicalContainer &_other) :
            _size(_other._size),
            container(vector<MagicalNode *>(_other.container)),
            first_prime(_other.first_prime) {}

    MagicalContainer::~MagicalContainer() {
        for (auto obj: this->container) {
            delete obj;
        }
    }

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        return *this;
    }

    void MagicalContainer::updatePrimes() {
        long prev_prime = -1;
        for (auto obj: this->container) {
            if (obj->isPrime()) {
                if (this->first_prime == -1 && prev_prime == -1) {
                    this->first_prime = obj->getLocation();
                } else {
                    this->container.at(static_cast<unsigned long>(prev_prime))->setNextPrime(obj->getLocation());
                }
                prev_prime = obj->getLocation();
            }
        }

    }

    long MagicalContainer::size() const {
        return static_cast<long>(this->container.size());
    }

    void MagicalContainer::addElement(int element) {
        for (auto obj: this->container) {
            if (obj->getValue() == element) {
                throw std::runtime_error("RUNTIME ERROR: Container already contains this element!");
                return;
            }
        }
        MagicalNode new_element(element);
        this->container.push_back(&new_element);
        std::sort(this->container.begin(), this->container.end());
        for (long i = 0; i < this->container.size(); ++i) {
            this->container.at(static_cast<unsigned long>(i))->setLocation(i);
        }
        this->updatePrimes();
        ++this->_size;
    }

    void MagicalContainer::removeElement(int element) {
        for (auto obj: this->container) {
            if (obj->getValue() > element) {
                return;
            } else if (obj->getValue() == element) {
                MagicalNode *temp = obj;
                this->container.erase(this->container.begin() + obj->getValue());
                if (temp->isPrime()) {
                    this->updatePrimes();
                }
                delete temp;
            }
        }
    }

    std::ostream &operator<<(ostream &output, MagicalContainer &_other) {
        output << "{ ";
        for (auto obj: _other.container) {
            output << obj->getValue() << " ";
        }
        output << "}";
        return output;
    }


}