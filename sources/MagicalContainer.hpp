#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP


//#include "../TOOLS/MY_DEBUG_TOOL.hpp"


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>


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

        struct Element_t {
            int _element;
            bool _prime;

            explicit Element_t(int element) :
                    _element(element),
                    _prime(isPrime(element)) {}

            Element_t &operator=(const Element_t &_other) = default;

            bool operator==(const Element_t &_other) const { return this->_element == _other._element; }

            bool operator!=(const Element_t &_other) const { return this->_element != _other._element; }

            bool operator>(const Element_t &_other) const { return this->_element > _other._element; }

            bool operator<(const Element_t &_other) const { return this->_element < _other._element; }

            friend std::ostream &operator<<(ostream &output, Element_t &_other) {
                return output << _other._element;
            }

        };

        set<Element_t> og_set;
        vector<const Element_t *> ascend_vector;
        vector<const Element_t *> cross_vector;
        vector<const Element_t *> prime_vector;

    public:

        MagicalContainer();

        MagicalContainer(const MagicalContainer &_other);

        MagicalContainer(MagicalContainer &&_other) noexcept;

        ~MagicalContainer();

        MagicalContainer &operator=(const MagicalContainer &_other);

        MagicalContainer &operator=(MagicalContainer &&_other) noexcept;

        /**
         * @brief Add an new_element to the container.
         * @param new_element The new_element to add.
         */
        void addElement(int new_element);

        unsigned long size() const;

        /**
         * @brief Remove an _element from the container.
         * @param element The _element to remove.
         * @throws std::runtime_error If the _element does not exist in the container.
         */
        void removeElement(int element);

        friend std::ostream &operator<<(ostream &output, MagicalContainer &_other);

        static void printVector(vector<const Element_t *> &_vec);


        void printOG();

        void printAscend();

        void printCross();

        void printPrime();

        bool contains(Element_t &element);

        bool contains(int element);

    private:
        /**
         * @brief Update ascend_vector AND prime_vector.
         */
        void updateAscendPrime(bool prime);

        /**
         * @brief Update cross_vector.
         */
        void updateCross();


        /************************************
         ********* Iterator classes *********
         ************************************/


    public:

        /**
         * @class Interface representing iterators over the MagicalContainer's elements.
         * @details each implementation of this class would traversal over the elements in a different order.
         */
        class Iterator {
        private:
            MagicalContainer &_container;
            unsigned long _index;
            vector<const Element_t *> &_vec_ref;
            vector<const Element_t *>::iterator _curr_iter;


        protected:
            Iterator(Iterator &_other, unsigned long index);

            vector<const Element_t *> getVecRef() const;

            void setVecRef(vector<const Element_t *> vecRef);

             vector<const Element_t *>::iterator & getCurrIter() ;

            void setCurrIter(vector<const Element_t *>::iterator &currIter);

            MagicalContainer &getContainer() const;

            void setContainer(MagicalContainer &container);

            int getElement() const;

            unsigned long getIndex() const;

            void setIndex(unsigned long index);

        public:

            explicit Iterator(MagicalContainer &my_container, vector<const Element_t *> &vec);

            /**
             * @brief Copy constructor.
             * @param _other Iterator instance to copy.
             */
            Iterator(const Iterator &_other);

            /**
             * @brief Move constructor.
             * @param _other Iterator instance to move.
             */
            Iterator(Iterator &&_other) noexcept;

            virtual ~Iterator();

            /**
             * @brief Copy assignment operator.
             * @param _other Iterator instance to copy.
             */
            Iterator &operator=(const Iterator &_other);

            /**
             * @brief Move assignment operator.
             * @param _other Iterator instance to move.
             */
            Iterator &operator=(Iterator &&_other) noexcept;


            // Boolean operations:

            /**
             * @brief Equality Iterator comparison.
             * @param _other Reference to the compared iterator.
             * @return True - if both iterators are of the same instance (container and index).\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator==(const Iterator &_other) const;

            /**
             * @brief Inequality Iterator comparison.
             * @param _other Reference to the compared iterator.
             * @return False - if both iterators are of the same instance (container and index).\n True - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator!=(const Iterator &_other) const;

            /**
             * @brief GT Iterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is grater then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::invalid_argument If both iterators are not of the same implemented type of iterator.
             * @throws std::invalid_argument If both iterators don't traversal the same container.
             */
            bool operator>(const Iterator &_other) const;

            /**
             * @brief LT Iterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is lower then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator<(const Iterator &_other) const;

            // Other operators:

            /**
             * @brief Dereference operator.
             * @return The int value of this _element.
             */
            int operator*() const;

            /**
             * @brief Pre-increment operator (++i).
             * @throws std::runtime_error If this is the last _element.
             */
            Iterator &operator++();

            friend std::ostream &operator<<(ostream &output, Iterator &_other);

            // Iterator functions:

//            /**
//            * @return Reference to the iterator pointing to the first _element of the magical_container.
//            */
//            virtual Iterator begin();
//
//            /**
//            * @return Reference to the iterator pointing to the last _element of the magical_container.
//            */
//            virtual Iterator end();

        };



        // AscendingIterator:


        /**
         * @class Inner class representing iterators over the MagicalContainer's elements.
         * @implements Iterator.
         * @details AscendingIterator going over the elements by ascending order (low value to high value).
         */
        class AscendingIterator : public Iterator {

        private:

            AscendingIterator(AscendingIterator &_other, unsigned long index);

        public:
            explicit AscendingIterator(MagicalContainer &container);

            AscendingIterator(const AscendingIterator &_other);

            AscendingIterator(AscendingIterator &&_other) noexcept;

            ~AscendingIterator() override;

            AscendingIterator &operator=(const AscendingIterator &_other);

            AscendingIterator &operator=(AscendingIterator &&_other) noexcept;


            // Override functions:

            /**
            * @return Reference to the iterator pointing to the first _element of the magical_container.
            */
            AscendingIterator begin();

            /**
            * @return Reference to the iterator pointing to the last _element of the magical_container.
            */
            AscendingIterator end();
        };


        // SideCrossIterator:

        /**
         * @details Iterating over the elements in cross order.
         * @details i.e. crossing from low value to high value elements:\n
         * 1. Lowest value _element\n
         * 2. Highest value _element\n
         * 3. Second lowest value _element\n
         * 4. Second highest value _element\n
         * 5. Third lowest value _element\n
         * .\n
         * .\n
         * .
         */
        class SideCrossIterator : public Iterator {

        private:

            SideCrossIterator(SideCrossIterator &_other, unsigned long index);

        public:

            explicit SideCrossIterator(MagicalContainer &container);

            SideCrossIterator(const SideCrossIterator &_other);

            SideCrossIterator(SideCrossIterator &&_other) noexcept;

            ~SideCrossIterator() override;

            SideCrossIterator &operator=(const SideCrossIterator &_other);

            SideCrossIterator &operator=(SideCrossIterator &&_other) noexcept;


            // Override functions:

            /**
            * @return Reference to the iterator pointing to the first _element of the magical_container.
            */
            virtual SideCrossIterator begin();

            /**
            * @return Reference to the iterator pointing to the last _element of the magical_container.
            */
            virtual SideCrossIterator end();
        };



        // PrimeIterator


        /**
         * @details Iterating over only the elements with prime value, by ascending order (low value to high value).
         */
        class PrimeIterator : public Iterator {

        private:

            PrimeIterator(PrimeIterator &_other, unsigned long index);

        public:

            explicit PrimeIterator(MagicalContainer &container);

            PrimeIterator(const PrimeIterator &_other);

            PrimeIterator(PrimeIterator &&_other) noexcept;

            ~PrimeIterator() override;

            PrimeIterator &operator=(const PrimeIterator &_other);

            PrimeIterator &operator=(PrimeIterator &&_other) noexcept;


            // Override functions:

            /**
            * @return Reference to the iterator pointing to the first _element of the magical_container.
            */
            PrimeIterator begin();

            /**
            * @return Reference to the iterator pointing to the last _element of the magical_container.
            */
            PrimeIterator end();
        };

    };

}
#endif // MAGICAL_CONTAINER_HPP












