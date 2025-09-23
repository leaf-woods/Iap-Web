#include <chrono>
#include <iostream>

#include "imagecolorvalues_t.h"

using namespace std;

/*
 * @20250920
 * We copied imagecolorvalues.h to this directory and tested the difference between 
 * const char* and string literals. Practically there is no difference.
 */
int main() {
    cout << "const char* " << endl;
    auto t1 = chrono::high_resolution_clock::now();
    for (int i=0; i<10000; i++) {
        imagecolorvalues_t::getColorVal(imagecolorvalues_t::PURPLE);
    }
    auto t2 = chrono::high_resolution_clock::now();
    cout << "Process time: " << (int)chrono::duration_cast<chrono::microseconds>(t2-t1).count() << endl;

    cout << "string literal" << endl;
    auto t3 = chrono::high_resolution_clock::now();
    for (int i=0; i<10000; i++) {
        imagecolorvalues_t::getColorVal(imagecolorvalues_t::BLACK);
    }
    auto t4 = chrono::high_resolution_clock::now();
    cout << "Process time: " << (int)chrono::duration_cast<chrono::microseconds>(t4-t3).count() << endl;

    cout << "string literal" << endl;
    auto t5 = chrono::high_resolution_clock::now();
    imagecolorvalues_t* cvalues = new imagecolorvalues_t();
    for (int i=0; i<10000; i++) {
        cvalues->toString(imagecolorvalues_t::BLACK);
    }
    auto t6 = chrono::high_resolution_clock::now();
    cout << "Process time: " << (int)chrono::duration_cast<chrono::microseconds>(t6-t5).count() << endl;
    delete cvalues;

    cout << "const char*" << endl;
    auto t7 = chrono::high_resolution_clock::now();
    cvalues = new imagecolorvalues_t();
    for (int i=0; i<10000; i++) {
        cvalues->toString(imagecolorvalues_t::GREEN);
    }
    auto t8 = chrono::high_resolution_clock::now();
    cout << "Process time: " << (int)chrono::duration_cast<chrono::microseconds>(t8-t7).count() << endl;
    delete cvalues;

    return 0;
}