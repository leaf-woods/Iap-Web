//https://www.geeksforgeeks.org/dsa/program-change-rgb-color-model-hsv-color-model/
//https://docs.opencv.org/4.6.0/de/d25/imgproc_color_conversions.html#color_convert_rgb_hsv

#include <bits/stdc++.h>
#include <stdlib.h>

#include "calcBgrHsv.h"

using namespace std;

calcBgrHsv::calcBgrHsv() {}

calcBgrHsv::~calcBgrHsv() {}

void calcBgrHsv::toHsvCV(int* hsv, double b, double g, double r)
{

    // R, G, B values are divided by 255
    // to change the range from 0..255 to 0..1
    r = r / 255.0;
    g = g / 255.0;
    b = b / 255.0;

    // h, s, v = hue, saturation, value
    double cmax = max(r, max(g, b)); // maximum of r, g, b
    double cmin = min(r, min(g, b)); // minimum of r, g, b
    double diff = cmax - cmin; // diff of cmax and cmin.
    double h = -1, s = -1;

    // if cmax and cmax are equal then h = 0
    if (cmax == cmin)
        h = 0;

    // if cmax equal r then compute h
    else if (cmax == r)
        h = fmod(60 * ((g - b) / diff) + 360, 360);

    // if cmax equal g then compute h
    else if (cmax == g)
        h = fmod(60 * ((b - r) / diff) + 120, 360);

    // if cmax equal b then compute h
    else if (cmax == b)
        h = fmod(60 * ((r - g) / diff) + 240, 360);

    // if cmax equal zero
    if (cmax == 0)
        s = 0;
    else {
        //s = (diff / cmax) * 100;
        s = (diff / cmax) * 255;
    }
    // compute v
    //double v = cmax * 100;
    double v = cmax * 255;
    //cout << "(" << h << ", " << s << ", " << v << ")" << endl;

    
    //hsv = new int[3]{(int)((h+0.5)/2), (int)(s+0.5), (int)(v+0.5)};
    hsv[0]= (int)((h+0.5)/2);
    hsv[1]= (int)(s+0.5);
    hsv[2]= (int)(v+0.5);
}

double calcBgrHsv::diffBGR(uchar b1, uchar g1, uchar r1, uchar b2, uchar g2, uchar r2) {
    int diff_b = b1 - b2;
    int diff_g = g1 - g2;
    int diff_r = r1 - r2;
    
    return sqrt(diff_b*diff_b + diff_g*diff_g + diff_r*diff_r);
}

double calcBgrHsv::diffHSV(int h1, int s1, int v1, int h2, int s2, int v2) {
    int diff_h = h1 - h2;
    int diff_s = s1 - s2;
    int diff_v = v1 - v2;
    
    return sqrt(diff_h*diff_h + diff_s*diff_s + diff_v*diff_v);
}
