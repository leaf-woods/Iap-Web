#include <iostream>
#include <vector>

#include <opencv2/core.hpp>

#include "get_stddev.h"
#include "eval_policy.h"
#include "iapcv_env.h"
#include "regioncontext.h"
#include "region_constants.h"
#include "fact_sky_init_train.h"
#include "sky_init_train.h"

using namespace std;
int main(int argc, char* argv[]) {
    fact_sky_init_train* ftrain = new fact_sky_init_train();
    sky_init_train* tr = ftrain->getSkyTrainInstance();
    
    cv::Mat* trainM = tr->getMatrixTrain();
    cv::Mat* hsvImage = tr->getHsvImage();
    cv::Mat* input = tr->getInputImage();

    eval_policy* po = new eval_policy();
    po->setPolicy(RegionDesc::sky, ColorType::TRAINED);

    regioncontext* region_ctx = new regioncontext();

    region_ctx->builder->setLogLevel(iapcv_log::DEBUG);
    region_ctx->builder->setEvalPolicy(po);
    region_ctx->builder->explore(*trainM, 0, 0, region_constants::VERTICAL);

    vector<int*>* colorIndices = new vector<int*>();
    region_ctx->builder->getRegionColorsIndices(*hsvImage, colorIndices, 2);
    cv::Vec3d stddev = region_ctx->stddev->calc_stddev(*colorIndices, *hsvImage);
    
    delete ftrain;
    delete region_ctx;
    /// TODO
    delete colorIndices;
    delete po;
    return 0;
}