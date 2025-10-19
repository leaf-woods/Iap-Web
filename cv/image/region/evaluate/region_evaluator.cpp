#include <any>
#include <cassert>

#include <opencv2/imgproc.hpp>

#include "region_desc.h"
#include "region_evaluator.h"

using namespace std;

region_evaluator::region_evaluator() {}

region_evaluator::~region_evaluator() {
    this->comparator = nullptr;
    this->printer = nullptr;
}

/// TODO Test 
void region_evaluator::evaluate(eval_policy& po, eval_params& pm, bool_status& sta) {
    if (po.getPolicy() == Policies::r_desc) {
        assert(po.getRegionDesc() != RegionDesc::na);
        any c2 = pm.getParam(ParamName::color2);
        
        if (c2.has_value()) {  
            evaluate(po.getRegionDesc(), any_cast<cv::Vec3b>(c2), sta);
        }
        else {
            setError(sta, "Bad parameter."); 
        }
        return;
    }

    if (po.getPolicy() == Policies::similar_base_00) {
        evaluateSimilarBase_00(pm, sta);
        return;
    }

    if (po.getPolicy() == Policies::color_value_00) {
        evaluateColorValue_00(pm, sta);
    }
}

void region_evaluator::setError(bool_status& sta, string msg) {
    sta.setStatus(status::ERROR);
    sta.setResult(false);
    sta.setMsg(msg);
}

void region_evaluator::evaluateColorValue_00(eval_params& pm, bool_status& sta) {
    RegionDesc d = RegionDesc::na;
    any c2 = pm.getParam(ParamName::color2);
        
    if (c2.has_value()) {
        d = comparator->compareValue_00(any_cast<cv::Vec3b>(c2));
        if (d==any_cast<RegionDesc>(pm.getParam(ParamName::startDesc))) {
            sta.setStatus(status::NORMAL);
            sta.setResult(true);
            return;
        }
    }
    else {
        setError(sta, "Bad parameter.");
        return;
    }
            
    if (d == RegionDesc::na) {
        any sc = pm.getParam(ParamName::startPixelColor);
        if (sc.has_value()) {
            bool result = comparator->compareStart(any_cast<cv::Vec3b>(sc), any_cast<cv::Vec3b>(c2));
            if (result) {
                sta.setStatus(status::NORMAL);
                sta.setResult(true);
                return;
            }
            any c1 = pm.getParam(ParamName::color1);
            if (c1.has_value()) {
                result = comparator->compareNeighbor(any_cast<cv::Vec3b>(c1), any_cast<cv::Vec3b>(c2));
                sta.setStatus(status::NORMAL);
                sta.setResult(result);
                return;
            }
            else {
                setError(sta, "Bad parameter.");
                return;
            } 
        }
        else {
            setError(sta, "Bad parameter.");
            return;
        }
    }
    sta.setStatus(status::NORMAL);
    sta.setResult(false);
    return;
}

void region_evaluator::evaluateSimilarBase_00(eval_params& pm, bool_status& sta) {
    any c1 = pm.getParam(ParamName::color1);
    any c2 = pm.getParam(ParamName::color2);
        
    if (c1.has_value() && c2.has_value()) {
        bool result = comparator->compareNeighbor(any_cast<cv::Vec3b>(c1), any_cast<cv::Vec3b>(c2));
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
    }
    else {
        setError(sta, "Bad parameters."); 
    }
}

void region_evaluator::evaluate(RegionDesc desc, cv::Vec3b color, bool_status& sta) {
    bool result;
    RegionDesc c;
    switch (desc) {
    case RegionDesc::sky:
        result = comparator->isSky_ma(static_cast<int>(desc), color);
        sta.setStatus(status::NORMAL);
        sta.setResult(result); 
        return;
    case RegionDesc::cloud:
        c = comparator->contents_sky_cloud_ma(color);
        result = c==RegionDesc::cloud;
        sta.setStatus(status::NORMAL);
        sta.setResult(result);
        return;
    case RegionDesc::black: /// TODO color type
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

bool region_evaluator::equals(cv::Vec3b color1, cv::Vec3b color2) {
    return comparator->equals(color1, color2);
}

RegionDesc region_evaluator::evaluatePixelColor(eval_policy& po, cv::Vec3b color) {
    if (po.getPolicy() != Policies::r_desc) {
        return RegionDesc::na;
    }
    
    RegionDesc desc = po.getRegionDesc();
    // @20251017 Currently only RegionDesc::sky, RegionDesc::cloud, RegionDesc::weakCloud available to train matrix. 
    if (po.getColorType() == ColorType::TRAINED) {
        assert(desc == RegionDesc::sky || desc == RegionDesc::cloud || desc == RegionDesc::weakCloud);
        return comparator->contents_sky_cloud_ma(color);
    }

    if (po.getColorType() == ColorType::BGR) {
        return region_desc::getRegionDesc(comparator->getColor(color));
    }

    if (po.getColorType() == ColorType::HSV) {
        if (desc == RegionDesc::sky || desc == RegionDesc::cloud || desc == RegionDesc::weakCloud) {
            // @20251017 The only way we know the color is RegionDesc::sky or not.
            return comparator->compareValue_00(color);
        }
        
        cv::Vec3b bgr;
        cv::cvtColor(bgr, color, cv::COLOR_HSV2BGR);
        printer->printPixelColor(bgr, "BGR");
        int c = comparator->getColor(bgr);
        return region_desc::getRegionDesc(c);
    }
    return RegionDesc::na;
}

void region_evaluator::setComparator(pixel_comparator* comparator) {
    this->comparator = comparator;
}

void region_evaluator::setPrint(iap_print* p) {
    this->printer = p;
}