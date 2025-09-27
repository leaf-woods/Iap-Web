//https://www.geeksforgeeks.org/dsa/program-change-rgb-color-model-hsv-color-model/
//https://docs.opencv.org/4.6.0/de/d25/imgproc_color_conversions.html#color_convert_rgb_hsv

#include <bits/stdc++.h>
#include <stdlib.h>

#include <iostream>

#include "convert_bgrhsv.h"

using namespace std;

/*
 * Dangerous parameter uchar* hsv
 * If caller is: uchar* hsv; then calls toHsvCV(hsv, b, g, r) we get SMF.
 * Caller has to ensure argument passed to function toHsvCV() is a size 3 uchar array.
 * Example: uchar hsv[3] = {0}; 
 *          uchar hsv[3];
 */
void convert_bgrhsv::toHsvCV(size_t channel, uchar* hsv, uchar b, uchar g, uchar r)
{
    uchar u_max = max(r, max(g, b));
    uchar u_min = min(r, min(g, b));
    uchar u_diff = u_max - u_min;

    double h = -1, s = -1;

    if (u_max == u_min)
        h = 0;

    else if (u_max == r)
        h = fmod(60 * ((double)(g - b) / (double)u_diff) + 360, 360);

    else if (u_max == g)
        h = fmod(60 * ((double)(b - r) / (double)u_diff) + 120, 360);

    else if (u_max == b)
        h = fmod(60 * ((double)(r - g) / (double)u_diff) + 240, 360);

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

/*
 * when h < 217.5 and h > 215.5, toHsvCV() will generate h = 108
 * This means given h=108, we don't know the exact classical Hue calculated from rgb.
 * Which means we can not get the original rgb.
 *
 * From CV S to Classical S: s==0? 0 : 100* s/255.0; 
 * From CV V to Classical V: v==0? 0 : 100*v/255.0;
 */
void convert_bgrhsv::toHsv(size_t channel, double* hsv, uchar b, uchar g, uchar r)
{
    double cmax = max(r, max(g, b)); 
    double cmin = min(r, min(g, b)); 
    double diff = cmax - cmin;
    double h = -1, s = -1;

    if (cmax == cmin)
        h = 0;

    else if (cmax == r)
        h = fmod(60 * ((g - b) / diff) + 360, 360);

    else if (cmax == g)
        h = fmod(60 * ((b - r) / diff) + 120, 360);

    else if (cmax == b)
        h = fmod(60 * ((r - g) / diff) + 240, 360);

    if (cmax == 0)
        s = 0;
    else
        s = (diff / cmax) * 100;

    double v = cmax * 100/255.0;
    
    hsv[0] = h;
    hsv[1] = s;
    hsv[2] = v;
}

// https://www.codespeedy.com/hsv-to-rgb-in-cpp/
// Input is traditional hsv
void convert_bgrhsv::toBgr(size_t channel, uchar* bgr, double H, double S,double V) {
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        cout<<"The givem HSV values are not in valid range"<<endl;
        return;
    }
    double s = S/100;
    double v = V/100;
    double C = s*v;
    double X = C*(1-abs(fmod(H/60.0, 2)-1));
    double m = v-C;
    double r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    double R = (r+m)*255;
    double G = (g+m)*255;
    double B = (b+m)*255;
    
    bgr[0]=(uchar)round(B); bgr[1]=(uchar)round(G); bgr[2]=(uchar)round(R);
}

double convert_bgrhsv::diffBGR(uchar b1, uchar g1, uchar r1, uchar b2, uchar g2, uchar r2) {
    int diff_b = b1 - b2;
    int diff_g = g1 - g2;
    int diff_r = r1 - r2;
    
    return sqrt(diff_b*diff_b + diff_g*diff_g + diff_r*diff_r);
}

double convert_bgrhsv::diffHSV(uchar h1, uchar s1, uchar v1, uchar h2, uchar s2, uchar v2) {
    int diff_h = h1 - h2;
    int diff_s = s1 - s2;
    int diff_v = v1 - v2;
    
    return sqrt(diff_h*diff_h + diff_s*diff_s + diff_v*diff_v);
}