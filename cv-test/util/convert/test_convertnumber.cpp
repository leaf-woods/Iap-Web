#include <opencv2/core.hpp>

#include "convertnumber.h"

#include <iostream>

using namespace std;
void printColor(uchar b, uchar g, uchar r) {
    cout << "Color [" << static_cast<unsigned>(b) << ", " << static_cast<unsigned>(g) << ", " << static_cast<unsigned>(r) << "]" << endl;
}

// copied from iap_print.cpp
void printPixelColor(size_t channel, uchar* array) {
    cout << "Color [" << static_cast<unsigned>(array[0]) << ", " << static_cast<unsigned>(array[1]) << ", " << static_cast<unsigned>(array[2]) << "]" << endl;
}

int main(int argc, char* argv[]) {

    convertnumber* convert = new convertnumber();
    
    uchar b = 0; 
    uchar g = 0;
    uchar r = 0;

    uchar bgr[3] = {0};

    int n = convert->getInt(b, g, r);
    assert(0==n);
    cout << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 0; r = 127;
    n = convert->getInt(b, g, r);
    cout << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 0; r = 255;
    n = convert->getInt(b, g, r);
    cout << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 127; r = 0;
    n = convert->getInt(b, g, r);
    cout << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);
    
    cout << endl;
    b = 0; g = 255; r = 0;
    n = convert->getInt(b, g, r);
    cout << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 127; r = 127;
    n = convert->getInt(b, g, r);
    cout << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 255; g = 0; r = 127;
    n = convert->getInt(b, g, r);
    cout << "Purple: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 255; g = 0; r = 0;
    n = convert->getInt(b, g, r);
    cout << "Blue: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 255; r = 0;
    n = convert->getInt(b, g, r);
    cout << "Green: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 255; r = 255;
    n = convert->getInt(b, g, r);
    cout << "Yellow: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 127; r = 255;
    n = convert->getInt(b, g, r);
    cout << "Orange: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    cout << endl;
    b = 0; g = 0; r = 255;
    n = convert->getInt(b, g, r);
    cout << "Red: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    // b-like
    cout << endl;
    b = 0; g = 0; r = 255;
    n = convert->getInt(b, g, r);
    cout << "Red: " << "key: " << n << " ";
    printColor(b, g, r);
    convert->setUChar3(n, bgr);
    assert(b==bgr[0] && g==bgr[1] && r==bgr[2]);
    printPixelColor(3, bgr);

    b = 0; g = 0; r = 240;
    n = convert->getInt(b, g, r);
    cout << "Red: " << "key: " << n << " ";
    printColor(b, g, r);
    
    return 0;
}