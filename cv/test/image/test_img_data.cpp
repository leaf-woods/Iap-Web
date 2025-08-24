#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

//#include "iap_context.h"
#include "test_img_data.h"

using namespace std;

test_img_data::test_img_data() {
    img_base = "/home/linye020603/iap-web/cv/test/image/data/";
    cout << "Use image base: " << img_base << endl;
}

void test_img_data::set(string fn){
    input = cv::imread(fn);
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
}

void test_img_data::test_img_data_blue(){
    // Open IMG_4585_S_CR_R1_SMALL.JPG with ImageMagick. Result is same.
    fname = "IMG_4585_S_CR_R1.JPG";

    string fn = img_base + fname;
    set(fn);  
    cout << "Test using file: " << fname << endl;
    
    //https://www.geeksforgeeks.org/dsa/program-change-rgb-color-model-hsv-color-model/
    /*
     * 20250817 Use bounds to detect blue in the above sample. 
     */
    int lower_h = 100;
    int lower_s = 158; //150;
    int lower_v = 0;

    int upper_h = 120; //140;
    int upper_s = 255;
    int upper_v = 155; //255;

    /*
    bh_max: 109 gs_max: 183 rv_max: 152
    bh_min: 108 gs_min: 175 rv_min: 142
    */

    lower_h = 108; upper_h = 109;
    lower_s = 175; upper_s = 183;
    lower_v = 142; upper_v = 152;
    
    cv::inRange(hsvImage, cv::Scalar(lower_h, lower_s, lower_v), cv::Scalar(upper_h,upper_s,upper_v), hueMask);

    double imageSize = hsvImage.cols * hsvImage.rows;
    double bluePercentage = 100*(((double) cv::countNonZero(hueMask))/imageSize);
    cout << "Percenage of blue: " << bluePercentage << "%" << endl;
}

void test_img_data::test_img_data_range(){
    fname = "IMG_4585_S_CR_R1.JPG";

    string fn = img_base + fname;
    set(fn);  
    cout << "Test using file: " << fname << endl;

    //https://www.geeksforgeeks.org/dsa/program-change-rgb-color-model-hsv-color-model/
    /*
     * 20250817 Use bounds to detect blue in the above sample. 
     */
    int lower_h = 100;
    int lower_s = 158; //150;
    int lower_v = 0;

    int upper_h = 120; //140;
    int upper_s = 255;
    int upper_v = 155; //255;

    /*
    bh_max: 109 gs_max: 183 rv_max: 152
    bh_min: 108 gs_min: 175 rv_min: 142
    */

    lower_h = 108; upper_h = 109;
    lower_s = 175; upper_s = 183;
    lower_v = 142; upper_v = 152;
    
    cv::inRange(hsvImage, cv::Scalar(lower_h, lower_s, lower_v), cv::Scalar(upper_h,upper_s,upper_v), hueMask);

    // Not in range
    int x = 5; int y = 14; // cloud

    cv::Vec<unsigned char, 3> entry = input.at<cv::Vec3b>(y, x);
    cout << "b: " << static_cast<unsigned>(entry[0]) << " g: " << static_cast<unsigned>(entry[1]) << " r: " << static_cast<unsigned>(entry[2]) << endl;

    entry = hsvImage.at<cv::Vec3b>(y, x);
    cout << "h: " << static_cast<unsigned>(entry[0]) << " s: " << static_cast<unsigned>(entry[1]) << " v: " << static_cast<unsigned>(entry[2]) << endl;

    entry = hueMask.at<cv::Vec3b>(y, x);
    cout << "masked b: " << static_cast<unsigned>(entry[0]) << " masked g: " << static_cast<unsigned>(entry[1]) << " masked r: " << static_cast<unsigned>(entry[2]) << endl;
    cout << endl;

    // In range
    x = 12; y = 5;  //sky

    entry = input.at<cv::Vec3b>(y, x);
    cout << "b: " << static_cast<unsigned>(entry[0]) << " g: " << static_cast<unsigned>(entry[1]) << " r: " << static_cast<unsigned>(entry[2]) << endl;

    entry = hsvImage.at<cv::Vec3b>(y, x);
    cout << "h: " << static_cast<unsigned>(entry[0]) << " s: " << static_cast<unsigned>(entry[1]) << " v: " << static_cast<unsigned>(entry[2]) << endl;

    entry = hueMask.at<cv::Vec3b>(y, x);
    cout << "masked h: " << static_cast<unsigned>(entry[0]) << " masked s: " << static_cast<unsigned>(entry[1]) << " masked v: " << static_cast<unsigned>(entry[2]) << endl;
    cout << endl;
}

void test_img_data::test_img_data_types(){
    fname = "IMG_4585_S_CR_R1.JPG";

    string fn = img_base + fname;
    set(fn); 
    cout << "Test using file: " << fname << endl;
    
     cout << "Testing of sky pixels and cloud pixels" << endl;
    /*
     * @20250822
     * Use ImageMagick to open file IMG_4585_S_CR_R1.JPG
     * (18,2) (19,2) (18,3) (19,3) (18,4) (19,4) : weak cloud
     * (0, 14) to (0, 38) cloud
     * (0, 0) to (0, 30) sky
     */
     // Find range of these pixels hsv

     cv::Vec<unsigned char, 3> entry; 
     // h: 108-109 s: 157-177 v: 142-148
     cout << "sky pixels" << endl;
     for (int i=0; i<30; i++) {
         entry = hsvImage.at<cv::Vec3b>(0, i);
         // check range of hsv
         cout << "h: " << static_cast<unsigned>(entry[0]) << " s: " << static_cast<unsigned>(entry[1]) << " v: " << static_cast<unsigned>(entry[2]) << endl;
     }
     cout << endl;

     // h: 109-110 s: 121-157 v: 154-162
     cout << "cloud pixels" << endl;
     for (int i=14; i<36; i++) {
         entry = hsvImage.at<cv::Vec3b>(i, 0);
         // check range of hsv
         cout << "h: " << static_cast<unsigned>(entry[0]) << " s: " << static_cast<unsigned>(entry[1]) << " v: " << static_cast<unsigned>(entry[2]) << endl;
     }
     cout << endl;

    // From the above examples, cloud: h similar, s lower, v higher
    // Verify with weak cloud
    // h: 108-109 s: 155-158 v: 147-152  Verified
    for (int r=2; r<5; r++) {
        for (int c=18; c<20; c++) {
            entry = hsvImage.at<cv::Vec3b>(r, c);
            // check range of hsv
            cout << "h: " << static_cast<unsigned>(entry[0]) << " s: " << static_cast<unsigned>(entry[1]) << " v: " << static_cast<unsigned>(entry[2]) << endl;
     
        }
    }
}