#include <iostream>

#include <opencv2/core.hpp>

#include "iapcv_env.h"
#include "regioncontext.h"
#include "sky_init_train.h"

int main(int argc, char* argv[]) {
    iapcv_env* env = iapcv_env::getInstance();

    string basePath = env->getDevTestImgBase();
    basePath.append("/img64");
    
    string imgName = "IMG_4585_S_CR_R1_S64_00.JPG";

    sky_init_train* tr = new sky_init_train(basePath, imgName);
    
    cv::Mat* trainM = tr->getMatrixTrain();

    regioncontext* region_ctx = new regioncontext();

    region_ctx->builder->setLogLevel(iapcv_log::INFO);
    region_ctx->builder->getEvalPolicy()->setPolicy(RegionDesc::cloud);
    region_ctx->builder->explore(*trainM, 20, 1); 
    region_ctx->builder->computeBorders(*tr->getHsvImage()); 

    // We see small H delta ( at most 1) for both cloud and sky regions.
    // We use _11.JPG
    // Policy: explore(0, 0). If delta H = 1, delta S >= 5, we consider it is different region.
    

    delete tr;
    delete region_ctx;

    return 0;
}