#include <cassert>
#include <iostream>

#include "matrix_bounds.h"

using namespace std;

int main(int argc, char* argv[]) {
    matrix_bounds* mbounds = new matrix_bounds();
    assert(!mbounds->isSubMatrix());
    
    cout << "Test Not Use Sub Matrix" << endl;
    mbounds->setOH(32);
    mbounds->setOW(32);
    assert(mbounds->getH()>0 && mbounds->getW()>0);
    assert(0==mbounds->top());
    assert(31==mbounds->bottom());
    assert(0==mbounds->left());
    assert(31==mbounds->right());
    cout << "Test Not Use Sub Matrix: Done" << endl;
    cout << endl;

    cout << "Test Use Sub Matrix" << endl;
    mbounds->setSubMatrix(0, 0, 32, 32);
    assert(mbounds->isSubMatrix());
    assert(0==mbounds->getH() && 0==mbounds->getW());
    assert(0==mbounds->top());
    assert(31==mbounds->bottom());
    assert(0==mbounds->left());
    assert(31==mbounds->right());

    //assert(0==mbounds->getH)
    cout << "Test Use Sub Matrix: Done" << endl;
    delete mbounds;

    return 0;
}