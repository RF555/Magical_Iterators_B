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

    MagicalContainer::MagicalNode::MagicalNode(const MagicalContainer::MagicalNode &_other) {}

    MagicalContainer::MagicalNode::MagicalNode(MagicalContainer::MagicalNode &&_other) noexcept {}

    MagicalContainer::MagicalNode::~MagicalNode() = default;

    MagicalContainer::MagicalNode &
    MagicalContainer::MagicalNode::operator=(const MagicalContainer::MagicalNode &_other) {
        return *this;
    }

    MagicalContainer::MagicalNode &
    MagicalContainer::MagicalNode::operator=(MagicalContainer::MagicalNode &&_other) noexcept {
        return *this;
    }

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

    MagicalContainer::MagicalContainer(MagicalContainer &&_other) noexcept {}

    MagicalContainer::~MagicalContainer() {
        for (auto obj: this->container) {
            delete obj;
        }
    }

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&_other) noexcept {
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
//        for (auto obj: this->magical_container) {
//            if (obj->getValue() == element) {
//                throw std::runtime_error("RUNTIME ERROR: Container already contains this element!");
//                return;
//            }
//        }
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


    MagicalContainer::Iterator::Iterator(MagicalContainer &_container) :
            magical_container(_container),
            _index(0),
            curr_element(nullptr) {}

    MagicalContainer::Iterator::Iterator(MagicalContainer &_container, long index) :
            magical_container(_container),
            _index(index) {
        if (index < 0) {
            throw std::invalid_argument("INVALID ARGUMENT: Index must be >= 0!\n");
        }
        this->curr_element = _container.container.at(static_cast<unsigned long>(index));
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::begin() {
        return Iterator(this->magical_container, 0);
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::end() {
        return Iterator(this->magical_container, this->magical_container.size() - 1);
    }

    int MagicalContainer::Iterator::operator*() const {
        return this->curr_element->getValue();
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator++() {
        ++this->_index;
        this->curr_element = this->magical_container.container.at(static_cast<unsigned long>(this->_index));
        return *this;
    }

    bool operator==(const MagicalContainer::Iterator &_iter1, const MagicalContainer::Iterator &_iter2) {
        return _iter1.curr_element->getValue() == _iter2.curr_element->getValue();
    }

    bool operator!=(const MagicalContainer::Iterator &_iter1, const MagicalContainer::Iterator &_iter2) {
        return _iter1.curr_element->getValue() != _iter2.curr_element->getValue();
    }

    bool operator>(const MagicalContainer::Iterator &_iter1, const MagicalContainer::Iterator &_iter2) {
        return _iter1.curr_element->getValue() > _iter2.curr_element->getValue();

    }

    bool operator<(const MagicalContainer::Iterator &_iter1, const MagicalContainer::Iterator &_iter2) {
        return _iter1.curr_element->getValue() < _iter2.curr_element->getValue();

    }

    std::ostream &operator<<(ostream &output, MagicalContainer::Iterator &_other) {
        return output << _other.curr_element->getValue();
    }


}