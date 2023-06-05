#include "MagicalContainer.hpp"

#include <typeinfo>

using namespace std;

namespace ariel {

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) :
            Iterator(container) {
        this->_curr_iter = container.og_set.begin();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &_other) :
            Iterator(_other),
            _curr_iter(_other._curr_iter) {
        if (&this->getContainer() != &_other.getContainer()) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator &&_other) noexcept:
            Iterator(_other),
            _curr_iter(_other._curr_iter) {}

    MagicalContainer::AscendingIterator::~AscendingIterator() = default;


    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &_other) {
        this->Iterator::operator=(_other);
        this->_curr_iter = _other._curr_iter;
        return *this;
    }

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&_other) noexcept {
        if (this != &_other) {
            this->setContainer(_other.getContainer());
            this->setIndex(_other.getIndex());
            this->setElement(_other.getElement());
        }
        return *this;
    }

    MagicalContainer::Iterator &MagicalContainer::AscendingIterator::operator++() {
        this->Iterator::operator++();
        ++this->_curr_iter;
        this->setElement(*this->_curr_iter);
        return *this;
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, long index) :
            Iterator(container) {
        this->_curr_iter = container.og_set.begin();
        for (int i = 0; i < index; ++i) {
            this->Iterator::operator++();
            ++this->_curr_iter;
        }
        this->setElement(*this->_curr_iter);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return {this->getContainer(), 0};
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        return {this->getContainer(), this->getContainer().size()};
    }


}
