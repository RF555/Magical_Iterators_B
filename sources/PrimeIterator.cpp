#include "MagicalContainer.hpp"

using namespace std;

namespace ariel {

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) :
            Iterator(container, container.prime_vector) {}

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &_other) :
            Iterator(_other) {
        if (&this->getContainer() != &_other.getContainer()) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer::PrimeIterator &&_other) noexcept:
            Iterator(_other) {}

    MagicalContainer::PrimeIterator::~PrimeIterator() = default;

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator &_other) {
        this->Iterator::operator=(_other);
        return *this;
    }

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator &&_other) noexcept {
        if (this != &_other) {
            this->setContainer(_other.getContainer());
            this->setIndex(_other.getIndex());
            this->setVecRef(_other.getVecRef());
            this->setCurrIter(_other.getCurrIter());
        }
        return *this;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &_other, unsigned long index) :
            Iterator(_other, index) {}

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return PrimeIterator(*this, 0);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return PrimeIterator(*this, this->getVecRef().size() - 1);
    }
    MagicalContainer::Iterator &MagicalContainer::PrimeIterator::operator++() {
        return Iterator::operator++();
    }

}
