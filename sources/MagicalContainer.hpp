#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

#include <iostream>
#include <string>
//#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include <typeinfo>


using namespace std;

namespace ariel {
    bool isPrime(int num);

    class MagicalContainer {
        /************************************
         ****** MagicalContainer class ******
         ************************************/
    private:
//        vector<int> ascending_vector;
//        vector<int> cross_vector;
//        vector<int> prime_vector;
        set<int> og_set;
        set<int> ascending_set;
        set<int> cross_set;
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
            static IterType _type;

        public:
            Iterator() :
                    _type(PURE_ITER) {}

            Iterator(IterType my_type) :
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
            virtual bool operator!=(const Iterator &_other) = 0;

            /**
             * @brief GT Iterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is grater then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator>(const Iterator &_other) = 0;

            /**
             * @brief LT Iterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is lower then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            virtual bool operator<(const Iterator &_other) = 0;
        };



        /************************************
         ********* Iterator classes *********
         ************************************/



        /**
         * @class Inner class representing iterators over the MagicalContainer's elements.
         * @implements Iterator.
         * @details AscendingIterator going over the elements by ascending order (low value to high value).
         */
        class AscendingIterator : public Iterator {
        private:

        };


    };

}
#endif // MAGICAL_CONTAINER_HPP












