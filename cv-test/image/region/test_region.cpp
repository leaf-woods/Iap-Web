#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "eval_policy.h"
#include "iapcv_env.h"
#include "region_constants.h"
#include "regioncontext.h"
//#include "sky_init_train.h"


void testRegionDesc() {
    RegionDesc desc = RegionDesc::na;
    int n = static_cast<int>(desc);
    cout << "na: " << n << endl;
    desc = RegionDesc::sky;
    n = static_cast<int>(desc);
    cout << "sky: " << n << endl;
    desc = RegionDesc::cloud;
    n = static_cast<int>(desc);
    cout << "cloud: " << n << endl;
    desc = RegionDesc::weakCloud;
    n = static_cast<int>(desc);
    cout << "weakCloud: " << n << endl;
    desc = RegionDesc::black;
    n = static_cast<int>(desc);
    cout << "black: " << n << endl;
    desc = RegionDesc::purple;
    n = static_cast<int>(desc);
    cout << "purple: " << n << endl;
    desc = RegionDesc::blue;
    n = static_cast<int>(desc);
    cout << "blue: " << n << endl;
    desc = RegionDesc::yellow;
    n = static_cast<int>(desc);
    cout << "green: " << n << endl;
    desc = RegionDesc::orange;
    n = static_cast<int>(desc);
    cout << "yellow: " << n << endl;
    desc = RegionDesc::green;
    n = static_cast<int>(desc);
    cout << "orange: " << n << endl;
    desc = RegionDesc::red;
    n = static_cast<int>(desc);
    cout << "red: " << n << endl;
    cout << endl;    
}

using namespace std;

int main(int argc, char* argv[]) {

    iapcv_env* env = iapcv_env::getInstance();
    string basePath = env->getDevTestImgBase();
    string imgName = "test-color-band-v.jpg";

    cout << "Test region" << endl;

    regioncontext* region_ctx = new regioncontext();

    string fname = basePath + "/" + imgName;
    cout << "Use file: " << fname << endl;
    cv::Mat input = cv::imread(fname);
    
    //simple_explore* sexp = region_ctx->sexp;

    cout << "Test exploration" << endl;
    eval_policy* po = new eval_policy();
    po->setPolicy(RegionDesc::black, ColorType::BGR);
    region_ctx->builder->setEvalPolicy(po);
    
    region_ctx->builder->explore(input, 315, 0, region_constants::VERTICAL);
    region_ctx->builder->explore(input, 319, 0, region_constants::VERTICAL);
    region_ctx->builder->explore(input, 315, 349, region_constants::VERTICAL);
    region_ctx->builder->explore(input, 319, 349, region_constants::VERTICAL);

    region_ctx->builder->explore(input, 0, 0, region_constants::VERTICAL);
    region_ctx->builder->explore(input, 0, 350, region_constants::VERTICAL);

    cout << endl;
    po->setPolicy(RegionDesc::purple, ColorType::BGR);
    region_ctx->builder->setEvalPolicy(po);
    region_ctx->builder->explore(input, 0, 0, region_constants::VERTICAL); 

    cout << endl;
    region_ctx->builder->explore(input, 175, 250, region_constants::VERTICAL); 
    
    delete region_ctx;

    return 0; // executed after test_region life time ends

    /// TODO link to pixel_comparator static int array.
}