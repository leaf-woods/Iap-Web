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

    cout << "Test: length of char and char*" << endl;
    cout << endl;
    size_t len = sizeof(unsigned char*);
    cout << "size of unsigned char*: " << len << endl;
    cout << "size of unsigned char: " << sizeof(unsigned char) << endl;
    cout << "Test: length of char and char*: Done" << endl;
    cout << endl;

    // https://stackoverflow.com/questions/1287306/difference-between-string-and-char-types-in-c
    std::string myString = "Hello World";
    cout << "string: " << myString << endl;
    int length = myString.length();
    const char *myStringChars = myString.c_str();
    for (int i=0; i<length; i++) {
        cout << myStringChars[i];
    }
    cout << endl;
    cout << "Out of bound: offset: length " << myStringChars[length] << endl;
    cout << "Out of bound: offset: length+1 " << myStringChars[length+1] << endl;
    cout << endl;

    cout << "Test pass by address" << endl;
    mtest* mp = new mtest();
    vector<int>* v1 = new vector<int>();
    v1->push_back(0);
    mp->testPassByAddress(*v1);
    delete mp;
    delete v1;
    cout << "Test pass by address: Done" << endl;
    cout << endl;
    
    return 0;
}