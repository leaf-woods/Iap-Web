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

        void clear() {
            this->desc = RegionDesc::na;
            this->color_type = ColorType::NA;
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
            prop->clear();
        }

    public:
        eval_policy() {
            prop = new eval_policy_property();
            // RegionDesc::na = -1, we have manually call clear().
            prop->clear();
        }

        ~eval_policy() {
            delete prop;
        }

        void setPolicy(Policies po) {
            this->po = po;
            if (po != Policies::r_desc) {
                prop->clear();
            }
        }

        void setPolicy(RegionDesc desc, ColorType type) {
            this->po = Policies::r_desc;
            this->prop->setRegionDesc(desc);
            this->prop->setColorType(type);
        }

        void setColorType(ColorType type) {
            this->prop->setColorType(type);
        }

        void setRegionDesc(RegionDesc d) {
            this->prop->setRegionDesc(d);
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