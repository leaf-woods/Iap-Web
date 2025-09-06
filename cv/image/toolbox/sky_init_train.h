#ifndef SKY_INIT_TRAIN_H
#define SKY_INIT_TRAIN_H

#include <bitset>
#include <cassert>
#include <iostream>
#include <opencv2/core.hpp>

#include "iap_print.h"

using namespace std;

class sky_init_train {
    private:
       static const int OF_SKY=0;
       static const int OF_CLD=1;
       static const int OF_WCL=2;

       string fname = "/home/linye020603/iap-web/cv/test/image/data/img64/IMG_4585_S_CR_R1_S64_00.JPG";
       cv::Mat input;
       cv::Mat hsvImage;
       cv::Mat mat;

       iap_print* printer;

    private:
        void init(cv::Mat& mat);
        void setupCloud(cv::Mat& mat, int row, int col_start, int col_end);
        void setupWeakCloud(cv::Mat& mat, int row, int col_start, int col_end);
        void setupSky(cv::Mat& mat, int row, int col_start, int col_end);
        void setup();
        int getInt(uchar b, uchar g, uchar r);

    public:
        sky_init_train();
        ~sky_init_train();
        void test_dist();
};
#endif