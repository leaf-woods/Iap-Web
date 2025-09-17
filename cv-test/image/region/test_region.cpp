#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "pixel_comparator.h"
#include "region_builder.h"
#include "region_evaluator.h"
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

    cout << "Test region" << endl;

    pixel_comparator* comp = new pixel_comparator();
    region_evaluator* evaluator = new region_evaluator();
    region_builder* builder = new region_builder();
    
    evaluator->setComparator(comp);
    builder->setRegionEvaluator(evaluator);

    string fname = "/home/linye020603/iap-web/cv-test/test-data/image/test-color-band-v.jpg";
    cout << "Use file: " << fname << endl;
    cv::Mat input = cv::imread(fname);
    
    cout << "Test exploration" << endl;
    builder->setRegionDesc(RegionDesc::black);
    builder->explore(input, 315, 0);
    builder->explore(input, 319, 0);
    builder->explore(input, 315, 349);
    builder->explore(input, 319, 349);

    builder->explore(input, 0, 0);
    builder->explore(input, 0, 350);

    cout << endl;
    builder->setRegionDesc(RegionDesc::purple);
    builder->explore(input, 0, 0); 

    cout << endl;
    builder->explore(input, 175, 250); 

    delete builder;
    delete evaluator;
    delete comp;

    return 0; // executed after test_region life time ends

    /// TODO link to pixel_comparator static int array.
}