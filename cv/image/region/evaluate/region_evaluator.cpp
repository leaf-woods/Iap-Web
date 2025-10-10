#include <cassert>
#include <string>

#include "region_desc.h"
#include "region_evaluator.h"

using namespace std;

region_evaluator::region_evaluator() {}

region_evaluator::~region_evaluator() {
    this->comparator = nullptr;
}

/// TODO Test 
void region_evaluator::evaluate(eval_policy& po, eval_params& pm, bool_status& sta) {
    if (po.getPolicy() == Policies::r_desc) {
        assert(po.getRegionDesc() != RegionDesc::na);
        evaluateDesc(po.getRegionDesc(), pm.getParam2(), sta);
    }
    else if (po.getPolicy() == Policies::similar_base_00) {
        bool result = comparator->similar_base_00(pm.getParam1(), pm.getParam2());
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    }
}

void region_evaluator::evaluateDesc(RegionDesc desc, cv::Vec3b color, bool_status& sta) {
    bool result;
    RegionDesc c;
    switch (desc) {
    case RegionDesc::sky:
        result = comparator->isSky(static_cast<int>(desc), color);
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    case RegionDesc::cloud:
        c = comparator->contents_sky_cloud(color);
        result = c==RegionDesc::cloud;
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    case RegionDesc::black:
        result = comparator->isColor(static_cast<int>(desc), color); 
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    default:
        break;
    }
    sta.setStatus(status::ERROR);
    sta.setResult(false); 
    sta.setMsg("Unsupported operation.");
}

void region_evaluator::evaluateInBound(eval_policy& po, cv::Vec3b color, bool_status& sta) {
    if (po.getPolicy() == Policies::r_desc) {
        evaluateDesc(po.getRegionDesc(), color, sta);
        return;
    }
    sta.setStatus(status::ERROR);
    sta.setResult(false); 
    sta.setMsg("Unsupported operation.");
}

void region_evaluator::setComparator(pixel_comparator* comparator) {
    this->comparator = comparator;
}