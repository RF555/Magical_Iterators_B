#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) :
            Iterator(container, container.cross_vector) {}

    MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer::SideCrossIterator &_other) :
            Iterator(_other) {
        if (&this->getContainer() != &_other.getContainer()) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator &&_other) noexcept:
            Iterator(_other) {}

    MagicalContainer::SideCrossIterator::~SideCrossIterator() = default;

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator &_other) {
        this->Iterator::operator=(_other);
        return *this;
    }

    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &&_other) noexcept {
        if (this != &_other) {
            this->setContainer(_other.getContainer());
            this->setIndex(_other.getIndex());
            this->setVecRef(_other.getVecRef());
            this->setCurrIter(_other.getCurrIter());
        }
        return *this;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &_other, unsigned long index) :
            Iterator(_other, index) {}

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
        return SideCrossIterator(*this, 0);
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
        return SideCrossIterator(*this, this->getVecRef().size() - 1);
    }
    MagicalContainer::Iterator &MagicalContainer::SideCrossIterator::operator++() {
        return Iterator::operator++();
    }

}
