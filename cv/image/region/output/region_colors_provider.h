#ifndef REGION_COLORS_PROVIDER_H
#define REGION_COLORS_PROVIDER_H

#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "iapcv_log.h"

class region_colors_provider {
    private:
        iapcv_log* logger;
    public:
        ~region_colors_provider();

        void getRegionColors(const cv::Mat& mat, std::map<int, std::vector<int*>*>& m, std::vector<int*>* colorIndices, size_t t);
        void getRegionColors(const cv::Mat& mat, std::map<int, std::vector<int*>*>& m, int key, std::vector<int*>* colorIndices, size_t t);

        void setLogger(iapcv_log* log);
};
#endif