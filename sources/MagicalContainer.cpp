#include "MagicalContainer.hpp"
#include <algorithm>
#include <cmath>
#include <typeinfo>

namespace ariel {

    bool isPrime(int num) {
        if (num <= 1) {
            return false;
        }

        if (num <= 3) {
            return true;
        }

        if (num % 2 == 0 || num % 3 == 0) {
            return false;
        }

        for (int i = 5; i * i <= num; i = i + 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }

        return true;
    }

    MagicalContainer::MagicalContainer() = default;

    MagicalContainer::MagicalContainer(const ariel::MagicalContainer &_other) :
            og_set(_other.og_set),
            cross_vector(vector<int>(_other.cross_vector)),
            prime_set(set<int>(_other.prime_set)) {}

    MagicalContainer::MagicalContainer(ariel::MagicalContainer &&_other) noexcept {}

    MagicalContainer::~MagicalContainer() = default;

    MagicalContainer &MagicalContainer::operator=(const MagicalContainer &_other) {
        if (this != &_other) {
            this->og_set = _other.og_set;
            this->cross_vector = _other.cross_vector;
            this->prime_set = _other.prime_set;
        }
        return *this;
    }

    MagicalContainer &MagicalContainer::operator=(MagicalContainer &&_other) noexcept {
        if (this != &_other) {
            this->og_set = _other.og_set;
            this->cross_vector = _other.cross_vector;
            this->prime_set = _other.prime_set;
        }
        return *this;
    }

    void MagicalContainer::addElement(int element) {
        bool clear_cross = this->og_set.contains(element);
        this->og_set.insert(element);
        if (isPrime(element)) {
            this->prime_set.insert(element);
        }
        if (clear_cross) {
            this->updateCross();
        }
    }

    void MagicalContainer::updateCross() {
        this->cross_vector.clear();
        auto ascend_iter = this->og_set.begin();
        auto descend_iter = this->og_set.end();
        while (ascend_iter != descend_iter) {
            this->cross_vector.push_back(*ascend_iter);
            ++ascend_iter;
            this->cross_vector.push_back(*descend_iter);
            --descend_iter;
        }
    }

    long MagicalContainer::size() const {
        return static_cast<long>(this->og_set.size());
    }

    void MagicalContainer::removeElement(int element) {
        bool clear_cross = this->og_set.contains(element);
        this->og_set.erase(element);
        this->prime_set.erase(element);
        if (clear_cross) {
            this->updateCross();
        }
    }

    std::ostream &operator<<(ostream &output, MagicalContainer &_other) {
        output << "{ ";
        for (auto element: _other.og_set) {
            output << element << " ";
        }
        output << "}";
        return output;
    }




    // AscendingIterator


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

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer::AscendingIterator &&_other) noexcept:
            Iterator(_other.getType()),
            _container(_other._container),
            _index(_other._index),
            _curr_iter(_other._curr_iter) {}

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
    MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator &&_other) noexcept {
        if (this != &_other) {
            this->_container = _other._container;
            this->_index = _other._index;
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







    // SideCrossIterator

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

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer::SideCrossIterator &&_other) noexcept:
            Iterator(_other.getType()),
            _container(_other._container),
            _index(_other._index),
            _curr_iter(_other._curr_iter) {}

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
    MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator &&_other) noexcept {
        if (this != &_other) {
            this->_container = _other._container;
            this->_index = _other._index;
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




    // PrimeIterator



    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) :
            Iterator(PRIME_ITER),
            _container(container),
            _index(0) {
        this->_curr_iter = container.prime_set.begin();
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer::PrimeIterator &_other) :
            Iterator(_other.getType()),
            _container(_other._container),
            _index(0),
            _curr_iter(_other._curr_iter) {
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer::PrimeIterator &&_other) noexcept:
            Iterator(_other.getType()),
            _container(_other._container),
            _index(_other._index),
            _curr_iter(_other._curr_iter) {}

    MagicalContainer::PrimeIterator::~PrimeIterator() = default;

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator &_other) {
        if (this != &_other) {
            if (&this->_container != &_other._container) {
                throw std::runtime_error("RUNTIME ERROR: have of the same container!\n");
            }
            this->_index = _other._index;
        }
        return *this;
    }

    MagicalContainer::PrimeIterator &
    MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator &&_other) noexcept {
        if (this != &_other) {
            this->_container = _other._container;
            this->_index = _other._index;
        }
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *_other._curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *_other._curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > _other._index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != _other.getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &_other._container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index < _other._index;
    }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter == *cast_other->_curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return *this->_curr_iter != *cast_other->_curr_iter;
    }

    bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::Iterator &_other) const {
        const auto *cast_other = dynamic_cast<const PrimeIterator *>(&_other);
        if (cast_other == nullptr || this->getType() != cast_other->getType()) {
            throw std::runtime_error("RUNTIME ERROR: Both iterators must be of the same type!\n");
        }
        if (&this->_container != &cast_other->_container) {
            throw std::runtime_error("RUNTIME ERROR: Must have the same container!\n");
        }
        return this->_index > cast_other->_index;
    }

    int MagicalContainer::PrimeIterator::operator*() const {
        return *this->_curr_iter;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (this->_index >= this->_container.size()) {
            throw std::runtime_error("RUNTIME ERROR: Out of range!\n");
        }
        ++this->_index;
        ++this->_curr_iter;
        return *this;
    }

    std::ostream &operator<<(ostream &output, MagicalContainer::PrimeIterator &_other) {
        return output << *_other._curr_iter;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, long index) :
            Iterator(this->getType()),
            _container(container),
            _index(index) {
        this->_curr_iter = container.og_set.begin();
        for (int i = 0; i < index; ++i) {
            ++_curr_iter;
        }
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
        return {this->_container, 0};
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
        return {this->_container, this->_container.size()};
    }

}






