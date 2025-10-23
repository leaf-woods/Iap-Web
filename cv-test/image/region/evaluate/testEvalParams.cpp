#include <any>
#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "eval_params.h"
#include "fact_sky_init_train.h"
#include "sky_init_train.h"

using namespace std;
int main(int argc, char* argv[]) {
    fact_sky_init_train* ftrain = new fact_sky_init_train();
    sky_init_train* tr = ftrain->getSkyTrainInstance();
    
    cv::Mat* trainM = tr->getMatrixTrain();
    cv::Mat* hsvImage = tr->getHsvImage();
    cv::Mat* input = tr->getInputImage();

    eval_params* params = new eval_params();
    assert(params->size()==0);

    cv::Vec<unsigned char, 3> color = hsvImage->at<cv::Vec3b>(0,0);
    params->setParam(ParamName::color1, color);
    assert(params->size()==1);
    std::any c1 = params->getParam(ParamName::color1);
    cv::Vec<unsigned char, 3> color1 = std::any_cast<cv::Vec<unsigned char, 3>>(c1);
    cout << "color1: [" << static_cast<int>(color1[0]) << " , " << static_cast<int>(color1[1]) << " , " << static_cast<int>(color1[2]) << " ]" << endl;
    /*
     * Add color twice, then unordered_map makes a different pair which is another copy of color object.
     */ 
    params->setParam(ParamName::startPixelColor, color);
    assert(params->size()==2);
    std::any sc = params->getParam(ParamName::startPixelColor);
    cv::Vec<unsigned char, 3> startColor = std::any_cast<cv::Vec<unsigned char, 3>>(sc);
    assert(startColor[0]==color1[0] && startColor[1]==color1[1] && startColor[2]==color1[2]);
    
    cout << "c1: " << &c1 << " sc: " << &sc << endl;
    cout << endl;

    cout << "color addr: " << &color << endl;
    cout << "color1 addr: " << &color1 << " startColor addr: " << &startColor << endl;
    cout << "color1: " << color1 << " startColor: " << startColor << endl;
    assert(color1 == startColor);
    cout << endl;

    params->clearParams();
    assert(params->size()==0);

    // Test no key found
    params->setParam(ParamName::color1, color);
    assert(params->size()==1);
    params->setParam(ParamName::startDesc, RegionDesc::sky);
    assert(params->size()==2);

    any c5 = params->getParam(ParamName::color2);
    assert(!c5.has_value());

    any rd = params->getParam(ParamName::startDesc);
    assert(RegionDesc::sky == any_cast<RegionDesc>(rd));
    cout << endl;

    // Test insert same key twice
    cv::Vec<unsigned char, 3> color_b = hsvImage->at<cv::Vec3b>(12,0);
    params->setParam(ParamName::color1, color_b);
    any cb = params->getParam(ParamName::color1);
    assert(cb.has_value());
    cout << "color: " << any_cast<cv::Vec3b>(cb) << endl;
    cout << endl;

    delete ftrain;
    delete params;

    return 0;
}