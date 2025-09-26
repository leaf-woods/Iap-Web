#include <cassert>
#include <ctime>
#include <iostream>

#include "mtest.h"

using namespace std;
mtest* mtest::create(string msg) {
    time_t timestamp;
    time(&timestamp);
    cout << msg << " " << "created at: " << ctime(&timestamp) << endl;
    return new mtest();
}

mtest* mtest::create() {
    time_t timestamp;
    time(&timestamp);
    cout << "created at: " << ctime(&timestamp) << endl;
    return new mtest();
}

void mtest::testPassByAddress(vector<int>& vec) {
    cout << "vec addr: " << &vec << endl;
    cout << "v0 addr: " << &v0 << endl;
    cout << endl;

    v0 = vec;  // A copy of vec was created at address &v0.
    
    cout << "vec size: " << vec.size() << endl;
    cout << "v0 size: " << v0.size() << endl;
    cout << "vec addr: " << &vec << endl;
    cout << "v0 addr: " << &v0 << endl;

    v0.push_back(1);
    cout << "Print v0: ";
    printVector(v0);
    cout << endl;

    cout << "Print vec: ";
    printVector(vec);
    cout << endl;
}

void mtest::testPassByAddressConst(const vector<int>& vec) {
    cout << "pass by address const" << endl;
    v0 = vec;
    cout << "vec addr: " << &vec << endl;
    cout << "v0 addr: " << &v0 << endl;
    v0.push_back(1);
    cout << "vec size: " << vec.size() << endl;
    cout << "v0 size: " << v0.size() << endl;
}

void mtest::printVector(const vector<int>& v) {  
    cout << " Vector: { ";
    for (int i=0; i < (int)v.size(); i++) {
       cout << v.at(i) << " "; 
    }
    cout << " }" << endl;
}


