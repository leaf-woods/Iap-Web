#include <iostream>
#include "iap_print.h" 

using namespace std;

void iap_print::printVector(vector<uchar*>* v) {
    if (!v) {
        cout << "Cannot print vector. Invalid v." << endl;
        return;
    }
            
    cout << " Vector: { ";
    for (int i=0; i<v->size(); i++) {
        cout << "[" << static_cast<unsigned>(v->at(i)[0]) << ", " 
             << static_cast<unsigned>(v->at(i)[1]) << ", " 
             << static_cast<unsigned>(v->at(i)[2]) << "] ";
    }
    cout << " }" << endl;
}

void iap_print::printVector(vector<int>* v) {
    if (!v) {
        cout << "Cannot print vector. Invalid v." << endl;
        return;
    }
            
    cout << " Vector: { ";
    for (int i=0; i<v->size(); i++) {
       cout << v->at(i) << " "; 
    }
    cout << " }" << endl;
}

void iap_print::printPixelColor(uchar* array) {
    cout << "Color [" << static_cast<unsigned>(array[0]) << ", " << static_cast<unsigned>(array[1]) << ", " << static_cast<unsigned>(array[2]) << "]" << endl;
}