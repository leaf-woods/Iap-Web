#include <cassert>
#include <iostream>

#include "colorvaluetree.h"

using namespace std;

int main(int argc, char* argv[]) {

    iap_print* p = new iap_print();
    ///*
    cout << "Test-1 colorvaluetree" << endl;
    colorvaluetree t;
    t.setPrint(p);
    t.add(0, 0);
    t.add(1, -1);
    assert(t.size()==0);
    t.printTree();
    t.deleteTree();
    assert(t.size()==0);
    cout << "Test-1 colorvaluetree completed." << endl;
    cout << endl;

    // This is a new tree.
    cout << "Test-2 colorvaluetree" << endl;
    t.add(3, 3000);
    t.add(5, 5000);
    t.add(2, 2000);
    t.add(6, 6000);
    t.add(4, 4000);
    t.add(1, 1000);
    t.add(8, 8000);
    t.add(7, 7000);
    t.add(10, 10000);
    t.add(9, 9000);
    assert(10==t.size());
    cout << endl;
    t.printTree();
    t.deleteTree();
    assert(0==t.size());
    cout << "Test-2 colorvaluetree completed." << endl;
    cout << endl;

    // This is a new tree.
    cout << "Test-3 colorvaluetree" << endl;
    t.add(3, 3000);
    t.add(5, 5000);
    t.add(2, 2000);
    t.add(6, 6000);
    t.add(4, 4000);
    t.add(1, 1000);
    t.add(8, 8000);
    t.add(7, 7000);
    t.add(10, 10000);
    t.add(9, 9000);
    assert(10==t.size());
    int max = t.getMaxValue();
    assert(10==max);
    cout << "Test-3 colorvaluetree completed." << endl;
    cout << endl;

    // Tree t was not deleted since Test-3. Cannot add identical data.
    cout << "Test-4 colorvaluetree" << endl;
    t.add(3, 3000);
    t.add(5, 5000);
    t.add(2, 2000);
    t.add(3, 3000);
    t.add(2, 2000);
    t.printTree();
    assert(10==t.size());
    cout << "Test-4 colorvaluetree completed." << endl;
    cout << endl;

    //*/

    cout << "Test-5 colorvaluetree" << endl;
    colorvaluetree* pt = new colorvaluetree();
    pt->setPrint(p);
    for (int i=0; i<3; i++) {
        pt->add(i, i*1000);
    }
    assert(2==pt->size());
    pt->deleteTree();  // Comment on this line to generate memory leak.
    delete pt;
    cout << "Test-5 colorvaluetree completed." << endl;
    cout << endl;

    /*
     * Memory leak.
     * Didn't call pt->deleteTree() 
     * Didn't call delete(pt)
     * and create a new instance of pt.
     */
    cout << "Test-6 colorvaluetree" << endl;
    pt = new colorvaluetree();
    pt->setPrint(p);
    for (int i=0; i<2; i++) {
        pt->add(i, i*1000);
    }
    assert(1==pt->size());
    delete pt;
    cout << "Test-6 colorvaluetree completed." << endl;
    cout << endl;
    
    cout << "Test-7 colorvaluetree" << endl;
    pt = new colorvaluetree();
    pt->setPrint(p);
    for (int i=1; i<3; i++) {
        pt->add(i, i*1000);
    }
    assert(2==pt->size());
    std::string s = pt->getContents();
    cout << "Contents: " << endl;
    cout << s << endl;
    delete pt;
    cout << "Test-7 colorvaluetree completed." << endl;
    cout << endl;

    cout << "Test-8 colorvaluetree" << endl;
    pt = new colorvaluetree();
    pt->setPrint(p);
    for (int i=1; i<10; i++) {
        pt->add(i, i*1000);
    }
    assert(9==pt->size());
    pt->add(3, 100);
    pt->add(6, 200);
    assert(9==pt->size());
    pt->add(20, 200);
    assert(10==pt->size());
    assert(20==pt->getMaxValue());
    s = pt->getContents();
    cout << "Contents: " << endl;
    cout << s << endl;
    delete pt;
    cout << "Test-8 colorvaluetree completed." << endl;
    cout << endl;
    
    delete p;
    // Moment destructor of each instance created is called.
    return 0;
}