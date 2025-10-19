#include <cassert>

#include "region_colors_provider.h" 

using namespace std;

region_colors_provider::~region_colors_provider() {
    logger = nullptr;
}

void region_colors_provider::getRegionColors(const cv::Mat& mat, map<int, vector<int*>*>& m, vector<int*>* colorIndices, size_t t) {
    assert(t==2);
    int b0 = 0;
    int b1 = 0;
    
    for (auto it=m.begin(); it!=m.end(); it++) {
        for (int i=0; i<it->second->size(); i++) {
            b0 = it->second->at(i)[0];
            b1 = it->second->at(i)[1];
            for (int k=b0; k<=b1; k++) {
                auto index = new int[]{it->first, k};
                colorIndices->push_back(index);
            }
        }
    }
    logger->debug("region pixel count: ", colorIndices->size());
}

void region_colors_provider::getRegionColors(const cv::Mat& mat, map<int, vector<int*>*>& m, int key, vector<int*>* colorIndices, size_t t) {
    assert(t==2 && key >= 0);
    
    auto search = m.find(key);
    if (search == m.end()) {
        logger->error("Map does not contain key: ", key);
        return;
    }

    int b0 = 0;
    int b1 = 0;

    for (int i=0; i<search->second->size(); i++) {
        b0 = search->second->at(i)[0];
        b1 = search->second->at(i)[1];
        for (int k=b0; k<=b1; k++) {
            auto index = new int[]{key, k};
            colorIndices->push_back(index);
        }
    }
    logger->fdebug("snsn", "region pixel count: key: ", key, " count: ", colorIndices->size());
}

void region_colors_provider::setLogger(iapcv_log* log) {
    this->logger = log;
}