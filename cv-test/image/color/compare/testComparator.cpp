#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "imagecolorvalues.h"
#include "pixel_comparator.h"

using namespace std;
int main(int argc, char* argv[]) {
    cout << "Test pixel_comparator." << endl;

    pixel_comparator* compt = new pixel_comparator();

    uchar b = 255; 
    uchar g = 0; 
    uchar r = 0;
    assert(16711680==compt->getBasicColorKey(b, g, r));
    
    b = 240; g = 0; r = 0;
    assert(16711680==compt->getBasicColorKey(b, g, r));
    
    b = 20; g = 20; r = 20;
    assert(0==compt->getBasicColorKey(b, g, r));

    // Purple: key: 16711807 Color [255, 0, 127]
    b = 255; g = 0; r = 127;
    assert(16711807==compt->getBasicColorKey(b, g, r));
    b = 245; g = 15; r = 120;
    assert(16711807==compt->getBasicColorKey(b, g, r));
    b = 240; g = 15; r = 140;
    assert(16711807==compt->getBasicColorKey(b, g, r));
    
    // Green: key: 65280 Color [0, 255, 0]
    b = 0; g = 255; r = 0;
    assert(65280==compt->getBasicColorKey(b, g, r));
    b = 20; g = 235; r = 10;
    assert(65280==compt->getBasicColorKey(b, g, r));

    // Yellow: key: 65535 Color [0, 255, 255]
    b = 0; g = 255; r = 255;
    assert(65535==compt->getBasicColorKey(b, g, r));
    b = 0; g = 235; r = 235;
    assert(65535==compt->getBasicColorKey(b, g, r));

    // Orange: key: 32767 Color [0, 127, 255]
    b = 0; g = 127; r = 255;
    assert(32767==compt->getBasicColorKey(b, g, r));
    b = 0; g = 112; r = 245;
    assert(32767==compt->getBasicColorKey(b, g, r));
    b = 0; g = 142; r = 245;
    assert(32767==compt->getBasicColorKey(b, g, r));

    // Red: key: 255 Color [0, 0, 255]
    b = 0; g = 0; r = 255;
    assert(255==compt->getBasicColorKey(b, g, r));
    b = 0; g = 0; r = 235;
    assert(255==compt->getBasicColorKey(b, g, r));

    b = 0; g = 0; r = 100;
    assert(imagecolorvalues::NOT_AVAILABLE==compt->getBasicColorKey(b, g, r));

    delete compt;

    cout << "Test pixel_comparator: Done." << endl;

    return 0;
}