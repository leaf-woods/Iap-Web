#include <string>
#include "region_evaluator.h"

using namespace std;

region_evaluator::region_evaluator() {}

region_evaluator::~region_evaluator() {
    this->comparator = nullptr;
}

void region_evaluator::evaluate(RegionDesc desc, cv::Vec3b color, bool_status& sta) {
    bool result;
    switch (desc) {
    case RegionDesc::sky:
        result = comparator->isSky(static_cast<int>(desc), color);
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    case RegionDesc::black:
        result = comparator->isColor(static_cast<int>(desc), color); 
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    break;
    }
    sta.setStatus(status::ERROR);
    sta.setResult(false); 
    sta.setMsg("Unsupported operation.");
}

void region_evaluator::setComparator(pixel_comparator* comparator) {
    this->comparator = comparator;
}