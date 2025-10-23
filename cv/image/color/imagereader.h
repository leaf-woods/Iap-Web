#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <opencv2/core.hpp>

#include "iapcv_log.h"
#include "iap_print.h"
#include "imagecolorvalues.h"

/*
 * @20250830
 * We allow test code during an image read and write process.
 */
class imagereader {
    private:
      iapcv_log* logger;

      cv::Mat input;
      cv::Mat hsvImage;
      cv::Mat hueMask;

      iap_print* printer;
      
    public:
      imagereader();
      ~imagereader(); 
      
      void setLogger(iapcv_log* logger);
      void setLogLevel(int level);
      cv::Mat* getInputImage();
      cv::Mat* getHsvImage();
      cv::Mat* getHueMask();
      double getNonZeroPercent();
      void printPixelColorValues(int x, int y);
      void printPixelColor(int x, int y, ColorType type);
      bool read_image(bool show, std::string path);
      void read_and_mask_image(bool show, std::string path, size_t channel, uchar* lower, uchar* upper);
      void setPrint(iap_print* p);
};
#endif