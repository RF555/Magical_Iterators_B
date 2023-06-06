#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer &my_container, vector<int> &vec) :
            _container(my_container),
            _index(0),
            _vec_ptr(vec) {
        this->_curr_iter = vec.begin();
    }

    MagicalContainer::Iterator::Iterator(const ariel::MagicalContainer::Iterator &_other) :
            _container(_other._container),
            _index(_other._index),
            _vec_ptr(_other._vec_ptr),
            _curr_iter(_other._curr_iter) {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
    }

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer::Iterator &&_other) noexcept:
            _container(_other._container),
            _index(_other._index),
            _vec_ptr(_other._vec_ptr),
            _curr_iter(_other._curr_iter) {}

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
            this->_vec_ptr = _other._vec_ptr;
            this->_curr_iter = _other._curr_iter;
        }
        return *this;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(MagicalContainer::Iterator &&_other) noexcept {
        if (this != &_other) {
            this->_container = _other._container;
            this->_index = _other._index;
            this->_vec_ptr = _other._vec_ptr;
            this->_curr_iter = _other._curr_iter;
        }
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *_other._curr_iter;
    }

    bool MagicalContainer::Iterator::operator!=(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *_other._curr_iter;
    }

    bool MagicalContainer::Iterator::operator>(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::Iterator::operator<(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index < _other._index;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::Iterator &_other) {
        return output << *_other._curr_iter;
    }

    int MagicalContainer::Iterator::operator*() const {
        return *this->_curr_iter;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator++() {
        if (*this == this->end()) {
            throw std::runtime_error("RUNTIME ERROR: Can not iterate past the last element!\n");
        }
        ++this->_index;
        ++this->_curr_iter;
        return *this;
    }

    MagicalContainer &MagicalContainer::Iterator::getContainer() const {
        if (this->_index >= this->_container.size()) {
            throw std::runtime_error("RUNTIME ERROR: Out of range!\n");
        }
        return _container;
    }

    void MagicalContainer::Iterator::setContainer(MagicalContainer &container) {
        this->_container = container;
    }

    int MagicalContainer::Iterator::getElement() const {
        return *this->_curr_iter;
    }

    unsigned long MagicalContainer::Iterator::getIndex() const {
        return _index;
    }

    void MagicalContainer::Iterator::setIndex(unsigned long index) {
        this->_index = index;
    }

    vector<int> &MagicalContainer::Iterator::getVecPtr() const {
        return _vec_ptr;
    }

    void MagicalContainer::Iterator::setVecPtr(vector<int> &vecPtr) {
        _vec_ptr = vecPtr;
    }

    const vector<int>::iterator &MagicalContainer::Iterator::getCurrIter() const {
        return _curr_iter;
    }

    void MagicalContainer::Iterator::setCurrIter(const vector<int>::iterator &currIter) {
        _curr_iter = currIter;
    }

    MagicalContainer::Iterator::Iterator(Iterator &_other, unsigned long index) :
            _container(_other._container),
            _index(index),
            _vec_ptr(_other._vec_ptr) {
        if (index == _other._vec_ptr.size() - 1) {
            this->_curr_iter = _other._vec_ptr.end();
        } else if (index == 0) {
            this->_curr_iter = _other._vec_ptr.begin();
        } else {
            this->_curr_iter = _other._vec_ptr.begin();
            for (int i = 0; i < index; ++i) {
                ++this->_curr_iter;
            }
        }
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::begin() {
        return {*this, 0};
    }

    MagicalContainer::Iterator MagicalContainer::Iterator::end() {
        return {*this, this->_vec_ptr.size()};
    }

}
