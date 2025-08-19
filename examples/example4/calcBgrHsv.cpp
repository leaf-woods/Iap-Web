//https://www.geeksforgeeks.org/dsa/program-change-rgb-color-model-hsv-color-model/
//https://docs.opencv.org/4.6.0/de/d25/imgproc_color_conversions.html#color_convert_rgb_hsv

#include <bits/stdc++.h>
#include <stdlib.h>

#include "calcBgrHsv.h"

using namespace std;

calcBgrHsv::calcBgrHsv() {}

calcBgrHsv::~calcBgrHsv() {}

void calcBgrHsv::toHsvCV(uchar* hsv, uchar b, uchar g, uchar r)
{
    uchar u_max = max(r, max(g, b));
    uchar u_min = min(r, min(g, b));
    uchar u_diff = u_max - u_min;

    double h = -1, s = -1;

    // if cmax and cmax are equal then h = 0
    if (u_max == u_min)
        h = 0;

    // if cmax equal r then compute h
    else if (u_max == r)
        h = fmod(60 * ((double)(g - b) / (double)u_diff) + 360, 360);

    // if cmax equal g then compute h
    else if (u_max == g)
        h = fmod(60 * ((double)(b - r) / (double)u_diff) + 120, 360);

    // if cmax equal b then compute h
    else if (u_max == b)
        h = fmod(60 * ((double)(r - g) / (double)u_diff) + 240, 360);

    // if cmax equal zero
    if (u_max == 0)
        s = 0;
    else {
        //s = (diff / cmax) * 100;
        s = ((double)u_diff / (double)u_max) * 255;
    }
    
    hsv[0]= (uchar)((h+0.5)/2);
    hsv[1]= (uchar)(s+0.5);
    hsv[2]= (uchar)u_max;
}

double calcBgrHsv::diffBGR(uchar b1, uchar g1, uchar r1, uchar b2, uchar g2, uchar r2) {
    int diff_b = b1 - b2;
    int diff_g = g1 - g2;
    int diff_r = r1 - r2;
    
    return sqrt(diff_b*diff_b + diff_g*diff_g + diff_r*diff_r);
}

double calcBgrHsv::diffHSV(uchar h1, uchar s1, uchar v1, uchar h2, uchar s2, uchar v2) {
    int diff_h = h1 - h2;
    int diff_s = s1 - s2;
    int diff_v = v1 - v2;
    
    return sqrt(diff_h*diff_h + diff_s*diff_s + diff_v*diff_v);
}
