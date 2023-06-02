#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

namespace ariel {
    class MagicalContainer {


    public:
        class MagicalNode {
            int _value;
            bool _prime;
            long _location;
            long next_prime;
        public:
            int getValue() const;

            bool isPrime() const;

            long getLocation() const;

            long getNextPrime() const;

            void setLocation(long location);

            void setNextPrime(long nextPrime);

        public:
            explicit MagicalNode(int val);

            friend bool operator>(const MagicalNode &_node1, const MagicalNode &_node2);

            friend bool operator==(const MagicalNode &_node1, const MagicalNode &_node2);

            friend bool operator!=(const MagicalNode &_node1, const MagicalNode &_node2);

//            friend std::ostream &operator<<(ostream &output, MagicalNode &_other);

        };

        static bool is_prime(int num);


    private:
        long _size;
        vector<MagicalNode *> container;
        long first_prime;

        void updatePrimes();


    public:
        MagicalContainer();

        MagicalContainer(const MagicalContainer &_other);

        ~MagicalContainer();

        MagicalContainer &operator=(const MagicalContainer &_other);

        void addElement(int element);

        long size() const;

        void removeElement(int element);

        friend std::ostream &operator<<(ostream &output, MagicalContainer &_other);


    private:

        /**
         * @class Abstract class representing iterators over the MagicalContainer's elements.
         * @details Iterator going over the elements by ascending order (low value to high value).
         * @details each implementation of this class would traversal over the elements in a different order.
         */
        class Iterator {
        private:

        public:
            Iterator();

            Iterator(MagicalContainer _container);

            Iterator(Iterator const &_other);

            ~Iterator();

            Iterator &operator=(const Iterator &_other);

            /**
             * @return Reference to the iterator pointing to the first element of the container.
             */
            virtual Iterator &begin();

            /**
             * @return Reference to the iterator pointing to the last element of the container.
             */
            virtual Iterator &end();

            /**
             * @brief Dereference operator.
             */
            Iterator &operator*() const;

            /**
             * @brief Pre-increment operator (++i).
             */
            virtual Iterator &operator++();

            /**
             * @brief Equality comparison.
             * @param _iter1 Reference to this Iterator.
             * @param _iter2 Reference to the compared Iterator.
             * @return True - if both _iter1 and _iter2 point to the same object.
             * @throws std::invalid_argument If _iter1 and _iter2 are not of the same implementation type of Iterator.
             */
            friend bool operator==(const Iterator &_iter1, const Iterator &_iter2);

            /**
             * @brief Equality comparison.
             * @param _iter1 Reference to this AscendingIterator.
             * @param _iter2 Reference to the compared AscendingIterator.
             * @return False - if both _iter1 and _iter2 point to the same object.
             * @throws std::invalid_argument If _iter1 and _iter2 are not of the same implementation type of Iterator.
             */
            friend bool operator!=(const Iterator &_iter1, const Iterator &_iter2);

            /**
             * @brief GT comparison operator.
             * @param _iter1 Reference to this AscendingIterator.
             * @param _iter2 Reference to the compared AscendingIterator.
             * @return True - if the location of _iter1 is grater then the location of _iter2. False - else.
             * @details Both objects must be of the same type.
             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type AscendingIterator.
             */
            friend bool operator>(const Iterator &_iter1, const Iterator &_iter2);

            /**
             * @brief LT comparison operator.
             * @param _iter1 Reference to this AscendingIterator.
             * @param _iter2 Reference to the compared AscendingIterator.
             * @return True - if the location of _iter1 is lower then the location of _iter2. False - else.
             * @details Both objects must be of the same type.
             * @throws std::invalid_argument If _iter1 and _iter2 are not of the same implementation type of Iterator.
             */
            friend bool operator<(const Iterator &_iter1, const Iterator &_iter2);


//            bool operator!() const;
//
//            friend bool operator>=(const Iterator &_iter1, const Iterator &_iter2);
//
//            friend bool operator<=(const Iterator &_iter1, const Iterator &_iter2);


            friend std::ostream &operator<<(ostream &output, Iterator &_other);

        };

    public:

        /**
         * @details Iterating over the elements by ascending order (low value to high value).
         */
        class AscendingIterator : public Iterator {
        private:

        public:
            AscendingIterator();

            AscendingIterator(MagicalContainer _container);

            AscendingIterator(AscendingIterator const &_other);

            ~AscendingIterator();

            AscendingIterator &operator=(const AscendingIterator &_other);

            Iterator &begin() override;

            Iterator &end() override;

            Iterator &operator++() override;

//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this AscendingIterator.
//             * @param _iter2 Reference to the compared AscendingIterator.
//             * @return True - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type AscendingIterator.
//             */
//            friend bool operator==(const AscendingIterator &_iter1, const AscendingIterator &_iter2);
//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this AscendingIterator.
//             * @param _iter2 Reference to the compared AscendingIterator.
//             * @return False - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type AscendingIterator.
//             */
//            friend bool operator!=(const AscendingIterator &_iter1, const AscendingIterator &_iter2);
//
//            /**
//             * @brief GT comparison operator.
//             * @param _iter1 Reference to this AscendingIterator.
//             * @param _iter2 Reference to the compared AscendingIterator.
//             * @return True - if the location of _iter1 is grater then the location of _iter2. False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type AscendingIterator.
//             */
//            friend bool operator>(const AscendingIterator &_iter1, const AscendingIterator &_iter2);
//
//            /**
//             * @brief LT comparison operator.
//             * @param _iter1 Reference to this AscendingIterator.
//             * @param _iter2 Reference to the compared AscendingIterator.
//             * @return True - if the location of _iter1 is lower than the location of _iter2. False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type AscendingIterator.
//             */
//            friend bool operator<(const AscendingIterator &_iter1, const AscendingIterator &_iter2);
//
//            bool operator!() const;
//
//            friend bool operator>=(const AscendingIterator &_iter1, const AscendingIterator &_iter2);
//
//            friend bool operator<=(const AscendingIterator &_iter1, const AscendingIterator &_iter2);

        };

        /**
         * @details Iterating over the elements in cross order.
         * @details i.e. crossing from low value to high value elements:\n
         * 1. Lowest value element\n
         * 2. Highest value element\n
         * 3. Second lowest value element\n
         * 4. Second highest value element\n
         * 5. Third lowest value element\n
         * .\n
         * .\n
         * .
         */
        class SideCrossIterator : public Iterator {
        private:
            vector<MagicalContainer> &container;

        public:
            SideCrossIterator();

            SideCrossIterator(MagicalContainer &_container);

            SideCrossIterator(SideCrossIterator const &_other);

            ~SideCrossIterator();

            SideCrossIterator &operator=(const SideCrossIterator &_other);

            Iterator &begin() override;

            Iterator &end() override;

            Iterator &operator++() override;

//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this SideCrossIterator.
//             * @param _iter2 Reference to the compared SideCrossIterator.
//             * @return True - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type SideCrossIterator.
//             */
//            friend bool operator==(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);
//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this SideCrossIterator.
//             * @param _iter2 Reference to the compared SideCrossIterator.
//             * @return False - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type SideCrossIterator.
//             */
//            friend bool operator!=(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);
//
//            /**
//             * @brief GT comparison operator.
//             * @param _iter1 Reference to this SideCrossIterator.
//             * @param _iter2 Reference to the compared SideCrossIterator.
//             * @return True - if the location of _iter1 is grater then the location of _iter2. False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type SideCrossIterator.
//             */
//            friend bool operator>(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);
//
//            /**
//             * @brief LT comparison operator.
//             * @param _iter1 Reference to this SideCrossIterator.
//             * @param _iter2 Reference to the compared SideCrossIterator.
//             * @return True - if the location of _iter1 is lower than the location of _iter2. False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type SideCrossIterator.
//             */
//            friend bool operator<(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);
//
//            bool operator!() const;
//
//            friend bool operator>=(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);
//
//            friend bool operator<=(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);

        };

        /**
         * @details Iterating over only the elements with prime value, by ascending order (low value to high value).
         */
        class PrimeIterator : public Iterator {
        private:

        public:
            PrimeIterator();

            PrimeIterator(MagicalContainer _container);

            PrimeIterator(PrimeIterator const &_other);

            ~PrimeIterator();

            PrimeIterator &operator=(const PrimeIterator &_other);

            Iterator &begin() override;

            Iterator &end() override;

            Iterator &operator++() override;

//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this PrimeIterator.
//             * @param _iter2 Reference to the compared PrimeIterator.
//             * @return True - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type PrimeIterator.
//             */
//            friend bool operator==(const PrimeIterator &_iter1, const PrimeIterator &_iter2);
//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this PrimeIterator.
//             * @param _iter2 Reference to the compared PrimeIterator.
//             * @return False - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type PrimeIterator.
//             */
//            friend bool operator!=(const PrimeIterator &_iter1, const PrimeIterator &_iter2);
//
//            /**
//             * @brief GT comparison operator.
//             * @param _iter1 Reference to this PrimeIterator.
//             * @param _iter2 Reference to the compared PrimeIterator.
//             * @return True - if the location of _iter1 is grater then the location of _iter2. False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type PrimeIterator.
//             */
//            friend bool operator>(const PrimeIterator &_iter1, const PrimeIterator &_iter2);
//
//            /**
//             * @brief LT comparison operator.
//             * @param _iter1 Reference to this PrimeIterator.
//             * @param _iter2 Reference to the compared PrimeIterator.
//             * @return True - if the location of _iter1 is lower than the location of _iter2. False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type PrimeIterator.
//             */
//            friend bool operator<(const PrimeIterator &_iter1, const PrimeIterator &_iter2);
//
//            bool operator!() const;
//
//            friend bool operator>=(const PrimeIterator &_iter1, const PrimeIterator &_iter2);
//
//            friend bool operator<=(const PrimeIterator &_iter1, const PrimeIterator &_iter2);

        };

    };

}
#endif // MAGICAL_CONTAINER_HPP
