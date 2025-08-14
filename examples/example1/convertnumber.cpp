#include <bitset>
#include <iostream>
#include "convertnumber.h"

using namespace std;

int convertnumber:: getInt(uchar b, uchar g, uchar r){
    return (b<<16) + (g<<8) + r;
}

uchar convertnumber::getUChar(int n) {
    std::bitset x = std::bitset<8>(n);
    return x[0] + x[1]*2 + x[2]*4 + x[3]*8 + x[4]*16 + x[5]*32 + x[6]*64 + x[7]*128;
}

void convertnumber:: setBGR(int n, uchar* p_bgr) {
    if (n < 0 || n > MAX) {
        cout << "invalid number: " << n << endl;
        exit;
    }
    std::bitset x = std::bitset<24>(n);
    //cout << "x: " << x << endl;
    //std::bitset y = std::bitset<32>(n);
    //cout << "y: " << x << endl;
    
    /// TODO which one is faster
    uchar r = x[0] + x[1]*2 + x[2]*4 + x[3]*8 + x[4]*16 + x[5]*32 + x[6]*64 + x[7]*128;
    //cout << "r: " << static_cast<unsigned>(r) << endl;

    //uchar g = x[8] + x[9]*2 + x[10]*4 + x[11]*8 + x[12]*16 + x[13]*32 + x[14]*64 + x[15]*128;
    uchar g = static_cast<uchar>(x.to_ulong() << 8 >> 16);
    //cout << "g: " << static_cast<unsigned>(g) << endl;

    //uchar b = x[16] + x[17]*2 + x[18]*4 + x[19]*8 + x[20]*16 + x[21]*32 + x[22]*64 + x[23]*128;
    uchar b = static_cast<uchar>(x.to_ulong() >> 16);
    //cout << "b: " << static_cast<unsigned>(b) << endl;

    p_bgr[0] = b;
    p_bgr[1] = g;
    p_bgr[2] = r;
}
