#include <iostream>

#include <opencv2/core.hpp>

#include "iapcv_env.h"
#include "regioncontext.h"
#include "sky_init_train.h"

using namespace std;

int main(int argc, char* argv[]) {

    iapcv_env* env = iapcv_env::getInstance();

    string basePath = env->getDevTestImgBase();
    basePath.append("/img64");
    
    string imgName = "IMG_4585_S_CR_R1_S64_00.JPG";

    sky_init_train* tr = new sky_init_train(basePath, imgName);
    
    cv::Mat* trainM = tr->getMatrixTrain();
    cv::Vec3b & color = trainM->at<cv::Vec3b>(0, 1);
    color[0] = 0;
    color[1] = 1;
    color[2] = 0;
    trainM->at<cv::Vec3b>(cv::Point(0, 1)) = color;
    color = trainM->at<cv::Vec3b>(1, 0);
    color[0] = 0;
    color[1] = 1;
    color[2] = 0;
    trainM->at<cv::Vec3b>(cv::Point(1, 0)) = color;

    regioncontext* region_ctx = new regioncontext();

    region_ctx->builder->setRegionDesc(RegionDesc::sky);
    region_ctx->builder->explore(*trainM, 0, 0); 

    // Restore two pixels' color
    color = trainM->at<cv::Vec3b>(0, 1);
    color[0] = 1;
    color[1] = 0;
    color[2] = 0;
    trainM->at<cv::Vec3b>(cv::Point(0, 1)) = color;
    color = trainM->at<cv::Vec3b>(1, 0);
    color[0] = 1;
    color[1] = 0;
    color[2] = 0;
    trainM->at<cv::Vec3b>(cv::Point(1, 0)) = color;

    cout << "Test explore diagonal" << endl;
    region_ctx->builder->setRegionDesc(RegionDesc::sky);
    region_ctx->builder->explore(*trainM, 0, 0); 
    cout << "Test explore diagonal: Done" << endl;
    cout << endl;

    delete tr;

    delete region_ctx;

    return 0;
}