#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "calcBgrHsv.h"

using namespace std;

int main(int argc, char* argv[]) {

    cout << "Test toHsvCV()" << endl;
    calcBgrHsv calc;
    int hsv[3];
    calc.toHsvCV(hsv, 165.0, 107.0, 72.0);
    cout << "h:" << hsv[0] << " s:" << hsv[1] << " v:" << hsv[2] << endl;
    cout << endl;
    // 159, 105, 75 masked
    // 150, 92, 57 not masked
    calc.toHsvCV(hsv, 158, 104, 74);
    cout << "h:" << hsv[0] << " s:" << hsv[1] << " v:" << hsv[2] << endl;
    cout << endl;

    calc.toHsvCV(hsv, 150, 91, 59);
    cout << "h:" << hsv[0] << " s:" << hsv[1] << " v:" << hsv[2] << endl;
    cout << endl;
    //delete hsv;
    cout << "Test toHsvCV(): Done" << endl;
    cout << endl;

    cout << "Test diffBGR()" << endl;
    // [0,0] 142,84,49
    // [0,9] 155,98,66
    // 
    double diff_bgr = calc.diffBGR(142, 84, 49, 155, 98, 66);
    cout << "diff_bgr: " << diff_bgr << endl;
    int hsv_a[3];
    calc.toHsvCV(hsv_a, 142, 84, 49); 
    int hsv_b[3];
    calc.toHsvCV(hsv_b, 155, 98, 66);
    double diff_hsv = calc.diffHSV(hsv_a[0], hsv_a[1], hsv_a[2], hsv_b[0], hsv_b[1], hsv_b[2]);
    cout << "diff_hsv: " << diff_hsv << endl;
    cout << "Test diffBGR(): Done" << endl;
    cout << endl;

    cout << "Test distance of artitrary two pixels on the image." << endl;
    std::string fname = "color-wheel.png"; 
    cout << "Test using file: " << fname << endl;
    cv::Mat input = cv::imread(fname);

    cv::Mat hsvImage;
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);

    // Start point: p1 [149, 139], p2 [74, 74]
    // Check whether there exists p3 such that diffBGR(p1, p2) > diffBGR(p1, p3) 
    // and diffHSV(p1, p2) < diffHSV(p1, p3)
    cv::Vec<unsigned char, 3> P1 = input.at<cv::Vec3b>(149, 139);
    cv::Vec<unsigned char, 3> P2 = input.at<cv::Vec3b>(74, 74);
    double DF_BGR_1 = calc.diffBGR(P1[0], P1[1], P1[2], P2[0], P2[1], P2[2]);
    cout << "DF_BGR_1: " << DF_BGR_1 << endl;
    double diff_bgr_2;

    cv::Vec<unsigned char, 3> H_P1 = hsvImage.at<cv::Vec3b>(149, 139);
    cv::Vec<unsigned char, 3> H_P2 = hsvImage.at<cv::Vec3b>(74, 74);
    double DF_HSV_1 = calc.diffHSV(H_P1[0], H_P1[1], H_P1[2], H_P2[0], H_P2[1], H_P2[2]);
    cout << "DF_HSV_1: " << DF_HSV_1 << endl;
    double diff_hsv_2; 
    
    cv::Vec<unsigned char, 3> entry_bgr;
    cv::Vec<unsigned char, 3> entry_hsv;
    // @20250818 This is the process to find the exception point at [30, 147]
    /*
    for (int i=0; i<input.rows; i++) {
        for (int j=0; j<input.cols; j++) {
            entry_bgr = input.at<cv::Vec3b>(i,j);
            entry_hsv = hsvImage.at<cv::Vec3b>(i,j);
            diff_bgr_2=calc.diffBGR(P1[0], P1[1], P1[2], entry_bgr[0], entry_bgr[1], entry_bgr[2]);
            diff_hsv_2=calc.diffHSV(H_P1[0], H_P1[1], H_P1[2], entry_hsv[0], entry_hsv[1], entry_hsv[2]);
            if (DF_BGR_1 > diff_bgr_2) {
                assert(DF_HSV_1 > diff_hsv_2);
            }
            if (DF_BGR_1 < diff_bgr_2) {
                cout << "case lt: [ " << i << ", " << j << " ]" << endl;
                assert(DF_HSV_1 < diff_hsv_2);
            }
        }
    }
    */

    cout << endl;
    // [30, 147]
    cout << "Exception found at [30, 147]" << endl;
    cout << "Use P1 [149, 139], P2 [74, 74]" << endl;
    cout << "P1 color: [149, 139] (" << static_cast<unsigned>(P1[0]) << ", " << static_cast<unsigned>(P1[1]) << ", " << static_cast<unsigned>(P1[2]) << " )" << endl;
    cout << "P2 color: [74, 74]   (" << static_cast<unsigned>(H_P1[0]) << ", " << static_cast<unsigned>(H_P1[1]) << ", " << static_cast<unsigned>(H_P1[2]) << " )" << endl;
    
    entry_bgr = input.at<cv::Vec3b>(30,147);
    entry_hsv = hsvImage.at<cv::Vec3b>(30,147);
    diff_bgr_2=calc.diffBGR(P1[0], P1[1], P1[2], entry_bgr[0], entry_bgr[1], entry_bgr[2]);
    diff_hsv_2=calc.diffHSV(H_P1[0], H_P1[1], H_P1[2], entry_hsv[0], entry_hsv[1], entry_hsv[2]);

    cout << "DF_BGR_1: " << DF_BGR_1 << " DF_BGR_2: " << diff_bgr_2 << endl;
    cout << "DF_HSV_1: " << DF_HSV_1 << " DF_HSV_2: " << diff_hsv_2 << endl;
    cout << endl;
    cout << "Pixel color: [30, 147] ( " << static_cast<unsigned>(entry_bgr[0]) << ", " << static_cast<unsigned>(entry_bgr[1]) << ", " << static_cast<unsigned>(entry_bgr[2]) << " )" << endl;
    
    cout << "Test distance of artitrary two pixels on the image: Done." << endl;
    cout << endl;
    
    return 0;
}
