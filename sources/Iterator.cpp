#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer &my_container) :
            _container(my_container),
            _index(0) {}

    MagicalContainer::Iterator::Iterator(const ariel::MagicalContainer::Iterator &_other) :
            _container(_other._container),
            _index(_other._index) {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
    }

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer::Iterator &&_other) noexcept:
            _container(_other._container),
            _index(_other._index) {}

    MagicalContainer::Iterator::~Iterator() = default;

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(const MagicalContainer::Iterator &_other) {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (this != &_other) {
            if (&this->_container != &_other._container) {
                throw std::runtime_error("RUNTIME ERROR: have of the same container!\n");
            }
            this->_index = _other._index;
            this->_element = _other._element;
        }
        return *this;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(MagicalContainer::Iterator &&_other) noexcept {
        if (this != &_other) {
            this->_container = _other._container;
            this->_index = _other._index;
            this->_element = _other._element;
        }
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const MagicalContainer::Iterator &_other) const {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_element == _other._element;
    }

    bool MagicalContainer::Iterator::operator!=(const MagicalContainer::Iterator &_other) const {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_element != _other._element;
    }

    bool MagicalContainer::Iterator::operator>(const MagicalContainer::Iterator &_other) const {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::Iterator::operator<(const MagicalContainer::Iterator &_other) const {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index < _other._index;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::Iterator &_other) {
        return output << _other._element;
    }

    int MagicalContainer::Iterator::operator*() const {
        return this->_element;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator++() {
        ++this->_index;
        return *this;
    }

    MagicalContainer &MagicalContainer::Iterator::getContainer() const {
        return _container;
    }

    void MagicalContainer::Iterator::setContainer(MagicalContainer &container) {
        _container = container;
    }

    int MagicalContainer::Iterator::getElement() const {
        return _element;
    }

    void MagicalContainer::Iterator::setElement(int element) {
        _element = element;
    }

    long MagicalContainer::Iterator::getIndex() const {
        return _index;
    }

    void MagicalContainer::Iterator::setIndex(long index) {
        _index = index;
    }

}
