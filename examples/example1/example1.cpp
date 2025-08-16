//https://stackoverflow.com/questions/35866411/opencv-how-to-detect-lines-of-a-specific-colour
//https://stackoverflow.com/questions/72115357/opencv-blue-color-ranges-detection
//https://stackoverflow.com/questions/12357732/hsv-color-ranges-table
//https://math.stackexchange.com/questions/556341/rgb-to-hsv-color-conversion-algorithm

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <cassert>
#include <ctime>
#include <iostream>

#include "imagecolordesc.h"
#include "convertnumber.h"

using namespace std;

int main(int argc, char* argv[])
{
    time_t timestamp = time(NULL);
    cout << ctime(&timestamp) << endl;

    /*** Test opencv basic */
    cout << "Test opencv first try." << endl;
    // white
    const int lower_h = 90;
    const int lower_s = 10;
    const int lower_v = 180;

    // gray
    const int upper_h = 120;
    const int upper_s = 50;
    const int upper_v = 230;

    std::string fname = "IMG_9898_SMALL.JPG"; 

    cv::Mat input = cv::imread(fname);

    cv::Mat hsvImage;
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);

    cv::Mat hueMask;
    cv::inRange(hsvImage, cv::Scalar(lower_h, lower_s, lower_v), cv::Scalar(upper_h,upper_s,upper_v), hueMask);

    double imageSize = hsvImage.cols * hsvImage.rows;
    double bluePercentage = 100*(((double) cv::countNonZero(hueMask))/imageSize);
    cout << "Percenage of blue: " << bluePercentage << "%" << endl;

    /*
    cv::imshow("desired color", hueMask);
    cv::imshow("input", input);
    cv::waitKey(0);
    */
    //cout << hsvImage.rowRange(0, 1) << endl;
    cout << endl;

    /*** Test imagecolordesc.cpp */
    cout << "Test imagecolordesc" << endl;
    imagecolordesc desc;
    ///*
    desc.setDescData(input);
    desc.printMap();
    desc.printColorValueTree();
    desc.printMinMax();
    cout << endl;
    //*/

    /*** Use integer calculated base on each pixel's bgr value as key in p_map.
     *** Reason: unordered_map<cv::Vec<unsigned char, 3>*, std::vector<int*>*> p_map
     ***         generates an iterator referencing to cv::Mat& mat
     */
    cout << "Test uniqueness" << endl; 
    uchar b = 255; uchar g = 255; uchar r = 255;
    /// precedence
    int s = (b<<16) + (g<<8) + r;
    cout << "sum: " << s << endl;

    cout << "b shifted: " << (b<<16) << " g shifted: " << (g<<8) << endl;
    cout << "sum: " << (b<<16) + (g<<8) + r << endl;

    int r_d = 255;
    int g_d = pow(2, 8) * 255;
    int b_d = pow(2, 16) * 255;

    cout << "sum: " << r_d+g_d+b_d << endl;
    cout << endl;

    /*** Test convertnumber.cpp */
    cout << "Test convernumber" << endl;
    convertnumber convert;
    assert(s==convertnumber::MAX);

    uchar bgr[] = {0, 0, 0};
    convert.setBGR(s, bgr);
    assert(bgr[0]==b); assert(bgr[1]==g); assert(bgr[2]==r);
    convert.setBGR(s+1, bgr);
    
    convert.setBGR(s-1, bgr);
    assert(bgr[0]==b); assert(bgr[1]==g); assert(bgr[2]==r-1);
    convert.setBGR(s-256, bgr);
    assert(bgr[0]==b); assert(bgr[1]==g-1); assert(bgr[2]==r);
    convert.setBGR(s-65536, bgr);
    assert(bgr[0]==b-1); assert(bgr[1]==g); assert(bgr[2]==r);

    assert(s-1==convert.getInt(b,g,r-1));
    assert(s-256==convert.getInt(b,g-1,r));
    assert(s-65536==convert.getInt(b-1,g,r));

    assert(r_d==static_cast<unsigned>(convert.getUChar(r)));
    assert(0==static_cast<unsigned>(convert.getUChar(0)));
    assert(r_d-1==static_cast<unsigned>(convert.getUChar(r_d-1)));
    cout << endl;
    
    
    cout << endl;

    return 0;
    
}
