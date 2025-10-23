#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "eval_params.h"
#include "eval_policy.h"
#include "fact_sky_init_train.h"
#include "pixel_comparator.h"
#include "region_evaluator.h"
#include "status.h"

using namespace std;
int main(int argc, char* argv[]) {
    fact_sky_init_train* ftrain = new fact_sky_init_train();
    sky_init_train* tr = ftrain->getSkyTrainInstance();
    cv::Mat* trainM = tr->getMatrixTrain();
    cv::Mat* hsvImage = tr->getHsvImage();
    cv::Mat* input = tr->getInputImage();
    
    pixel_comparator* compt = new pixel_comparator();
    iap_print* printer = new iap_print();
    region_evaluator* eval = new region_evaluator();

    eval->setComparator(compt);
    eval->setPrint(printer);

    // Test evaluate()
    eval_policy* po = new eval_policy();
    po->setPolicy(RegionDesc::sky, ColorType::TRAINED);
    eval_params* pm = new eval_params();
    pm->setParam(ParamName::color2, trainM->at<cv::Vec3b>(0, 0));
    bool_status* st = new bool_status(status::NORMAL, false);
    eval->evaluate(*po, *pm, *st);
    assert(st->getResult());
    printer->printPixelColor(trainM->at<cv::Vec3b>(0, 0), "TRAINED");
    cout << endl;

    po->setPolicy(Policies::color_value_00);
    po->setColorType(ColorType::HSV);
    pm->clearParams();
    pm->setParam(ParamName::color2, hsvImage->at<cv::Vec3b>(0, 0));
    pm->setParam(ParamName::startDesc, RegionDesc::sky);
    //pm->setParam(ParamName::startPixelColor, hsvImage->at<cv::Vec3b>(0, 0));
    //pm->setParam(ParamName::color1, trainM->at<cv::Vec3b>(0, 0));
    st->clear();
    eval->evaluate(*po, *pm, *st);
    assert(st->getResult());
    printer->printPixelColor(hsvImage->at<cv::Vec3b>(0, 0), "HSV");
    cout << endl;

    delete po;
    delete pm;
    delete st;
    delete compt;
    delete printer;
    delete ftrain;

    return 0;
}