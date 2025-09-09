#include <cassert>
#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "imagecolorvalues.h"
#include "imagereader.h"

using namespace std;

/*
 * We read an image into cv::Mat.
 * We convert the image to hsv color image.
 * We may mask hsv color image.
 * We may display all three images at runtime.
 * 
 * We need to provide the following states to be handled by other classes.
 * Read an image into cv::Mat input and convert it to a hsv image.
 * Read an image into cv::Mat input, convert it to a hsv image and set desc data.
 * Read an image into cv::Mat input, convert it to a hsv image and mask it using given bounds.
 *
 * We ensure each time we read an image into cv::Mat, we clear the desc before reading operation.
 * This is to handle the scenario that we read image into any of the above three states then we 
 * read image again and use desc data.
 * 
 */
imagereader::imagereader() {
    logger = new iapcv_log(typeid(this).name());
}

imagereader::~imagereader() {
    delete logger;
    logger = nullptr;
    printer = nullptr;
}

void imagereader::setLogLevel(int level) {
    logger->setLevel(level);
}

void imagereader::setPrint(iap_print* p) {
    this->printer = p;
}

/**
 * Given the coordinates (y, x), print the bgr, hsv and masked values on imput, hsvImage, hueMask.
 */
 void imagereader::printPixelColorValues(int x, int y) {
     cv::Vec<unsigned char, 3> entry = input.at<cv::Vec3b>(y, x);
     printer->printPixelColor(entry, imagecolorvalues::getColorTypeVal(imagecolorvalues::BGR));

     entry = hsvImage.at<cv::Vec3b>(y, x);
     printer->printPixelColor(entry, imagecolorvalues::getColorTypeVal(imagecolorvalues::HSV));

     entry = hueMask.at<cv::Vec3b>(y, x);
     printer->printPixelColor(entry, imagecolorvalues::getColorTypeVal(imagecolorvalues::MASKED));
     cout << endl;
 }

 void imagereader::printPixelColor(int x, int y, int type) {
    cv::Vec<unsigned char, 3> entry;
    if (type==imagecolorvalues::BGR) {
        entry = input.at<cv::Vec3b>(y, x);
        printer->printPixelColor(entry, imagecolorvalues::getColorTypeVal(imagecolorvalues::BGR));
    }
    else if (type==imagecolorvalues::HSV) {
        entry = hsvImage.at<cv::Vec3b>(y, x);
        printer->printPixelColor(entry, imagecolorvalues::getColorTypeVal(imagecolorvalues::HSV));
    }
    else if (type==imagecolorvalues::MASKED) {
        entry = hueMask.at<cv::Vec3b>(y, x);
         printer->printPixelColor(entry, imagecolorvalues::getColorTypeVal(imagecolorvalues::MASKED));
    }
 }

 /*
  * We read image to input and hsvImage without doing anything else.
  */
 bool imagereader::read_image(bool show, string path) {
     logger->info("Read image: ", path);

     /* @20250904 We don't try catch for imread as matrix is empty after a failed imread.
      * We throw an error otherwise cvtColor will throw exception if matrix is empty.
      *
      * However this is not feasible. See 20250904.html
      * So we use bool to indicate any failure in reading image operation.
      */
     input = cv::imread(path);
     if ( !(input.rows>0 && input.cols>0) ) {
         logger->error("Faild to read image: ", path);
         return false;
     }
     cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);

     if (show) {
        cv::imshow("input", input);
        cv::imshow("hsvImage", hsvImage);
        cv::waitKey(0);
     }
     return true; 
 }

 /*
  * blue_percent is calculated here.
  */
 void imagereader::read_and_mask_image(bool show, string path, size_t channel, uchar* lower, uchar* upper) {
    logger->info("Read and mask on image: ", path);
    logger->debug("Use range: ");
    if (logger->isDebug()) {
        printer->printPixelColor(channel, lower);
        printer->printPixelColor(channel, upper);
    }
    
    input = cv::imread(path);
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
    cv::inRange(hsvImage, cv::Scalar(lower[0], lower[1], lower[2]), cv::Scalar(upper[0],upper[1],upper[2]), hueMask);

    if (show) {
        cv::imshow("input", input);
        cv::imshow("hsvImage", hsvImage);
        cv::imshow("hueMask", hueMask);
        cv::waitKey(0);
    }  
 }

 cv::Mat* imagereader::getHueMask() {
    return &hueMask;
 }

 cv::Mat* imagereader::getHsvImage() {
    return &hsvImage;
 }

 cv::Mat* imagereader::getInputImage() {
    return &input;
 }

 double imagereader::getNonZeroPercent() {
    double imageSize = hsvImage.cols * hsvImage.rows;
    double percent = 100*((double) cv::countNonZero(hueMask))/imageSize;
    return percent;
 }