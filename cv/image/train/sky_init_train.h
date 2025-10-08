#ifndef SKY_INIT_TRAIN_H
#define SKY_INIT_TRAIN_H

#include <bitset>
#include <cassert>
#include <iostream>
#include <opencv2/core.hpp>

#include "iap_print.h"

/*
 * @20250923
 * This class is specific to cv-test/test-data/img64/*.JPG
 */
class sky_init_train {
    private:
       static const int OF_SKY=0;
       static const int OF_CLD=1;
       static const int OF_WCL=2;

       std::string basePath;
       std::string imageName;

       cv::Mat input;
       cv::Mat hsvImage;
       cv::Mat train;

       iap_print* printer;

    private:
        void init(cv::Mat& mat);
        void setupCloud(cv::Mat& mat, int row, int col_start, int col_end);
        void setupWeakCloud(cv::Mat& mat, int row, int col_start, int col_end);
        void setup();
        int getInt(uchar b, uchar g, uchar r);
        void verifyTrainMax(const cv::Mat& mat);

    public:
        sky_init_train(std::string basePath, std::string imageName);
        ~sky_init_train();

        std::string getBasePath();
        std::string getImageName();
        cv::Mat* getMatrixTrain();
        cv::Mat* getInputImage();
        cv::Mat* getHsvImage();

        void printTrainR();
        void test_dist();
};
#endif