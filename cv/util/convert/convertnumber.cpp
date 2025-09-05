#include <bitset>
#include <chrono>
#include <iostream>

#include "convertnumber.h"

using namespace std;

typedef std::chrono::high_resolution_clock Clock;

int convertnumber:: getInt(uchar b, uchar g, uchar r){
    return (b<<16) + (g<<8) + r;
}

uchar convertnumber::getUChar(int n) {
    if (n < 0 || n > 255) {
        cout << "Can not get uchar. Invalid number: " << n << endl;
        return '\0';
    }
    std::bitset x = std::bitset<8>(n);
    return static_cast<uchar>(x.to_ulong());
}

void convertnumber:: setUChar3(int n, uchar* p_bgr) {
    if (n < 0 || n > MAX) {
        cout << "Can not set uchar. Invalid number: " << n << endl;
        return;
    }
    std::bitset x = std::bitset<24>(n);
    
    /*
     * @20250816
     * Proved bit shift is much faster than arithmetic for single operation.
     */
    //auto t1 = Clock::now();
    //uchar r = x[0] + x[1]*2 + x[2]*4 + x[3]*8 + x[4]*16 + x[5]*32 + x[6]*64 + x[7]*128;
    //auto t2 = Clock::now();
    //cout << "Time to convert r arithmetic: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << endl;
    //auto t3 = Clock::now();
    uchar r= static_cast<uchar>(x.to_ulong() << 16 >> 16);
    //auto t4 = Clock::now();
    //cout << "Time to convert r bit shift: " << std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count() << endl;

    uchar g = static_cast<uchar>(x.to_ulong() << 8 >> 16);

    uchar b = static_cast<uchar>(x.to_ulong() >> 16);

    p_bgr[0] = b;
    p_bgr[1] = g;
    p_bgr[2] = r;
}
