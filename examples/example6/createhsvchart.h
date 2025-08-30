#ifndef CREATEHSVCHART_H
#define CREATEHSVCHART_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "convert_bgrhsv.h"

class createhsvchart {
  private: 
    double H;
    std::string fname;

    convert_bgrhsv* convert;
  
  private:
    std::string createFileName(std::string prefix);

  public:
    ~createhsvchart();
    void createChart(double h);
    void createChart(uchar b, uchar g, uchar r);
    void setConvertHSV(convert_bgrhsv* convert);
    void setFileName(std::string fname);
};
#endif