#include <cassert>
#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "imagecolormatrices.h"

using namespace std;

imagecolormatrices::imagecolormatrices() {}

imagecolormatrices::~imagecolormatrices() {
    printer = nullptr;
}

void imagecolormatrices::setImagePath(std::string path) {
    this->fname = path;    
}

void imagecolormatrices::setPrint(iap_print* p) {
    this->printer = p;
}

void imagecolormatrices::read_to_hsv() {
    cout << "Color matrices use image: " << fname << endl;
    input = cv::imread(fname);
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
}

void imagecolormatrices::in_range_mask(uchar* lower, uchar* upper) {
    cv::inRange(hsvImage, cv::Scalar(lower[0], lower[1], lower[2]), cv::Scalar(upper[0],upper[1],upper[2]), hueMask);
}

double imagecolormatrices::get_percentage() {
    double imageSize = hsvImage.cols * hsvImage.rows;
    double bluePercentage = 100*(((double) cv::countNonZero(hueMask))/imageSize);
    cout << "Percenage of blue: " << bluePercentage << "%" << endl;
    return bluePercentage;
}

/**
 * Given the coordinates (y, x), print the bgr, hsv and masked values on imput, hsvImage, hueMask.
 */
 void imagecolormatrices::printPixelColorValues(int x, int y) {
     cv::Vec<unsigned char, 3> entry = input.at<cv::Vec3b>(y, x);
     printer->printPixelColor(entry, "BGR");

     entry = hsvImage.at<cv::Vec3b>(y, x);
     printer->printPixelColor(entry, "HSV");

     entry = hueMask.at<cv::Vec3b>(y, x);
     printer->printPixelColor(entry, "Masked");
     cout << endl;
 }

 void imagecolormatrices::printPixelColor(int x, int y, string type) {
    cv::Vec<unsigned char, 3> entry;
    if (type=="BGR") {
        entry = input.at<cv::Vec3b>(y, x);
        printer->printPixelColor(entry, "BGR");
    }
    else if (type=="HSV") {
        entry = hsvImage.at<cv::Vec3b>(y, x);
        printer->printPixelColor(entry, "HSV");
    }
    else if (type=="Masked") {
        entry = hueMask.at<cv::Vec3b>(y, x);
         printer->printPixelColor(entry, "Masked");
    }
 }