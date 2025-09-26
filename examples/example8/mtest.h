#ifndef MTEST_H
#define MTEST_H

#include <vector>

class mtest {
    private:
        std::vector<int> v0;

    public:
        mtest* create();
        mtest* create(std::string msg);
        void testPassByAddress(std::vector<int>& vec);
        void printVector(const std::vector<int>& v);
};

#endif