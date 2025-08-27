#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "iap_context.h"
#include "test_img_data.h"

using namespace std;

test_img_data::test_img_data() {
   ctx = new iap_context();
}

test_img_data::~test_img_data() {
   delete ctx;
}

void test_img_data::setImageBase(string path) {
    img_base = path;
}

void test_img_data::set(string fn){
    input = cv::imread(fn);
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
}

double test_img_data::test_blue(std::string f) {
   
    ctx->mats->setImagePath(f);
    ctx->mats->read_to_hsv();

    // Calculate the first range 
    ctx->desc->setColorType(imagecolorvalues::HSV);
    ctx->desc->setDescData(ctx->mats->hsvImage);
    uchar* lower = ctx->desc->getLowerBoundHSV();
    uchar* upper = ctx->desc->getUpperBoundHSV();
    ctx->desc->getPrint()->printPixelColor(lower);
    ctx->desc->getPrint()->printPixelColor(upper);

    //https://www.geeksforgeeks.org/dsa/program-change-rgb-color-model-hsv-color-model/
    /*
     * 20250817 Use bounds to detect blue in the above sample. 
     */
    ctx->mats->in_range_mask(lower, upper);

    return ctx->mats->get_percentage();
}

void test_img_data::test_img_data_blue(){
    // For IMG_4585_S_CR_R1.JPG, open IMG_4585_S_CR_R1_SMALL.JPG with ImageMagick. Result is same.
    string fname = "IMG_4585_S_CR_R1.JPG";

    fname = "img64/IMG_4585_S_CR_R1_S64_11.JPG";
    string fn = img_base + fname; 
    cout << "Test uses file: " << fn << endl;
    double percent = test_blue(fn);
    assert(percent==100.0);
    cout << endl;
    
    fname = "img64/IMG_4585_S_CR_R1_S64_10.JPG";
    fn = img_base + fname; 
    cout << "Test uses file: " << fn << endl;
    percent = test_blue(fn);
    //assert(percent==100.0);
    cout << endl;
}

/// TODO
void test_img_data::test_range(int x, int y){
    // IMG_4585_S_CR_R1.JPG
    // Not in range
    x = 5; y = 14; // cloud
    ctx->mats->printPixelColorValues(x, y);
    // In range
    x = 12; y = 5;  //sky
    ctx->mats->printPixelColorValues(x, y);
    cout << endl;
}

void test_img_data::test_types(){
     // IMG_4585_S_CR_R1.JPG
     cout << "Test of sky pixels and cloud pixels" << endl;
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
        ctx->mats->printPixelColor(0, i, "HSV");
     }
     cout << endl;

     // h: 109-110 s: 121-157 v: 154-162
     cout << "cloud pixels" << endl;
     for (int i=14; i<36; i++) {
        ctx->mats->printPixelColor(0, i, "HSV");
     }
     cout << endl;

    // From the above examples, cloud: h similar, s lower, v higher
    // Verify with weak cloud
    // h: 108-109 s: 155-158 v: 147-152  Verified
    for (int r=2; r<5; r++) {
        for (int c=18; c<20; c++) {
            ctx->mats->printPixelColor(c, r, "HSV");
        }
    }
}