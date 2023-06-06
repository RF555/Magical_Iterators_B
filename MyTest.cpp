#include "doctest.h"

#define private public

#include "sources/MagicalContainer.hpp"

#undef private

using namespace ariel;
using namespace std;

TEST_CASE("Test isPrime()") {
    int primes[] = {2, 3, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                    47, 53, 59, 61, 67, 71, 173, 281, 541, 1069, 2129, 7919};
    for (auto num: primes) {
        CHECK(isPrime(num));
    }
}

TEST_CASE("Adding and removing elements") {
    MagicalContainer container;
    for (int i = 0; i < 99; ++i) {
        CHECK(container.size() == i);
        container.addElement(i);
        CHECK(container.size() == i + 1);
    }
    for (int i = 0; i < 98; ++i) {
        CHECK(container.size() == 99 - i);
        container.removeElement(i);
        CHECK(container.size() == 98 - i);
    }
}

TEST_CASE("Removing elements that doesn't exist") {
    MagicalContainer container;
    for (int i = 0; i < 99; i += 2) {
        container.addElement(i);
    }

    CHECK(container.size() == 50);

    for (int i = 0; i <= 98; ++i) {
        if (i % 2 == 0) {
            container.removeElement(i);
        } else {
            CHECK_THROWS_AS(container.removeElement(i), std::runtime_error);
        }
    }

    CHECK(container.size() == 0);
}

TEST_CASE("AscendingIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(20);
    container.addElement(2);
    container.addElement(15);
    container.addElement(64);
    container.addElement(30);
    container.addElement(22);
    container.addElement(75);
    CHECK(container.size() == 8);

    MagicalContainer::AscendingIterator it(container);
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 15);
    ++it;
    CHECK(*it == 20);
    ++it;
    CHECK(*it == 22);
    ++it;
    CHECK(*it == 30);
    ++it;
    CHECK(*it == 64);
    ++it;
    CHECK(*it == 75);
}

TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(20);
    container.addElement(2);
    container.addElement(15);
    container.addElement(64);
    container.addElement(30);
    container.addElement(22);
    container.addElement(75);
    CHECK(container.size() == 8);

    MagicalContainer::SideCrossIterator it(container);
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 75);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 64);
    ++it;
    CHECK(*it == 15);
    ++it;
    CHECK(*it == 30);
    ++it;
    CHECK(*it == 20);
    ++it;
    CHECK(*it == 22);
}

TEST_CASE("PrimeIterator") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(15);
    container.addElement(2);
    container.addElement(12);
    container.addElement(3);
    container.addElement(17);
    CHECK(container.size() == 6);

    MagicalContainer::PrimeIterator it(container);
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 17);
}

TEST_CASE("Iterator comparison") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(20);
    container.addElement(2);
    container.addElement(15);
    CHECK(container.size() == 4); // 2 5 15 20

    // AscendingIterator:
    MagicalContainer::AscendingIterator ascend_iter1(container);
    MagicalContainer::AscendingIterator ascend_iter2(container);

    CHECK(ascend_iter1 == ascend_iter2);
    ++ascend_iter1;
    CHECK(ascend_iter1 != ascend_iter2);
    CHECK(ascend_iter1 > ascend_iter2);
    ++ascend_iter2;
    CHECK(ascend_iter1 == ascend_iter2);


    // SideCrossIterator:
    MagicalContainer::SideCrossIterator cross_iter1(container);
    MagicalContainer::SideCrossIterator cross_iter2(container);

    CHECK(cross_iter1 == cross_iter2);
    ++cross_iter1;
    CHECK(cross_iter1 != cross_iter2);
    CHECK(cross_iter1 > cross_iter2);
    ++cross_iter2;
    CHECK(cross_iter1 == cross_iter2);


    // PrimeIterator:
    MagicalContainer::PrimeIterator prime_iter1(container);
    MagicalContainer::PrimeIterator prime_iter2(container);

    CHECK(prime_iter1 == prime_iter2);
    ++prime_iter1;
    CHECK(prime_iter1 != prime_iter2);
    CHECK(prime_iter1 > prime_iter2);
    ++prime_iter2;
    CHECK(prime_iter1 == prime_iter2);
}

TEST_CASE("Iterate past last element") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(20);
    container.addElement(2);
    container.addElement(15);
    CHECK(container.size() == 4); // 2 5 15 20

    MagicalContainer::AscendingIterator ascend_it(container);
    CHECK_NOTHROW(++ascend_it);
    CHECK_NOTHROW(++ascend_it);
    CHECK_NOTHROW(++ascend_it);
    CHECK_NOTHROW(++ascend_it);
    CHECK_THROWS_AS(++ascend_it, std::runtime_error);

    MagicalContainer::SideCrossIterator cross_it(container);
    CHECK_NOTHROW(++cross_it);
    CHECK_NOTHROW(++cross_it);
    CHECK_NOTHROW(++cross_it);
    CHECK_NOTHROW(++cross_it);
    CHECK_THROWS_AS(++cross_it, std::runtime_error);

    MagicalContainer::PrimeIterator prime_it(container);
    CHECK_NOTHROW(++prime_it);
    CHECK_NOTHROW(++prime_it);
    CHECK_THROWS_AS(++prime_it, std::runtime_error);
}

TEST_CASE("Assignment = : only on same container!") {
    MagicalContainer container;
    container.addElement(5);
    container.addElement(20);
    CHECK(container.size() == 2); // 2 5 15 20

    MagicalContainer container2;
    container2.addElement(52);
    container2.addElement(3);
    CHECK(container.size() == 2); // 2 5 15 20

    MagicalContainer::AscendingIterator ascend_it1(container);
    MagicalContainer::AscendingIterator ascend_it2(container2);
    MagicalContainer::SideCrossIterator cross_it1(container);
    MagicalContainer::SideCrossIterator cross_it2(container2);
    MagicalContainer::PrimeIterator prime_it1(container);
    MagicalContainer::PrimeIterator prime_it2(container2);

    CHECK_THROWS_AS(ascend_it1 = ascend_it2, std::runtime_error);
    CHECK_THROWS_AS(cross_it1 = cross_it2, std::runtime_error);
    CHECK_THROWS_AS(prime_it1 = prime_it2, std::runtime_error);
}
