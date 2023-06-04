#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <typeinfo>


using namespace std;

namespace ariel {
    /**
     * @brief Primality test for a number.
     * @param num Number to test.
     * @return True - if num is indeed prime.\n False - else.
     */
    bool isPrime(int num);

    class MagicalContainer {
        /************************************
         ****** MagicalContainer class ******
         ************************************/
    private:
        set<int> og_set;
//        vector<int> ascending_vector;
        vector<int> cross_vector;
//        vector<int> prime_vector;
//        set<int> ascending_set;
//        set<int> cross_set;
        set<int> prime_set;


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

        friend std::ostream &operator<<(ostream &output, MagicalContainer &_other);

    private:
        /**
         * @brief Update the cross_vector.
         */
        void updateCross();



        /************************************
         ********* Iterator classes *********
         ************************************/


    public:

        enum IterType {
            PURE_ITER = -1,
            ASCENDING_ITER = 0,
            CROSS_ITER = 1,
            PRIME_ITER = 2
        };

        /**
         * @class Inner interface representing iterators over the MagicalContainer's elements.
         * @details each implementation of this class would traversal over the elements in a different order.
         */
        class Iterator {
        private:
            /**
             * @brief Represents the implementation type of the Iterator.
             */
            IterType _type;

        protected:
            IterType getType() const { return _type; }

        public:
            Iterator() :
                    _type(PURE_ITER) {}

            explicit Iterator(IterType my_type) :
                    _type(my_type) {}

            /**
             * @brief Copy constructor.
             * @param _other Iterator instance to copy.
             */
            Iterator(const Iterator &_other) = default;

            /**
             * @brief Move constructor.
             * @param _other Iterator instance to move.
             */
            Iterator(Iterator &&_other) = default;

            virtual ~Iterator() = default;

            /**
             * @brief Copy assignment operator.
             * @param _other Iterator instance to copy.
             */
            Iterator &operator=(const Iterator &_other) = default;

            /**
             * @brief Move assignment operator.
             * @param _other Iterator instance to move.
             */
            Iterator &operator=(Iterator &&_other) = default;


            // Boolean operations:

            /**
             * @brief Equality Iterator comparison.
             * @param _other Reference to the compared iterator.
             * @return True - if both iterators are of the same instance (container, index and element value).\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator==(const Iterator &_other) const = 0;

            /**
             * @brief Inequality Iterator comparison.
             * @param _other Reference to the compared iterator.
             * @return False - if both iterators are of the same instance (container, index and element value).\n True - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator!=(const Iterator &_other) const = 0;

            /**
             * @brief GT Iterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is grater then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator>(const Iterator &_other) const = 0;

            /**
             * @brief LT Iterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is lower then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator<(const Iterator &_other) const = 0;

            // Other operators:

            /**
             * @brief Dereference operator.
             * @return The int value of this element.
             */
            virtual int operator*() const = 0;

        };



        // AscendingIterator:


        /**
         * @class Inner class representing iterators over the MagicalContainer's elements.
         * @implements Iterator.
         * @details AscendingIterator going over the elements by ascending order (low value to high value).
         */
        class AscendingIterator : public Iterator {
        private:
            MagicalContainer &_container;
            long _index;

        public:
            AscendingIterator(MagicalContainer &container);

            AscendingIterator(const AscendingIterator &_other);

            AscendingIterator(AscendingIterator &&_other) noexcept;

            ~AscendingIterator() override;

            AscendingIterator &operator=(const AscendingIterator &_other);

            AscendingIterator &operator=(AscendingIterator &&_other) noexcept;


            // Boolean operations:

            /**
             * @brief Equality AscendingIterator comparison.
             * @param _other Reference to the compared iterator.
             * @return True - if both iterators are of the same instance (container, index and element value).\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator==(const AscendingIterator &_other) const;

            /**
             * @brief Inequality AscendingIterator comparison.
             * @param _other Reference to the compared iterator.
             * @return False - if both iterators are of the same instance (container, index and element value).\n True - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator!=(const AscendingIterator &_other) const;

            /**
             * @brief GT AscendingIterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is grater then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator>(const AscendingIterator &_other) const;

            /**
             * @brief LT AscendingIterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is lower then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator<(const AscendingIterator &_other) const;


            // Overriding Iterator operations:

            bool operator==(const Iterator &_other) const override;

            bool operator!=(const Iterator &_other) const override;

            bool operator>(const Iterator &_other) const override;

            bool operator<(const Iterator &_other) const override;

            int operator*() const override;


            // Other operators:

            /**
             * @brief Pre-increment operator (++i).
             */
            AscendingIterator &operator++();

            friend std::ostream &operator<<(ostream &output, AscendingIterator &_other);
        };



    };

}
#endif // MAGICAL_CONTAINER_HPP












