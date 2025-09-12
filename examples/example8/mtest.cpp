#include <ctime>
#include <iostream>

#include "mtest.h"

using namespace std;
mtest* mtest::create(string msg) {
    time_t timestamp;
    time(&timestamp);
    cout << msg << " " << "create at: " << ctime(&timestamp) << endl;
    return new mtest();
}

mtest* mtest::create() {
    time_t timestamp;
    time(&timestamp);
    cout << "create at: " << ctime(&timestamp) << endl;
    return new mtest();
}