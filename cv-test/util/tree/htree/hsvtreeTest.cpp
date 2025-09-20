#include <cassert>
#include <iostream>
#include <opencv2/core.hpp>
#include "hsvtree.h"

using namespace std;

/*
 * The tests lead to change findValues() to return copy of vector.
 */
int main(int argc, char* argv[]) {

    uchar data[5][3] = { {255, 255, 255}, 
                     {255, 0, 0},
                     {128, 128, 128},
                     {0, 0, 0},
                     {220, 255, 255}
                    };

    int max = 0;
    iap_print* p = new iap_print();

    cout << "Test-1 hsvtree" << endl;
    /*
     * @20250919
     * This is valid in C++. We do not use this coding style in iapcv.
     */
    hsvtree t;
    t.setPrint(p);
    t.printTree();
    assert(0==t.size());
    assert(hsvtree::HUE==t.getHSVDim());
    try {
        cout << "max: " << t.getMaxValue() << endl;
    }
    catch( const std::invalid_argument& e ) {
        cout << "Exception: " << e.what() << endl;
    }

    try {
        cout << "find values." << endl;  
        t.findValues(0);
    }
    catch( const std::logic_error& e ) {
        cout << "Exception: " << e.what() << endl;
    }
    
    vector<int>* vec_h = nullptr;
    try {
        t.getTreeData(vec_h);
    }
    catch( const std::invalid_argument& e ) {
        cout << "Exception: " << e.what() << endl;
    }

    vec_h = new vector<int>();
    try {
        t.getTreeData(vec_h);
    }
    catch( const std::logic_error& e ) {
        cout << "Exception: " << e.what() << endl;
    }

    vec_h->push_back(0);
    try {
        t.getTreeData(vec_h);
    }
    catch( const std::invalid_argument& e ) {
        cout << "Exception: " << e.what() << endl;
    }

    t.deleteTree();
    cout << endl;

    uchar hsv_data[] = {255, 255, 255};
    t.add(hsv_data);
    assert(1==t.size());
    assert(hsvtree::HUE==t.getHSVDim());
    assert(255==t.getMaxValue());
    t.printTree();
    
    auto vec_uch = t.findValues(255);
    assert(1==vec_uch.size()); 
    vec_uch = vector<uchar*>(); 
    vec_h->clear();
    t.getTreeData(vec_h);
    assert(1==vec_h->size());

    t.deleteTree();
    assert(0==t.size());
    cout << "Test-1 hsvtree: Done." << endl;
    cout << endl;

    cout << "Test-2 hsvtree: add duplicate hsv color. " << endl;
    t.add(data[1]); 
    assert(1==t.size());
    assert(255==t.getMaxValue());
    t.printTree();
    t.add(data[1]);
    t.printTree();
    assert(1==t.size());
    assert(255==t.getMaxValue());
    vec_uch = t.findValues(255);
    assert(2==vec_uch.size());
    vec_uch = vector<uchar*>(); 
    t.deleteTree();
    assert(0==t.size()); 
    cout << "data 1: ";  p->printPixelColor(3, data[1]);
    cout << "Test-2 hsvtree: add duplicate hsv color. Done." << endl;
    cout << endl;
    
    cout << "Test-3 hsvtree" << endl;
    t.add(data[0]);  
    t.add(data[1]); 
    t.add(data[2]);  
    t.printTree();
    assert(2==t.size());
    assert(255==t.getMaxValue());
    vec_uch = t.findValues(255);
    assert(2==vec_uch.size());
    p->printVector(vec_uch);
    vec_uch = vector<uchar*>(); 
    vec_h->clear();
    t.getTreeData(vec_h);
    assert(2==vec_h->size());
    t.deleteTree();
    cout << "Test-3 hsvtree: Done." << endl;
    cout << endl;
    
    cout << "Test-4 hsvtree" << endl;
    t.add(data[0]);
    t.add(data[1]);
    t.add(data[2]);
    t.add(data[3]);
    t.add(data[4]);
    //assert(4==t.size());
    //assert(255==t.getMaxValue());
    //t.printTree();
    
    vec_uch = t.findValues(0);
    assert(1==vec_uch.size()); 
    vec_uch = vector<uchar*>();
    t.printTree();
    
    //vec_h->clear();
    //t.getTreeData(vec_h);
    //assert(4==vec_h->size());

    t.deleteTree();
    t.setHsvDim(hsvtree::SAT);
    t.add(data[0]);
    t.add(data[1]);
    t.add(data[2]);
    t.add(data[3]);
    t.add(data[4]);
    t.printTree();
    assert(3==t.size());
    assert(hsvtree::SAT==t.getHSVDim());
    assert(255==t.getMaxValue());

    t.deleteTree();
    t.setHsvDim(hsvtree::VAL);
    t.add(data[0]);
    t.add(data[1]);
    t.add(data[2]);
    t.add(data[3]);
    t.add(data[4]);
    t.printTree();
    assert(3==t.size());
    assert(hsvtree::VAL==t.getHSVDim());
    assert(255==t.getMaxValue());
    cout << "Test-4 hsvtree: Done." << endl;
    cout << endl;

    t.deleteTree();
    assert(0==t.size());

    delete p;
    p = nullptr;
    delete vec_h;
    vec_h = nullptr;
    return 0;
}