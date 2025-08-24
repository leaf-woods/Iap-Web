#ifndef TEST_IMG_DATA_H
#define TEST_IMG_DATA_H

#include <opencv2/core.hpp>

class test_img_data {
    private:
      std::string img_base;
      std::string fname;
      cv::Mat input;
      cv::Mat hsvImage;
      cv::Mat hueMask;

    private:
      void set(std::string fn);
    public:
      test_img_data();
      void test_img_data_blue();
      void test_img_data_range();
      void test_img_data_types();
};
#endif