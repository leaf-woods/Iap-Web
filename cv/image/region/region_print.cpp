#include <iostream>

#include "region_print.h"

using namespace std;
void region_print::printMap(string which, const map<int, vector<int*>*>& m) {
    cout << "Print map: " << which << endl;
    for (auto it=m.begin(); it!=m.end(); it++) {
        cout << "offset: " << it->first << " vector size: " << it->second->size() << " { ";
        for (int i=0; i<it->second->size(); i++) {
            cout << " [" << it->second->at(i)[0] << ", " << it->second->at(i)[1] << "] ";   
        }
        cout << " }" << endl;
    }
}

void region_print::printQueue(string which, const deque<span_node*>& q) {
    cout << "Print deque. " << which << " size: " << q.size();
    int s = q.size();
    if (s == 0) {
        cout << "Empty queue." << endl;
        return;
    }
    for (span_node* p : q) {
        cout << p->offset << " ; ";
    }
    cout << endl;
}

void region_print::printSpan(const span_node& sp) {
    if (sp.type == span_constants::COL) {
        cout << "Col offset: ";
    }
    else {
        cout << "Row offset: ";
    }
    cout << sp.offset << " bounds: [ " << sp.span[0] << " , " << sp.span[1] << " ]" << endl;
}

void region_print::printBorderPixelsDiff(const vector<border_pixel_diff_node*>& bv) {
    cout << "Print border pixels diff. size: " << bv.size() << endl;
    for (int i=0; i<bv.size(); i++) {
        bv.at(i)->print();
    }
}
