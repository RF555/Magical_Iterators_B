#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) :
            Iterator(CROSS_ITER),
            _container(container),
            _index(0) {
        this->_curr_iter = container.cross_vector.begin();
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &_other) :
            Iterator(_other.getType()),
            _container(_other._container),
            _index(0),
            _curr_iter(_other._curr_iter) {
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator &&_other)

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

    MagicalContainer::SideCrossIterator::~SideCrossIterator() = default;

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &_other) {
        if (this != &_other) {
            if (&this->_container != &_other._container) {
                throw std::runtime_error("RUNTIME ERROR: have of the same container!\n");
            }
            this->_index = _other._index;
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &&_other)

    noexcept {
        if (this != &_other) {
            this->
                    _container = _other._container;
            this->
                    _index = _other._index;
        }
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::SideCrossIterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *_other._curr_iter;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::SideCrossIterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *_other._curr_iter;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::SideCrossIterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::SideCrossIterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index < _other._index;
    }

    bool MagicalContainer::SideCrossIterator::operator==(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *cast_other->_curr_iter;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *cast_other->_curr_iter;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const SideCrossIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    int MagicalContainer::SideCrossIterator::operator*() const {
        return *this->_curr_iter;
    }

    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (this->_index >= this->_container.size()) {
            throw std::runtime_error("RUNTIME ERROR: Out of range!\n");
        }
        ++this->_index;
        ++this->_curr_iter;
        return *this;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::SideCrossIterator &_other) {
        return output << *_other._curr_iter;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, long index) :
            Iterator(this->getType()),
            _container(container),
            _index(index) {
        this->_curr_iter = container.cross_vector.begin();
        for (int i = 0; i < index; ++i) {
            ++_curr_iter;
        }
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return {this->_container, 0};
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return {this->_container, this->_container.size()};
    }


}
