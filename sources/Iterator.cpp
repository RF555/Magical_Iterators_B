#include "MagicalContainer.hpp"


using namespace std;

namespace ariel {

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer &my_container, vector<const Element_t *> &vec) :
            _container(my_container),
            _index(0),
            _vec_ref(vec) {
        this->_curr_iter = vec.begin();
    }

    MagicalContainer::Iterator::Iterator(const ariel::MagicalContainer::Iterator &_other) :
            _container(_other._container),
            _index(_other._index),
            _vec_ref(_other._vec_ref),
            _curr_iter(_other._curr_iter) {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Both iterators must be of the same type!\n"));
        }
    }

    MagicalContainer::Iterator::Iterator(ariel::MagicalContainer::Iterator &&_other) noexcept:
            _container(_other._container),
            _index(_other._index),
            _vec_ref(_other._vec_ref),
            _curr_iter(_other._curr_iter) {}

    MagicalContainer::Iterator::~Iterator() = default;

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(const MagicalContainer::Iterator &_other) {
        if (typeid(this) != typeid(_other)) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Both iterators must be of the same type!\n"));
        }
        if (this != &_other) {
            if (&this->_container != &_other._container) {
                throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "have of the same container!\n"));
            }
            this->_index = _other._index;
            this->_vec_ref = _other._vec_ref;
            this->_curr_iter = _other._curr_iter;
        }
        return *this;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(MagicalContainer::Iterator &&_other) noexcept {
        if (this != &_other) {
            this->_container = _other._container;
            this->_index = _other._index;
            this->_vec_ref = _other._vec_ref;
            this->_curr_iter = _other._curr_iter;
        }
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Both iterators must be of the same type!\n"));
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Must have the same container!\n"));
        }
        if (this->_vec_ref.empty()) {
            return true;
        }
        return this->_curr_iter == _other._curr_iter;
    }

    bool MagicalContainer::Iterator::operator!=(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Both iterators must be of the same type!\n"));
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Must have the same container!\n"));
        }
        if (this->_vec_ref.empty()) {
            return false;
        }
        return this->_curr_iter != _other._curr_iter;
    }

    bool MagicalContainer::Iterator::operator>(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Both iterators must be of the same type!\n"));
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Must have the same container!\n"));
        }
        if (this->_vec_ref.empty()) {
            return false;
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::Iterator::operator<(const MagicalContainer::Iterator &_other) const {
        if (typeid(*this) != typeid(_other)) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Both iterators must be of the same type!\n"));
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Must have the same container!\n"));
        }
        if (this->_vec_ref.empty()) {
            return false;
        }
        return this->_index < _other._index;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::Iterator &_other) {
        return output << *_other._curr_iter;
    }

    int MagicalContainer::Iterator::operator*() const {
        return (*this->_curr_iter)->_element;
    }

    MagicalContainer::Iterator &MagicalContainer::Iterator::operator++() {
        if (this->_curr_iter == this->_vec_ref.end()) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Can not iterate past the last element!\\n"));
        }
        ++this->_index;
        ++this->_curr_iter;
        return *this;
    }

    MagicalContainer &MagicalContainer::Iterator::getContainer() const {
        return _container;
    }

    void MagicalContainer::Iterator::setContainer(MagicalContainer &container) {
        this->_container = container;
    }

    int MagicalContainer::Iterator::getElement() const {
        return (*this->_curr_iter)->_element;
    }

    unsigned long MagicalContainer::Iterator::getIndex() const {
        return _index;
    }

    void MagicalContainer::Iterator::setIndex(unsigned long index) {
        this->_index = index;
    }

    vector<const MagicalContainer::Element_t *> MagicalContainer::Iterator::getVecRef() const {
        return this->_vec_ref;
    }

    void MagicalContainer::Iterator::setVecRef(vector<const Element_t *> vecRef) {
        _vec_ref = vecRef;
    }

    vector<const MagicalContainer::Element_t *>::iterator &MagicalContainer::Iterator::getCurrIter() {
        return _curr_iter;
    }

    void MagicalContainer::Iterator::setCurrIter(vector<const MagicalContainer::Element_t *>::iterator &currIter) {
        _curr_iter = currIter;
    }

    MagicalContainer::Iterator::Iterator(Iterator &_other, unsigned long index) :
            _container(_other._container),
            _vec_ref(_other._vec_ref) {
        if (_other._vec_ref.empty()) {
            this->_index = 0;
            this->_curr_iter = _other._vec_ref.begin();
        } else if (index >= _other._vec_ref.size()) {
            throw std::runtime_error(getErrorMessage("RUNTIME ERROR", "Index out of range!\n"));
        } else if (index == _other._vec_ref.size() - 1) {
            this->_curr_iter = _other._vec_ref.end();
        } else if (index == 0) {
            this->_curr_iter = _other._vec_ref.begin();
        } else {
            this->_curr_iter = _other._vec_ref.begin();
            for (int i = 0; i < index; ++i) {
                ++this->_curr_iter;
            }
        }
    }

//    MagicalContainer::Iterator MagicalContainer::Iterator::begin() {
//        return {*this, 0};
//    }
//
//    MagicalContainer::Iterator MagicalContainer::Iterator::end() {
//        return {*this, this->_vec_ref.size()};
//    }

}
