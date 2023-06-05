#ifndef MAGICAL_CONTAINER_HPP
#define MAGICAL_CONTAINER_HPP

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
        set<int> og_set;
        vector<int> ascend_vector;
        vector<int> cross_vector;
        vector<int> prime_vector;


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
         * @brief Update ascend_vector.
         */
        void updateAscend();

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
            long _index;
            vector<int> *_vec_ptr;
            vector<int>::iterator _curr_iter;


        protected:
            vector<int> *getVecPtr() const;

            void setVecPtr(vector<int> *vecPtr);

            const vector<int>::iterator &getCurrIter() const;

            void setCurrIter(const vector<int>::iterator &currIter);

            MagicalContainer &getContainer() const;

            void setContainer(MagicalContainer &container);

            int getElement() const;

            long getIndex() const;

            void setIndex(long index);

        public:

            explicit Iterator(MagicalContainer &my_container, vector<int> *vec);

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
             * @return The int value of this element.
             */
            int operator*() const;

            /**
             * @brief Pre-increment operator (++i).
             * @throws std::runtime_error If this is the last element.
             */
            virtual Iterator &operator++();

            friend std::ostream &operator<<(ostream &output, Iterator &_other);


        };



        // AscendingIterator:


        /**
         * @class Inner class representing iterators over the MagicalContainer's elements.
         * @implements Iterator.
         * @details AscendingIterator going over the elements by ascending order (low value to high value).
         */
        class AscendingIterator : public Iterator {
        private:

            AscendingIterator(MagicalContainer &container, long index);

        public:
            explicit AscendingIterator(MagicalContainer &container);

            AscendingIterator(const AscendingIterator &_other);

            AscendingIterator(AscendingIterator &&_other) noexcept;

            ~AscendingIterator() override;

            AscendingIterator &operator=(const AscendingIterator &_other);

            AscendingIterator &operator=(AscendingIterator &&_other) noexcept;

            // Override operator:

            /**
             * @brief Pre-increment operator (++i).
             * @throws std::runtime_error If this is the last element.
             */
            Iterator &operator++() override;


            // Iterator functions:

            /**
             * @return Reference to the iterator pointing to the first element of the magical_container.
             */
            AscendingIterator begin();

            /**
             * @return Reference to the iterator pointing to the last element of the magical_container.
             */
            AscendingIterator end();
        };


        // SideCrossIterator:

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
            vector<int>::iterator _curr_iter;

            SideCrossIterator(MagicalContainer &container, long index);

        public:

            explicit SideCrossIterator(MagicalContainer &container);

            SideCrossIterator(const SideCrossIterator &_other);

            SideCrossIterator(SideCrossIterator &&_other) noexcept;

            ~SideCrossIterator() override;

            SideCrossIterator &operator=(const SideCrossIterator &_other);

            SideCrossIterator &operator=(SideCrossIterator &&_other) noexcept;


            // Override operators:

            /**
             * @brief Pre-increment operator (++i).
             * @throws std::runtime_error If this is the last element.
             */
            Iterator &operator++() override;


            // Iterator functions:

            /**
             * @return Reference to the iterator pointing to the first element of the magical_container.
             */
            SideCrossIterator begin();

            /**
             * @return Reference to the iterator pointing to the last element of the magical_container.
             */
            SideCrossIterator end();
        };



        // PrimeIterator


        /**
         * @details Iterating over only the elements with prime value, by ascending order (low value to high value).
         */
        class PrimeIterator : public Iterator {

        private:
            set<int>::iterator _curr_iter;

            PrimeIterator(MagicalContainer &container, long index);

        public:

            explicit PrimeIterator(MagicalContainer &container);

            PrimeIterator(const PrimeIterator &_other);

            PrimeIterator(PrimeIterator &&_other) noexcept;

            ~PrimeIterator() override;

            PrimeIterator &operator=(const PrimeIterator &_other);

            PrimeIterator &operator=(PrimeIterator &&_other) noexcept;


            // Boolean operations:

            /**
             * @brief Equality PrimeIterator comparison.
             * @param _other Reference to the compared iterator.
             * @return True - if both iterators are of the same instance (container, index and element value).\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator==(const PrimeIterator &_other) const;

            /**
             * @brief Inequality PrimeIterator comparison.
             * @param _other Reference to the compared iterator.
             * @return False - if both iterators are of the same instance (container, index and element value).\n True - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator!=(const PrimeIterator &_other) const;

            /**
             * @brief GT PrimeIterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is grater then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator>(const PrimeIterator &_other) const;

            /**
             * @brief LT PrimeIterator comparison operator.
             * @param _other Reference to the compared iterator.
             * @return True - if the index of THIS iterator is lower then the index of _other.\n False - else.
             * @details Both iterators must be of the same type and traversal over the same container.
             * @throws std::runtime_error If both iterators are not of the same implemented type of iterator.
             * @throws std::runtime_error If both iterators don't traversal the same container.
             */
            bool operator<(const PrimeIterator &_other) const;


            // Overriding Iterator operations:

            bool operator==(const Iterator &_other) const override;

            bool operator!=(const Iterator &_other) const override;

            bool operator>(const Iterator &_other) const override;

            bool operator<(const Iterator &_other) const override;

            int operator*() const override;


            // Other operators:

            /**
             * @brief Pre-increment operator (++i).
             * @throws std::runtime_error If this is the last element.
             */
            PrimeIterator &operator++();

            friend std::ostream &operator<<(ostream &output, PrimeIterator &_other);


            // Iterator functions:

            /**
             * @return Reference to the iterator pointing to the first element of the magical_container.
             */
            PrimeIterator begin();

            /**
             * @return Reference to the iterator pointing to the last element of the magical_container.
             */
            PrimeIterator end();
        };

    };

}
#endif // MAGICAL_CONTAINER_HPP












