#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) :
            Iterator(PRIME_ITER),
            _container(container),
            _index(0) {
        this->_curr_iter = container.prime_set.begin();
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &_other) :
            Iterator(_other.getType()),
            _container(_other._container),
            _index(0),
            _curr_iter(_other._curr_iter) {
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer::PrimeIterator &&_other)

    noexcept:
            Iterator(_other
                             .

                                     getType()

            ),
            _container(_other
                               ._container),
            _index(_other
                           ._index),
            _curr_iter(_other
                               ._curr_iter) {
    }

    MagicalContainer::PrimeIterator::~PrimeIterator() = default;

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator &_other) {
        if (this != &_other) {
            if (&this->_container != &_other._container) {
                throw std::runtime_error("RUNTIME ERROR: have of the same container!\n");
            }
            this->_index = _other._index;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator &&_other)

    noexcept {
        if (this != &_other) {
            this->
                    _container = _other._container;
            this->
                    _index = _other._index;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *_other._curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *_other._curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index < _other._index;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *cast_other->_curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *cast_other->_curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        return *this->_curr_iter;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (this->_index >= this->_container.size()) {
            throw std::runtime_error("RUNTIME ERROR: Out of range!\n");
        }
        ++this->_index;
        ++this->_curr_iter;
        return *this;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::PrimeIterator &_other) {
        return output << *_other._curr_iter;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, long index) :
            Iterator(this->getType()),
            _container(container),
            _index(index) {
        this->_curr_iter = container.og_set.begin();
        for (int i = 0; i < index; ++i) {
            ++_curr_iter;
        }
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return {this->_container, 0};
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return {this->_container, this->_container.size()};
    }

}
