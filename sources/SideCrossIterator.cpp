#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) :
            Iterator(container) {
        this->_curr_iter = container.cross_vector.begin();
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &_other) :
            Iterator(_other),
            _curr_iter(_other._curr_iter) {
        if (&this->getContainer() != &_other.getContainer()) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator &&_other) noexcept:
            Iterator(_other),
            _curr_iter(_other._curr_iter) {}

    MagicalContainer::SideCrossIterator::~SideCrossIterator() = default;

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &_other) {
        this->Iterator::operator=(_other);
        this->_curr_iter = _other._curr_iter;
        return *this;
    }

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &&_other) noexcept {
        if (this != &_other) {
            this->setContainer(_other.getContainer());
            this->setIndex(_other.getIndex());
            this->setElement(_other.getElement());
        }
        return *this;
    }


    MagicalContainer::Iterator &MagicalContainer::SideCrossIterator::operator++() {
        this->Iterator::operator++();
        ++this->_curr_iter;
        this->setElement(*this->_curr_iter);
        return *this;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, long index) :
            Iterator(container) {
        this->_curr_iter = container.cross_vector.begin();
        for (int i = 0; i < index; ++i) {
            this->Iterator::operator++();
            ++this->_curr_iter;
        }
        this->setElement(*this->_curr_iter);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return {this->getContainer(), 0};
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return {this->getContainer(), this->getContainer().size()};
    }


}
