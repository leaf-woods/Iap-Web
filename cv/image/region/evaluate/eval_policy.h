#ifndef EVAL_POLICIES_H
#define EVAL_POLICIES_H

#include "imagecolorvalues.h"
#include "region_desc.h"

enum class Policies {
    na,
    r_desc,
    color_value_00,
    similar_base_00
};

class eval_policy_property {
    private:
        RegionDesc desc;
        ColorType color_type;

    public:
        void setRegionDesc(RegionDesc d){
            this->desc = d;
        }

        void setColorType(ColorType type) {
            this->color_type = type;
        }

        RegionDesc getRegionDesc() {
            return desc;
        }

        ColorType getColorType() {
            return color_type;
        }
};

/**
 * @20251017
 * An evaluation policy has: a Policies enum, a property Regiondesc, a property useTrain
 */
class eval_policy {
    private:
        Policies po = Policies::na;
        eval_policy_property* prop;

    private:
        void clear() {
            po = Policies::na;
            prop->setRegionDesc(RegionDesc::na);
            prop->setColorType(ColorType::NA);
        }

    public:
        eval_policy() {
            prop = new eval_policy_property();
        }

        ~eval_policy() {
            delete prop;
        }

        /// TODO test: If it is a policy applicable to train Matrix, user has to manually set it up.
        /// Currently, we don't know how to solve the policies problem. 
        void setPolicy(Policies po) {
            this->po = po;
        }

        void setPolicy(RegionDesc desc, ColorType type) {
            this->po = Policies::r_desc;
            this->prop->setRegionDesc(desc);
            this->prop->setColorType(type);
        }

        Policies getPolicy() {
            return this->po;
        }

        RegionDesc getRegionDesc() {
            return this->prop->getRegionDesc();
        }

        ColorType getColorType() {
            return this->prop->getColorType();
        }

        std::string getPolicyVal() {
            if (this->po == Policies::r_desc) {
                return "R_DESC: " + region_desc::toString(this->prop->getRegionDesc());
            }
            if (this->po == Policies::similar_base_00) {
                return "SIMILAR_BASE_00";
            }
            if (this->po == Policies::color_value_00) {
                return "COLOR_VALUE_00";
            }
            return "NA";
        } 
};
#endif