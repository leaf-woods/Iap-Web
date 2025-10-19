#ifndef GET_STDDEV_H
#define GET_STDDEV_H

#include <vector>

#include <opencv2/core.hpp>

#include "iapcv_log.h"

class get_stddev {
    private:
        const double INVALID = -1.0;

        iapcv_log* logger;

    public:
        ~get_stddev();

        cv::Vec3d calc_mean(const std::vector<int*>& v, const cv::Mat& mat);
        cv::Vec3d calc_stddev(const std::vector<int*>& v, const cv::Mat& mat);
        cv::Vec3d calc_variance(const std::vector<int*>& v, const cv::Mat& mat);
        
        void setLogger(iapcv_log* log);
};
#endif