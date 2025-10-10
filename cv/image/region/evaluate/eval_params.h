#ifndef EVAL_PARAMS_H
#define EVAL_PARAMS_H

#include <opencv2/core.hpp>

enum class ParamName {
    na,
    key1,
    key2
};

class eval_params {
    private:
        ParamName k1;
        cv::Vec3b color1;

        ParamName k2;
        cv::Vec3b color2;

    public:
        void clearParams() {
            k1 = ParamName::na;
            //color1 = nullptr;
            k2 = ParamName::na;
            //color2 = nullptr;
        }

        void setParams(ParamName n1, cv::Vec3b c1, ParamName n2, cv::Vec3b c2) {
            k1 = n1;
            k2 = n2;
            color1 = c1;
            color2 = c2;
        }

        void setParam1(ParamName n1, cv::Vec3b c1) {
            k1 = n1;
            color1 = c1;
        }

        void setParam2(ParamName n2, cv::Vec3b c2) {
            k2 = n2;
            color2 = c2;
        }

        cv::Vec3b getParam1() {
            return color1;
        }

        cv::Vec3b getParam2() {
            return color2;
        }
};
#endif