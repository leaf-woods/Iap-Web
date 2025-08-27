#ifndef IMAGECOLORMATRICES_H
#define IMAGECOLORMATRICES_H

#include <opencv2/core.hpp>

#include "iap_print.h"

class imagecolormatrices {
    private:
      iap_print* printer;
    public:
      std::string fname;
      cv::Mat input;
      cv::Mat hsvImage;
      cv::Mat hueMask;

    public:
      imagecolormatrices();
      ~imagecolormatrices();
      void setImagePath(std::string path);
      void setPrint(iap_print* p);
      void printPixelColorValues(int x, int y);
      void printPixelColor(int x, int y, std::string type);
      void read_to_hsv();
      void in_range_mask(uchar* lower, uchar* upper);
      double get_percentage();
};
#endif