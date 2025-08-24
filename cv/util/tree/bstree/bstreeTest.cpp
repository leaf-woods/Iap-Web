#include <cassert>
#include <iostream>

#include "bstree.h"

using namespace std;

int main(int argc, char* argv[]) {
    ///*
    cout << "Test-1 bstree" << endl;
    bstree t;
    for (int i=0; i<1; i++) {
        t.add(i);
    }
    cout << endl;
    t.printTree();
    t.deleteTree();
    assert(t.size()==0);
    cout << "Test-1 bstree completed." << endl;
    cout << endl;

    // This is a new tree.
    cout << "Test-2 bstree" << endl;
    t.add(3);
    t.add(5);
    t.add(2);
    t.add(6);
    t.add(4);
    t.add(1);
    t.add(8);
    t.add(7);
    t.add(10);
    t.add(9);
    assert(10==t.size());
    cout << endl;
    t.printTree();
    t.deleteTree();
    assert(0==t.size());
    cout << "Test-2 bstree completed." << endl;
    cout << endl;

    // This is a new tree.
    cout << "Test-3 bstree" << endl;
    t.add(3);
    t.add(5);
    t.add(2);
    t.add(6);
    t.add(4);
    t.add(1);
    t.add(8);
    t.add(7);
    t.add(10);
    t.add(9);
    assert(10==t.size());
    int max = t.getMaxValue();
    assert(10==max);
    cout << "Test-3 bstree completed." << endl;
    cout << endl;

    // Tree t was not deleted since Test-3. Cannot add identical data.
    cout << "Test-4 bstree" << endl;
    t.add(3);
    t.add(5);
    t.add(2);
    t.add(3);
    t.add(2);
    t.printTree();
    assert(10==t.size());
    cout << "Test-4 bstree completed." << endl;
    cout << endl;

    //*/

    cout << "Test-5 bstree" << endl;
    bstree* pt = new bstree();
    for (int i=0; i<3; i++) {
        pt->add(i);
    }
    assert(3==pt->size());
    pt->deleteTree();  // Comment on this line to generate memory leak.
    cout << "Test-5 bstree completed." << endl;
    cout << endl;

    /*
     * Didn't call pt->deleteTree() 
     * Didn't call delete(pt)
     * and create a new instance of pt.
     */
    cout << "Test-6 bstree" << endl;
    pt = new bstree();
    for (int i=0; i<2; i++) {
        pt->add(i);
    }
    assert(2==pt->size());

    cout << "Max: " << pt->getMaxValue() << endl;
    cout << "Test-6 bstree completed." << endl;
    cout << endl;
    
    delete pt;
    
    // Moment destructor of each instance created is called.
    return 0;
}
