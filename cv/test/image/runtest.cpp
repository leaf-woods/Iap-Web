#include <iostream>

#include "test_img_data.h"

using namespace std;

int main(int argc, char* argv[]) {
    string img_base = "/home/linye020603/iap-web/cv/test/image/data/";
    
    cout << "Test image data. Use image base: " << img_base << endl;
    test_img_data* t1 = new test_img_data();
    t1->setImageBase(img_base);
    t1->test_img_data_blue();
    
    delete t1;
    cout << "Test image data: Done." << endl;
    cout << endl;

    return 0;
}
