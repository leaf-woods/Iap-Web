#include <iostream>

#include "mtest.h"

using namespace std;

int main(int argc, char* argv[]) {

    cout << "Object ct is created in mt->create(). It is deleted in main." << endl;
    mtest* mt = new mtest();
    mtest* ct = mt->create("test 1");
    delete ct;
    delete mt;

    mtest* mt2 = nullptr;
    mt2->create("test 2");

    mtest* mt3;
    mt3->create();

    cout << "mtest done." << endl;

    cout << endl;
    size_t len = sizeof(unsigned char*);
    cout << "size of unsigned char*: " << len << endl;
    cout << "size of unsigned char: " << sizeof(unsigned char) << endl;
    return 0;
}