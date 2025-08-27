#ifndef TEST_IMG_DATA_H
#define TEST_IMG_DATA_H

#include <opencv2/core.hpp>

#include "iap_context.h"

class test_img_data {
    private:
      std::string img_base;
      cv::Mat input;
      cv::Mat hsvImage;
      cv::Mat hueMask;

      iap_context* ctx;

    private:
      void set(std::string fn);
      double test_blue(std::string f);
      void test_range(int x, int y);
      void test_types();

    public:
      test_img_data();
      ~test_img_data();
      void setImageBase(std::string path);
      void test_img_data_blue();
};
#endif