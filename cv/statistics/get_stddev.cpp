#include <cmath>

#include "get_stddev.h"

using namespace std;
get_stddev::~get_stddev() {
    logger = nullptr;
}

cv::Vec3d get_stddev::calc_mean(const vector<int*>& v, const cv::Mat& mat) {
    cv::Vec3d rv;
    if (v.size() == 0) {
        logger->error("Empty vector.");
        rv[0] = rv[1] = rv[2] = INVALID;
        return rv;
    }

    cv::Vec3b entry;
    double sum_d0 = 0.0d;
    double sum_d1 = 0.0d;
    double sum_d2 = 0.0d;
    for (int i=0; i<v.size(); i++) {
        entry = mat.at<cv::Vec3b>(v.at(i)[0], v.at(i)[1]);
        sum_d0 += static_cast<int>(entry[0]);
        sum_d1 += static_cast<int>(entry[1]);
        sum_d2 += static_cast<int>(entry[2]);
    }
    rv[0] = sum_d0/v.size();
    rv[1] = sum_d1/v.size();
    rv[2] = sum_d2/v.size(); 
    logger->fdebug("sfsfsfs", "mean: [ ", rv[0], " , ", rv[1], " , ", rv[2], " ]");
    return rv;
}

cv::Vec3d get_stddev::calc_variance(const vector<int*>& v, const cv::Mat& mat) {
    cv::Vec3d rv;
    if (v.size() == 0) {
        logger->error("Empty vector.");
        rv[0] = rv[1] = rv[2] = INVALID;
        return rv;
    }
    if (v.size() == 1) {
        logger->error("Vector size 1. Cannot calculate variance.");
        rv[0] = rv[1] = rv[2] = INVALID;
        return rv;
    }

    cv::Vec3d mean = calc_mean(v, mat);
    if (mean[0] == INVALID || mean[1] == INVALID || mean[2] == INVALID) {
        logger->error("Invalid mean values. ");
        rv[0] = rv[1] = rv[2] = INVALID;
        return rv;
    }

    cv::Vec3b entry;
    double sum_d0_var = 0.0d;
    double sum_d1_var = 0.0d;
    double sum_d2_var = 0.0d;
    for (int i=0; i<v.size(); i++) {
        entry = mat.at<cv::Vec3b>(v.at(i)[0], v.at(i)[1]);
        sum_d0_var += pow((static_cast<int>(entry[0])-mean[0]), 2);
        sum_d1_var += pow((static_cast<int>(entry[1])-mean[1]), 2);
        sum_d2_var += pow((static_cast<int>(entry[2])-mean[2]), 2);
    }
    rv[0] = sum_d0_var/(v.size()-1);
    rv[1] = sum_d1_var/(v.size()-1);
    rv[2] = sum_d2_var/(v.size()-1); 
    logger->fdebug("sfsfsfs", "variance: [ ", rv[0], " , ", rv[1], " , ", rv[2], " ]");
    return rv;
}

cv::Vec3d get_stddev::calc_stddev(const vector<int*>& v,  const cv::Mat& mat) {
    cv::Vec3d rv;
    cv::Vec3d variance = calc_variance(v, mat);
    if (variance[0] == INVALID || variance[1] == INVALID || variance[2] == INVALID) {
        logger->error("Invalid variances");
        rv[0] = rv[1] = rv[2] = INVALID;
        return rv;
    }
    rv[0] = sqrt(variance[0]);
    rv[1] = sqrt(variance[1]);
    rv[2] = sqrt(variance[2]);
    logger->fdebug("sfsfsfs", "std dev: [ ", rv[0], " , ", rv[1], " , ", rv[2], " ]");
    return rv;
}

void get_stddev::setLogger(iapcv_log* log) {
    this->logger = log;
}