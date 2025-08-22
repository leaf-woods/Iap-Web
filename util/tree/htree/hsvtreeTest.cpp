#include <cassert>
#include <iostream>
#include <opencv2/core.hpp>
#include "hsvtree.h"

using namespace std;

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
    hsvtree t;
    t.setPrint(p);

    uchar hsv[] = {255, 255, 255};
    t.add(hsv);
    assert(255==t.getMaxValue());
    t.printTree();
    t.deleteTree();
    cout << "Test-1 hsvtree: Done." << endl;
    cout << endl;

    cout << "Test-2 hsvtree" << endl;
    t.add(data[1]);
    assert(1==t.size());
    assert(255==t.getMaxValue());
    t.printTree();
    cout << "Test-2 hsvtree: Done." << endl;
    cout << endl;

    cout << "Test-3 hsvtree" << endl;
    t.add(data[2]);
    assert(2==t.size());
    assert(255==t.getMaxValue());
    t.printTree();
    cout << "Test-3 hsvtree: Done." << endl;
    cout << endl;

    cout << "Test-4 hsvtree" << endl;
    t.add(data[0]);
    t.add(data[3]);
    t.add(data[4]);
    assert(4==t.size());
    assert(255==t.getMaxValue());
    t.printTree();
    cout << "Test-4 hsvtree: Done." << endl;
    cout << endl;

    t.deleteTree();
    assert(0==t.size());

    delete p;
    p = nullptr;
    return 0;
}