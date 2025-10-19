#include <iostream>

#include <opencv2/core.hpp>

#include "eval_policy.h"
#include "iapcv_env.h"
#include "regioncontext.h"
#include "region_constants.h"
#include "fact_sky_init_train.h"
#include "sky_init_train.h"

using namespace std;

void getHSVStdDev(const regioncontext& ctx, const cv::Mat& hsv) {
    vector<int*>* colorIndices = new vector<int*>();
    ctx.builder->getRegionColorsIndices(hsv, colorIndices, 2);
    cv::Vec3d stddev = ctx.stddev->calc_stddev(*colorIndices, hsv);
    delete colorIndices;
}

int main() {
    fact_sky_init_train* ftrain = new fact_sky_init_train();
    sky_init_train* tr = ftrain->getSkyTrainInstance();
    
    cv::Mat* trainM = tr->getMatrixTrain();
    cv::Mat* hsvImage = tr->getHsvImage();
    cv::Mat* input = tr->getInputImage();

    eval_policy* po = new eval_policy();
    po->setPolicy(RegionDesc::sky, ColorType::TRAINED);

    regioncontext* region_ctx = new regioncontext();

    region_ctx->builder->setLogLevel(iapcv_log::DEBUG);
    
    /// TODO: start (0, 0) generates different region compared with start (4, 2)
    /// Two pixels are both on region
    /// Reason: we use different start points and comparison is based on start point.
    region_ctx->builder->setEvalPolicy(po);
    //region_ctx->builder->getEvalPolicy()->setPolicy(Policies::similar_base_00);
    //region_ctx->builder->getEvalPolicy()->setPolicy(Policies::color_value_00);
    //region_ctx->builder->explore(*hsvImage, 0, 0, region_constants::VERTICAL); 

    region_ctx->builder->explore(*trainM, 0, 0, region_constants::VERTICAL);
    //region_ctx->builder->computeBorders(*hsvImage); 

    getHSVStdDev(*region_ctx, *hsvImage);

    /*
    cout << endl;
    cout << "row 0: "  << hsvImage->row(0) << endl;
    cout << endl;
    cout << "row 1: "  << hsvImage->row(1) << endl;
    cout << endl;
    cout << "row 2: "  << hsvImage->row(2) << endl;
    cout << endl;
    */
    //region_ctx->builder->printMapOnMatrix(*hsvImage);

    int next[2] = {0};
    if (region_ctx->builder->getNextStartPoint(2, next)) {
        //cout << "found next." << endl;
        //region_ctx->builder->explore(*trainM, next[0], next[1]);
    }

    delete ftrain;

    delete region_ctx;
    delete po;

    return 0;
}