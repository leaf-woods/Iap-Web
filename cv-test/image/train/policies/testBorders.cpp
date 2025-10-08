#include <iostream>

#include <opencv2/core.hpp>

#include "iapcv_env.h"
#include "regioncontext.h"
#include "sky_init_train.h"

using namespace std;

int main() {
    iapcv_env* env = iapcv_env::getInstance();

    string basePath = env->getDevTestImgBase();
    basePath.append("/img64");
    
    string imgName = "IMG_4585_S_CR_R1_S64_00.JPG";

    sky_init_train* tr = new sky_init_train(basePath, imgName);
    
    cv::Mat* trainM = tr->getMatrixTrain();

    regioncontext* region_ctx = new regioncontext();

    region_ctx->builder->setLogLevel(iapcv_log::INFO);
    region_ctx->builder->setRegionDesc(RegionDesc::sky);
    region_ctx->builder->explore(*trainM, 0, 0); 
    region_ctx->builder->computeBorders(*tr->getHsvImage()); 
    
    int next[2] = {0};
    if (region_ctx->builder->getNextStartPoint(2, next)) {
        //cout << "found next." << endl;
        region_ctx->builder->explore(*trainM, next[0], next[1]);
    }

    delete tr;

    delete region_ctx;

    return 0;
}