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
    bool isPrime(int num);

    class MagicalContainer {
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
    };

}
#endif // MAGICAL_CONTAINER_HPP
