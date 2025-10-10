#ifndef EVAL_POLICIES_H
#define EVAL_POLICIES_H

#include "region_desc.h"

enum class Policies {
    na,
    r_desc,
    similar_base_00
};

class eval_policy {
    private:
        RegionDesc desc = RegionDesc::na;
        Policies po = Policies::na;

    public:
        void setPolicy(RegionDesc desc) {
            this->po = Policies::r_desc;
            this->desc = desc;
        }

        void setPolicy(Policies po) {
            this->po = po;
        }

        Policies getPolicy() {
            return this->po;
        }

        RegionDesc getRegionDesc() {
            return this->desc;
        }

        std::string getPolicyVal() {
            if (this->po == Policies::r_desc) {
                return "R_DESC: " + region_desc::toString(desc);
            }
            if (this->po == Policies::similar_base_00) {
                return "SIMILAR_BASE_00";
            }
            return "NA";
        }
};
#endif