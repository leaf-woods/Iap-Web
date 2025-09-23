#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "imagecolorvalues.h"
#include "imagereader.h"
#include "pixel_comparator.h"
//#include "sky_init_train.h"

using namespace std;
int main(int argc, char* argv[]) {
    cout << "Test pixel_comparator." << endl;

    pixel_comparator* compt = new pixel_comparator();

    uchar b = 255; 
    uchar g = 0; 
    uchar r = 0;
    assert(16711680==compt->getBasicColorKey(b, g, r));
    
    b = 240; g = 0; r = 0;
    assert(16711680==compt->getBasicColorKey(b, g, r));
    
    b = 20; g = 20; r = 20;
    assert(0==compt->getBasicColorKey(b, g, r));

    // Purple: key: 16711807 Color [255, 0, 127]
    b = 255; g = 0; r = 127;
    assert(16711807==compt->getBasicColorKey(b, g, r));
    b = 245; g = 15; r = 120;
    assert(16711807==compt->getBasicColorKey(b, g, r));
    b = 240; g = 15; r = 140;
    assert(16711807==compt->getBasicColorKey(b, g, r));
    
    // Green: key: 65280 Color [0, 255, 0]
    b = 0; g = 255; r = 0;
    assert(65280==compt->getBasicColorKey(b, g, r));
    b = 20; g = 235; r = 10;
    assert(65280==compt->getBasicColorKey(b, g, r));

    // Yellow: key: 65535 Color [0, 255, 255]
    b = 0; g = 255; r = 255;
    assert(65535==compt->getBasicColorKey(b, g, r));
    b = 0; g = 235; r = 235;
    assert(65535==compt->getBasicColorKey(b, g, r));

    // Orange: key: 32767 Color [0, 127, 255]
    b = 0; g = 127; r = 255;
    assert(32767==compt->getBasicColorKey(b, g, r));
    b = 0; g = 112; r = 245;
    assert(32767==compt->getBasicColorKey(b, g, r));
    b = 0; g = 142; r = 245;
    assert(32767==compt->getBasicColorKey(b, g, r));

    // Red: key: 255 Color [0, 0, 255]
    b = 0; g = 0; r = 255;
    assert(255==compt->getBasicColorKey(b, g, r));
    b = 0; g = 0; r = 235;
    assert(255==compt->getBasicColorKey(b, g, r));

    // Don't know color name
    b = 127; g = 127; r = 127;
    assert(8355711==compt->getBasicColorKey(b, g, r));
    b = 111; g = 127; r = 127;
    assert(imagecolorvalues::NOT_AVAILABLE==compt->getBasicColorKey(b, g, r));

    b = 0; g = 0; r = 100;
    assert(imagecolorvalues::NOT_AVAILABLE==compt->getBasicColorKey(b, g, r));

    // test isColor()
    imagereader* reader = new imagereader();
    string fname = "/home/linye020603/iap-web/cv-test/test-data/image/test-color-band-v.jpg";
    cout << "Use file: " << fname << endl;
    reader->read_image(false, fname);
    cv::Mat* mat = reader->getInputImage();
    
    assert(compt->isColor(imagecolorvalues::RED, mat->at<cv::Vec3b>(0, 170)));
    assert(compt->isColor(imagecolorvalues::ORANGE, mat->at<cv::Vec3b>(70, 170)));
    assert(compt->isColor(imagecolorvalues::ORANGE, mat->at<cv::Vec3b>(67, 170)));
    assert(compt->isColor(imagecolorvalues::ORANGE, mat->at<cv::Vec3b>(75, 170)));
    assert(compt->isColor(imagecolorvalues::ORANGE, mat->at<cv::Vec3b>(97, 170)));
    assert(compt->isColor(imagecolorvalues::ORANGE, mat->at<cv::Vec3b>(98, 170)));
    assert(compt->isColor(imagecolorvalues::YELLOW, mat->at<cv::Vec3b>(100, 170)));
    assert(compt->isColor(imagecolorvalues::YELLOW, mat->at<cv::Vec3b>(116, 170)));
    assert(compt->isColor(imagecolorvalues::YELLOW, mat->at<cv::Vec3b>(118, 170)));
    cv::Vec3b color;
    color[0] = 127; color[1] = 255; color[2] = 255; 
    assert(compt->isColor(imagecolorvalues::L75_YELLOW, color));

    assert(compt->isColor(imagecolorvalues::GREEN, mat->at<cv::Vec3b>(180, 170)));
    cout << mat->at<cv::Vec3b>(119, 170) << endl;
    assert(compt->isColor(imagecolorvalues::L50_GREEN, mat->at<cv::Vec3b>(119, 170)));
    assert(compt->isColor(imagecolorvalues::BLUE, mat->at<cv::Vec3b>(223, 170)));
    assert(compt->isColor(imagecolorvalues::BLUE, mat->at<cv::Vec3b>(207, 170)));
    assert(compt->isColor(imagecolorvalues::PURPLE, mat->at<cv::Vec3b>(265, 170)));
    assert(compt->isColor(imagecolorvalues::PURPLE, mat->at<cv::Vec3b>(250, 170)));
    assert(compt->isColor(imagecolorvalues::PURPLE, mat->at<cv::Vec3b>(253, 170)));
    assert(compt->isColor(imagecolorvalues::BLACK, mat->at<cv::Vec3b>(318, 170)));

    // test isSky()
    //sky_init_train* tr = new sky_init_train();
    

    delete compt;
    delete reader;
    //delete tr;
    
    cout << "Test pixel_comparator: Done." << endl;

    return 0;
}