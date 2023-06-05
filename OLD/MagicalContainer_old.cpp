#include "MagicalContainer_old.hpp"


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
        _index(-1),
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

long MagicalContainer::MagicalNode::getIndex() const { return _index; }

long MagicalContainer::MagicalNode::getNextPrime() const { return next_prime; }

void MagicalContainer::MagicalNode::setIndex(long location) { _index = location; }

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
                this->first_prime = obj->getIndex();
            } else {
                this->container.at(static_cast<unsigned long>(prev_prime))->setNextPrime(obj->getIndex());
            }
            prev_prime = obj->getIndex();
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
        this->container.at(static_cast<unsigned long>(i))->setIndex(i);
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

MagicalContainer::MagicalNode *MagicalContainer::at(long index) {
    if (index < 0) {
        throw std::invalid_argument("INVALID ARGUMENT: Index must be >= 0!\n");
    }
    return this->container.at(static_cast<unsigned long>(index));
}

std::ostream &operator<<(ostream &output, MagicalContainer &_other) {
    output << "{ ";
    for (auto obj: _other.container) {
        output << obj->getValue() << " ";
    }
    output << "}";
    return output;
}


/*****************************************************
 ***************** AscendingIterator *****************
 *****************************************************/


MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &_container) :
        magical_container(_container),
        curr_element(nullptr) {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &_container, long index) :
        magical_container(_container) {
    if (index < 0) {
        throw std::invalid_argument("INVALID ARGUMENT: Index must be >= 0!\n");
    }
    this->curr_element = _container.container.at(static_cast<unsigned long>(index));
}

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &_other)
        : magical_container(_other.magical_container),
          curr_element(_other.curr_element) {}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator &&_other) noexcept
        : magical_container(_other.magical_container),
          curr_element(_other.curr_element) {}

MagicalContainer::AscendingIterator::~AscendingIterator() = default;


MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &_other) {
    if (&(this->magical_container) != &(_other.magical_container)) {
        throw std::runtime_error("RUNTIME ERROR: Must be of the same container!\n");
    }
    if (this != &_other) {

        this->curr_element = _other.curr_element;
    }
    return *this;
}

MagicalContainer::AscendingIterator &
MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&_other) noexcept {
    return *this;
}

MagicalContainer &MagicalContainer::AscendingIterator::getMagicalContainer() const {
    return magical_container;
}

void MagicalContainer::AscendingIterator::setMagicalContainer(MagicalContainer &magicalContainer) {
    magical_container = magicalContainer;
}

long MagicalContainer::AscendingIterator::getIndex() const { return this->curr_element->getIndex(); }

MagicalContainer::MagicalNode *MagicalContainer::AscendingIterator::getCurrElement() const { return curr_element; }

void MagicalContainer::AscendingIterator::setCurrElement(MagicalContainer::MagicalNode *currElement) {
    curr_element = currElement;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
    return AscendingIterator(this->magical_container, 0);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    return AscendingIterator(this->magical_container, this->magical_container.size() - 1);
}

int MagicalContainer::AscendingIterator::operator*() const {
    return this->curr_element->getValue();
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
    this->curr_element = this->magical_container.at(this->getIndex());
    return *this;
}

bool
operator==(const MagicalContainer::AscendingIterator &_iter1, const MagicalContainer::AscendingIterator &_iter2) {
    if (typeid(_iter1) != typeid(_iter2)) {
        throw std::invalid_argument("INVALID ARGUMENT: Both iterators must be of the same type!\n");
    }
    return _iter1.curr_element == _iter2.curr_element;
}

bool
operator!=(const MagicalContainer::AscendingIterator &_iter1, const MagicalContainer::AscendingIterator &_iter2) {
    if (typeid(_iter1) != typeid(_iter2)) {
        throw std::invalid_argument("INVALID ARGUMENT: Both iterators must be of the same type!\n");
    }
    return _iter1.curr_element != _iter2.curr_element;
}

bool
operator>(const MagicalContainer::AscendingIterator &_iter1, const MagicalContainer::AscendingIterator &_iter2) {
    if (typeid(_iter1) != typeid(_iter2)) {
        throw std::invalid_argument("INVALID ARGUMENT: Both iterators must be of the same type!\n");
    }
    return _iter1.curr_element->getValue() > _iter2.curr_element->getValue();
}

bool
operator<(const MagicalContainer::AscendingIterator &_iter1, const MagicalContainer::AscendingIterator &_iter2) {
    if (typeid(_iter1) != typeid(_iter2)) {
        throw std::invalid_argument("INVALID ARGUMENT: Both iterators must be of the same type!\n");
    }
    return _iter1.curr_element->getValue() < _iter2.curr_element->getValue();
}

std::ostream &operator<<(ostream &output, MagicalContainer::AscendingIterator &_other) {
    output << "Index: " << _other.getIndex() << "\telement value: ";
    return output << _other.curr_element->getValue();
}


/*****************************************************
 ***************** SideCrossIterator *****************
 *****************************************************/


MagicalContainer &MagicalContainer::SideCrossIterator::getMagicalContainer() const {
    return magical_container;
}

void MagicalContainer::SideCrossIterator::setMagicalContainer(MagicalContainer &magicalContainer) {
    magical_container = magicalContainer;
}

MagicalContainer::MagicalNode *MagicalContainer::SideCrossIterator::getCurrAscending() const {
    return curr_ascending;
}

void MagicalContainer::SideCrossIterator::setCurrAscending(MagicalContainer::MagicalNode *currAscending) {
    curr_ascending = currAscending;
}

MagicalContainer::MagicalNode *MagicalContainer::SideCrossIterator::getCurrDescending() const {
    return curr_descending;
}

void MagicalContainer::SideCrossIterator::setCurrDescending(MagicalContainer::MagicalNode *currDescending) {
    curr_descending = currDescending;
}

long MagicalContainer::SideCrossIterator::getAscendingIndex() {
    return this->curr_ascending->getIndex();
}

long MagicalContainer::SideCrossIterator::getDescendingIndex() {
    return this->curr_descending->getIndex();

}