#ifndef CREATEHSVCHART_H
#define CREATEHSVCHART_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "convert_bgrhsv.h"

class createhsvchart {
  private:
    cv::Mat input;  
    double H;

    convert_bgrhsv* convert;

  public:
    ~createhsvchart();
    void createChart(double h);
    void setConvertHSV(convert_bgrhsv* convert);
};
#endif
