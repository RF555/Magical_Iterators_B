#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) :
            Iterator(container, container.ascend_vector) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer::AscendingIterator &_other) :
            Iterator(_other) {
        if (&this->getContainer() != &_other.getContainer()) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator &&_other) noexcept:
            Iterator(_other) {}

    MagicalContainer::AscendingIterator::~AscendingIterator() = default;

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator &_other) {
        this->Iterator::operator=(_other);
        return *this;
    }

    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&_other) noexcept {
        if (this != &_other) {
            this->setContainer(_other.getContainer());
            this->setIndex(_other.getIndex());
            this->setVecRef(_other.getVecRef());
            this->setCurrIter(_other.getCurrIter());
        }
        return *this;
    }

    MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &_other, unsigned long index) :
            Iterator(_other, index) {}

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
        return AscendingIterator(*this, 0);
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
        if(this->getVecRef().empty()){
            return AscendingIterator(*this, 0);
        }
        return AscendingIterator(*this, this->getVecRef().size() - 1);
    }

    MagicalContainer::Iterator &MagicalContainer::AscendingIterator::operator++() {
        if (*this == this->end()) {
            throw std::runtime_error("RUNTIME ERROR: Can not iterate past the last _element!\n");
        }
        return Iterator::operator++();
    }
}
