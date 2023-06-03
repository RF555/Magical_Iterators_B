#ifndef MAGICAL_CONTAINER_OLD_HPP
#define MAGICAL_CONTAINER_OLD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <typeinfo>


using namespace std;

    class MagicalContainer {


    public:
        class MagicalNode {

        private:

            int _value;
            bool _prime;
            long _index;
            long next_prime;

        public:

            // Getters

            int getValue() const;

            bool isPrime() const;

            long getIndex() const;

            long getNextPrime() const;


            // Setters

            void setIndex(long location);

            void setNextPrime(long nextPrime);

            // Constructors/Destructors

            explicit MagicalNode(int val);

            MagicalNode(MagicalNode const &_other);

            MagicalNode(MagicalNode &&_other) noexcept;

            ~MagicalNode();

            // Copy/move assignments

            MagicalNode &operator=(const MagicalNode &_other);

            MagicalNode &operator=(MagicalNode &&_other) noexcept;

            // Boolean operators

            friend bool operator>(const MagicalNode &_node1, const MagicalNode &_node2);

            friend bool operator==(const MagicalNode &_node1, const MagicalNode &_node2);

            friend bool operator!=(const MagicalNode &_node1, const MagicalNode &_node2);

//            friend std::ostream &operator<<(ostream &output, MagicalNode &_other);

        };

        static bool is_prime(int num);


        /*****************************************************
         ***************** MagicalContainer ******************
         *****************************************************/

    private:

        long _size;
        vector<MagicalNode *> container;
        long first_prime;

        void updatePrimes();


    public:

        MagicalContainer();

        MagicalContainer(const MagicalContainer &_other);

        MagicalContainer(MagicalContainer &&_other) noexcept;

        ~MagicalContainer();

        MagicalContainer &operator=(const MagicalContainer &_other);

        MagicalContainer &operator=(MagicalContainer &&_other) noexcept;

        void addElement(int element);

        long size() const;

        void removeElement(int element);

        MagicalNode *at(long index);

        friend std::ostream &operator<<(ostream &output, MagicalContainer &_other);


        /*****************************************************
         ******************* Inner classes *******************
         *****************************************************/


        /**
         * @class Inner class representing iterators over the MagicalContainer's elements.
         * @details each implementation of this class would traversal over the elements in a different order.
         * @details AscendingIterator going over the elements by ascending order (low value to high value).
         */
        class AscendingIterator {
        private:
            MagicalContainer &magical_container;
            MagicalNode *curr_element;

        protected:

            void setMagicalContainer(MagicalContainer &magicalContainer);

            void setCurrElement(MagicalNode *currElement);

            MagicalContainer &getMagicalContainer() const;

            MagicalNode *getCurrElement() const;

            long getIndex() const;

        public:

            explicit AscendingIterator(MagicalContainer &_container);

            explicit AscendingIterator(MagicalContainer &_container, long index);

            AscendingIterator(const AscendingIterator &_other);

            AscendingIterator(AscendingIterator &&_other) noexcept;

            ~AscendingIterator();

            AscendingIterator &operator=(const AscendingIterator &_other);

            AscendingIterator &operator=(AscendingIterator &&_other) noexcept;

            /**
             * @return Reference to the iterator pointing to the first element of the magical_container.
             */
            AscendingIterator begin();

            /**
             * @return Reference to the iterator pointing to the last element of the magical_container.
             */
            AscendingIterator end();

            /**
             * @brief Dereference operator.
             * @return the int value of this element.
             */
            int operator*() const;

            /**
             * @brief Pre-increment operator (++i).
             */
            AscendingIterator &operator++();

            /**
             * @brief Equality comparison.
             * @param _iter1 Reference to this iterator.
             * @param _iter2 Reference to the compared iterator.
             * @return True - if both _iter1 and _iter2 point to the same object.
             * @throws std::invalid_argument If _iter1 and _iter2 are not of the same implementation type of iterator.
             */
            friend bool operator==(const AscendingIterator &_iter1, const AscendingIterator &_iter2);

            /**
             * @brief Equality comparison.
             * @param _iter1 Reference to this iterator.
             * @param _iter2 Reference to the compared iterator.
             * @return False - if both _iter1 and _iter2 point to the same object.
             * @throws std::invalid_argument If _iter1 and _iter2 are not of the same implementation type of iterator.
             */
            friend bool operator!=(const AscendingIterator &_iter1, const AscendingIterator &_iter2);

            /**
             * @brief GT comparison operator.
             * @param _iter1 Reference to this iterator.
             * @param _iter2 Reference to the compared iterator.
             * @return True - if the location of _iter1 is grater then the location of _iter2.\n False - else.
             * @details Both objects must be of the same type.
             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type iterator.
             */
            friend bool operator>(const AscendingIterator &_iter1, const AscendingIterator &_iter2);

            /**
             * @brief LT comparison operator.
             * @param _iter1 Reference to this iterator.
             * @param _iter2 Reference to the compared iterator.
             * @return True - if the location of _iter1 is lower then the location of _iter2.\n False - else.
             * @details Both objects must be of the same type.
             * @throws std::invalid_argument If _iter1 and _iter2 are not of the same implementation type of iterator.
             */
            friend bool operator<(const AscendingIterator &_iter1, const AscendingIterator &_iter2);


//            bool operator!() const;
//
//            friend bool operator>=(const AscendingIterator &_iter1, const AscendingIterator &_iter2);
//
//            friend bool operator<=(const AscendingIterator &_iter1, const AscendingIterator &_iter2);


            friend std::ostream &operator<<(ostream &output, AscendingIterator &_other);

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
        class SideCrossIterator {
        private:
            MagicalContainer &magical_container;
            MagicalNode *curr_ascending;
            MagicalNode *curr_descending;


        protected:
            MagicalContainer &getMagicalContainer() const;

            void setMagicalContainer(MagicalContainer &magicalContainer);

            MagicalNode *getCurrAscending() const;

            void setCurrAscending(MagicalNode *currAscending);

            MagicalNode *getCurrDescending() const;

            void setCurrDescending(MagicalNode *currDescending);

            long getAscendingIndex();

            long getDescendingIndex();

        public:

            explicit SideCrossIterator(MagicalContainer &_container);

            explicit SideCrossIterator(MagicalContainer &_container, long index);

            SideCrossIterator(const SideCrossIterator &_other);

            SideCrossIterator(SideCrossIterator &&_other) noexcept;

            ~SideCrossIterator();


            SideCrossIterator &operator=(const SideCrossIterator &_other);

            SideCrossIterator &operator=(SideCrossIterator &&_other) noexcept;

            SideCrossIterator begin();

            SideCrossIterator end();

            SideCrossIterator &operator++();

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
//             * @return True - if the location of _iter1 is grater then the location of _iter2.\n False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type SideCrossIterator.
//             */
//            friend bool operator>(const SideCrossIterator &_iter1, const SideCrossIterator &_iter2);
//
//            /**
//             * @brief LT comparison operator.
//             * @param _iter1 Reference to this SideCrossIterator.
//             * @param _iter2 Reference to the compared SideCrossIterator.
//             * @return True - if the location of _iter1 is lower than the location of _iter2.\n False - else.
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
        class PrimeIterator  {
        private:

        public:

            explicit PrimeIterator(const MagicalContainer &_container);

            PrimeIterator &operator=(const PrimeIterator &_other);

            PrimeIterator &operator=(PrimeIterator &&_other) noexcept;

            AscendingIterator begin() ;

            AscendingIterator end() ;

            AscendingIterator &operator++() ;

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
//             * @return True - if the location of _iter1 is grater then the location of _iter2.\n False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type PrimeIterator.
//             */
//            friend bool operator>(const PrimeIterator &_iter1, const PrimeIterator &_iter2);
//
//            /**
//             * @brief LT comparison operator.
//             * @param _iter1 Reference to this PrimeIterator.
//             * @param _iter2 Reference to the compared PrimeIterator.
//             * @return True - if the location of _iter1 is lower than the location of _iter2.\n False - else.
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


        /**
         * @details Iterating over the elements by ascending order (low value to high value).
         */
        class _F_AscendingIterator : public AscendingIterator {
        private:

        public:

            explicit _F_AscendingIterator(const MagicalContainer &_container);

            _F_AscendingIterator &operator=(const _F_AscendingIterator &_other);

            _F_AscendingIterator &operator=(_F_AscendingIterator &&_other) noexcept;

            AscendingIterator begin() override;

            AscendingIterator end() override;

            AscendingIterator &operator++() override;

//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this _F_AscendingIterator.
//             * @param _iter2 Reference to the compared _F_AscendingIterator.
//             * @return True - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type _F_AscendingIterator.
//             */
//            friend bool operator==(const _F_AscendingIterator &_iter1, const _F_AscendingIterator &_iter2);
//
//            /**
//             * @brief Equality comparison.
//             * @param _iter1 Reference to this _F_AscendingIterator.
//             * @param _iter2 Reference to the compared _F_AscendingIterator.
//             * @return False - if both _iter1 and _iter2 point to the same object.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type _F_AscendingIterator.
//             */
//            friend bool operator!=(const _F_AscendingIterator &_iter1, const _F_AscendingIterator &_iter2);
//
//            /**
//             * @brief GT comparison operator.
//             * @param _iter1 Reference to this _F_AscendingIterator.
//             * @param _iter2 Reference to the compared _F_AscendingIterator.
//             * @return True - if the location of _iter1 is grater then the location of _iter2.\n False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type _F_AscendingIterator.
//             */
//            friend bool operator>(const _F_AscendingIterator &_iter1, const _F_AscendingIterator &_iter2);
//
//            /**
//             * @brief LT comparison operator.
//             * @param _iter1 Reference to this _F_AscendingIterator.
//             * @param _iter2 Reference to the compared _F_AscendingIterator.
//             * @return True - if the location of _iter1 is lower than the location of _iter2.\n False - else.
//             * @details Both objects must be of the same type.
//             * @throws std::invalid_argument If either _iter1 OR _iter2 are not of type _F_AscendingIterator.
//             */
//            friend bool operator<(const _F_AscendingIterator &_iter1, const _F_AscendingIterator &_iter2);
//
//            bool operator!() const;
//
//            friend bool operator>=(const _F_AscendingIterator &_iter1, const _F_AscendingIterator &_iter2);
//
//            friend bool operator<=(const _F_AscendingIterator &_iter1, const _F_AscendingIterator &_iter2);

        };

    };


#endif // MAGICAL_CONTAINER_OLD_HPP
