#include <cassert>
#include <iostream>

#include "eval_policy.h"

using namespace std;
int main(int argc, char* argv[]) {
    eval_policy* po = new eval_policy();

    //po->clear();
    assert(po->getPolicy() == Policies::na);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);

    po->setPolicy(Policies::na);
    assert(po->getPolicy() == Policies::na);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);

    po->setPolicy(Policies::color_value_00);
    assert(po->getPolicy() == Policies::color_value_00);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);

    po->setPolicy(Policies::similar_base_00);
    assert(po->getPolicy() == Policies::similar_base_00);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);

    po->setPolicy(Policies::r_desc);
    assert(po->getPolicy() == Policies::r_desc);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);

    po->setRegionDesc(RegionDesc::sky);
    po->setColorType(ColorType::TRAINED);
    assert(po->getPolicy() == Policies::r_desc);
    assert(po->getRegionDesc() == RegionDesc::sky);
    assert(po->getColorType() == ColorType::TRAINED);

    po->setPolicy(RegionDesc::black, ColorType::BGR);
    assert(po->getPolicy() == Policies::r_desc);
    assert(po->getRegionDesc() == RegionDesc::black);
    assert(po->getColorType() == ColorType::BGR);

    po->setPolicy(RegionDesc::sky, ColorType::HSV);
    assert(po->getPolicy() == Policies::r_desc);
    assert(po->getRegionDesc() == RegionDesc::sky);
    assert(po->getColorType() == ColorType::HSV);
    cout << "Policy: " << po->getPolicyVal() << endl;

    po->setPolicy(Policies::color_value_00);
    assert(po->getPolicy() == Policies::color_value_00);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);
    cout << "Policy: " << po->getPolicyVal() << endl;

    po->setPolicy(Policies::similar_base_00);
    assert(po->getPolicy() == Policies::similar_base_00);
    assert(po->getRegionDesc() == RegionDesc::na);
    assert(po->getColorType() == ColorType::NA);

    delete po;
    return 0;
}