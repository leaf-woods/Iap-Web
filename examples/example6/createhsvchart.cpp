#include <iostream>

#include "createhsvchart.h"

using namespace std;

createhsvchart::~createhsvchart() {
    convert = nullptr;
    input.release();
}

void createhsvchart::createChart(double h) {
    this->H = h;
    
    uchar* bgr = new uchar[3]{0};
    input = cv::imread("IMG_4624_S_CHT.JPG");
    
    for(int r=0; r<input.rows; r=r+4) {
      for(int c=0; c<input.cols; c=c+4) {
        
        // S increases from 0 to 100 as loop going on c.
        convert->toBgr(bgr, 217, c/4, 100-r/4);
        cv::Vec3b & color = input.at<cv::Vec3b>(c, r);

        color[0] = bgr[0];
        color[1] = bgr[1];
        color[2] = bgr[2];
        
        for (int k=0; k<4; k++) {
            for (int m=0; m<4; m++) {
                input.at<cv::Vec3b>(cv::Point(c+k, r+m)) = color;
            }
        }
    }
  }
  cv::imshow("input", input);
  cv::waitKey(0);
  //cv::imwrite("HUE217.JPG", input);
  delete bgr;
}

void createhsvchart::setConvertHSV(convert_bgrhsv* convert) {
    this->convert = convert;
}