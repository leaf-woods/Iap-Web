#include <iostream>

#include <opencv2/core.hpp>

#include "eval_policy.h"
#include "iapcv_env.h"
#include "regioncontext.h"
#include "region_constants.h"
#include "fact_sky_init_train.h"
#include "sky_init_train.h"

void getHSVStdDev(const regioncontext& ctx, const cv::Mat& hsv) {
    vector<int*>* colorIndices = new vector<int*>();
    ctx.builder->getRegionColorsIndices(hsv, colorIndices, 2);
    cv::Vec3d stddev = ctx.stddev->calc_stddev(*colorIndices, hsv);
    delete colorIndices;
}

int main(int argc, char* argv[]) {
    fact_sky_init_train* ftrain = new fact_sky_init_train();
    sky_init_train* tr = ftrain->getSkyTrainInstance();
    
    cv::Mat* trainM = tr->getMatrixTrain();
    cv::Mat* hsvImage = tr->getHsvImage();
    cv::Mat* input = tr->getInputImage();

    eval_policy* po = new eval_policy();
    po->setPolicy(RegionDesc::cloud, ColorType::TRAINED);

    regioncontext* region_ctx = new regioncontext();

    region_ctx->builder->setLogLevel(iapcv_log::DEBUG);

    region_ctx->builder->setEvalPolicy(po);
    region_ctx->builder->explore(*trainM, 14, 1, region_constants::VERTICAL); 
    //region_ctx->builder->computeBorders(*tr->getHsvImage()); 

    cout << endl;
    //region_ctx->builder->printMapOnMatrix(*tr->getHsvImage());

    getHSVStdDev(*region_ctx, *hsvImage);

    // We see small H delta ( at most 1) for both cloud and sky regions.
    // We use _11.JPG
    // Policy: explore(0, 0). If delta H = 1, delta S >= 5, we consider it is different region.
    
    // https://www.scribbr.com/statistics/anova-in-r/
    // https://cran.rstudio.com/
    delete ftrain;
    delete region_ctx;
    delete po;

    return 0;
}