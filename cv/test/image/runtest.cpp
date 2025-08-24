#include <iostream>

#include "test_img_data.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Test image data." << endl;
    test_img_data* t1 = new test_img_data(); 
    t1->test_img_data_blue();
    t1->test_img_data_range();
    t1->test_img_data_types();
    delete t1;
    cout << "Test image data: Done." << endl;
    cout << endl;

    return 0;
}
