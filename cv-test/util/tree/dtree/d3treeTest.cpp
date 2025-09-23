#include <cassert>
#include <iostream>
#include <opencv2/core.hpp>
#include "d3tree.h"

using namespace std;

int main(int argc, char* argv[]) {

    int LEN = 3;

    uchar data[5][3] = { {255, 255, 255}, 
                     {255, 0, 0},
                     {128, 128, 128},
                     {0, 0, 0},
                     {220, 255, 255}
                    };

    int max = 0;
    iap_print* p = new iap_print();

    cout << "Test-1 d3tree" << endl;
    /*
     * @20250919
     * This is valid in C++. We do not use this coding style in iapcv.
     */
    d3tree t;
    t.setPrint(p);
    t.printTree();
    assert(0==t.size());
    assert(dimensions::D_X==t.getDim());
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
    t.add(LEN, hsv_data);
    assert(1==t.size());
    assert(dimensions::D_X==t.getDim());
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
    cout << "Test-1 d3tree: Done." << endl;
    cout << endl;

    cout << "Test-2 d3tree: add duplicate hsv color. " << endl;
    t.add(LEN, data[1]); 
    assert(1==t.size());
    assert(255==t.getMaxValue());
    t.printTree();
    t.add(LEN, data[1]);
    t.printTree();
    assert(1==t.size());
    assert(255==t.getMaxValue());
    vec_uch = t.findValues(255);
    assert(2==vec_uch.size());
    vec_uch = vector<uchar*>(); 
    t.deleteTree();
    assert(0==t.size()); 
    cout << "data 1: ";  p->printPixelColor(3, data[1]);
    cout << "Test-2 d3tree: add duplicate hsv color. Done." << endl;
    cout << endl;
    
    cout << "Test-3 hsvtree" << endl;
    t.add(LEN, data[0]);  
    t.add(LEN, data[1]); 
    t.add(LEN, data[2]);  
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
    cout << "Test-3 d3tree: Done." << endl;
    cout << endl;
    
    cout << "Test-4 d3tree" << endl;
    t.add(LEN, data[0]);
    t.add(LEN, data[1]);
    t.add(LEN, data[2]);
    t.add(LEN, data[3]);
    t.add(LEN, data[4]);
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
    t.setDim(DimType::HSV, dimensions::SAT);
    t.add(LEN, data[0]);
    t.add(LEN, data[1]);
    t.add(LEN, data[2]);
    t.add(LEN, data[3]);
    t.add(LEN, data[4]);
    t.printTree();
    assert(3==t.size());
    assert(dimensions::SAT==t.getDim());
    assert(255==t.getMaxValue());

    t.deleteTree();
    t.setDim(DimType::HSV, dimensions::VAL);
    t.add(LEN, data[0]);
    t.add(LEN, data[1]);
    t.add(LEN, data[2]);
    t.add(LEN, data[3]);
    t.add(LEN, data[4]);
    t.printTree();
    assert(3==t.size());
    assert(dimensions::VAL==t.getDim());
    assert(255==t.getMaxValue());
    t.deleteTree();
    cout << "Test-4 d3tree: Done." << endl;
    cout << endl;

    cout << "Test-5 d3tree: change dimension type/dimension after adding nodes" << endl;
    t.setDim(DimType::HSV, dimensions::VAL);
    t.add(LEN, hsv_data);
    t.setDim(DimType::HSV, dimensions::SAT);
    assert(dimensions::VAL==t.getDim());
    t.setDim(DimType::XYZ, dimensions::D_X);
    assert(DimType::HSV==t.getDimensionType() && dimensions::VAL==t.getDim());
    t.deleteTree();
    cout << "Test-5 d3tree: change dimension type/dimension after adding nodes: Done." << endl;
    cout << endl;

    cout << "Test-6 d3tree: v3 size" << endl;
    t.setDim(DimType::HSV, dimensions::VAL);
    t.add(LEN, hsv_data);
    /***  Assertion failed ***/
    /*
    uchar tmp_data[] = {1, 1, 255, 1};
    int length = (sizeof(tmp_data)/sizeof(*tmp_data)) ;
    cout << "length: " << length << endl;
    t.add(length, tmp_data); 
    uchar tmp_data2[] = {1, 255};
    length = (sizeof(tmp_data2)/sizeof(*tmp_data2)) ;
    cout << "length: " << length << endl;
    t.add(length, tmp_data2);
    */
    t.printTree();
    assert(1==t.size());
    t.deleteTree();
    cout << "Test-6 d3tree: v3 size: Done" << endl;
    cout << endl;
    
    //assert(0==t.size());

    delete p;
    p = nullptr;
    delete vec_h;
    vec_h = nullptr;
    return 0;
}