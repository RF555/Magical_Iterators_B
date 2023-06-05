#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) :
            Iterator(ASCENDING_ITER),
            _container(container),
            _index(0) {
        this->_curr_iter = container.og_set.begin();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &_other) :
            Iterator(_other.getType()),
            _container(_other._container),
            _index(0),
            _curr_iter(_other._curr_iter) {
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator &&_other)

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

    MagicalContainer::AscendingIterator::~AscendingIterator() = default;

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &_other) {
        if (this != &_other) {
            if (&this->_container != &_other._container) {
                throw std::runtime_error("RUNTIME ERROR: have of the same container!\n");
            }
            this->_index = _other._index;
        }
        return *this;
    }

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&_other)

    noexcept {
        if (this != &_other) {
            this->
                    _container = _other._container;
            this->
                    _index = _other._index;
        }
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::AscendingIterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *_other._curr_iter;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::AscendingIterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *_other._curr_iter;
    }

    bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index < _other._index;
    }

    bool MagicalContainer::AscendingIterator::operator==(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *cast_other->_curr_iter;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *cast_other->_curr_iter;
    }

    bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const AscendingIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    int MagicalContainer::AscendingIterator::operator*() const {
        return *this->_curr_iter;
    }

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (this->_index >= this->_container.size()) {
            throw std::runtime_error("RUNTIME ERROR: Out of range!\n");
        }
        ++this->_index;
        ++this->_curr_iter;
        return *this;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::AscendingIterator &_other) {
        return output << *_other._curr_iter;
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, long index) :
            Iterator(this->getType()),
            _container(container),
            _index(index) {
        this->_curr_iter = container.og_set.begin();
        for (int i = 0; i < index; ++i) {
            ++_curr_iter;
        }
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return {this->_container, 0};
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return {this->_container, this->_container.size()};
    }


}
