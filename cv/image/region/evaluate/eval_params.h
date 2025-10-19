#ifndef EVAL_PARAMS_H
#define EVAL_PARAMS_H

#include <any>
#include <iostream>
#include <unordered_map>

#include <opencv2/core.hpp>

#include "region_desc.h"

enum class ParamName {
    na,
    color1,
    color2,
    startPixelColor,
    startDesc
};

class eval_params {
    private:

        std::unordered_map<ParamName, std::any>* params_map;
        
        cv::Vec3b color1;
        cv::Vec3b color2;

    public:
        eval_params() {
            params_map = new std::unordered_map<ParamName, std::any>();
        }

        ~eval_params() {
            clearParams();
            delete params_map;
        }
        
        void clearParams() {
            if (params_map->size() > 0) {
                for (auto it=params_map->begin(); it!=params_map->end();) {
                    it = params_map->erase(it);
                }
            }
        }

        void setParam(ParamName n, cv::Vec3b color) {
            params_map->insert_or_assign(n, color);
        }

        void setParam(ParamName n, RegionDesc d) {
            if (ParamName::startDesc != n) {
                std::cout << "Bad parameter." << std::endl;
                return;
            }
            params_map->insert_or_assign(n, d);
        }

        // https://en.cppreference.com/w/cpp/utility/any.html
        std::any getParam(ParamName n) {
            auto search = params_map->find(n);
            if (search == params_map->end()) {
                std::any a;
                return a;
            }
            return search->second;
        }

        int size() {
            return params_map->size();
        }
};
#endif