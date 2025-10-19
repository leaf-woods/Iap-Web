#ifndef EXPLORE_HELPER_H
#define EXPLORE_HELPER_H

#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "iapcv_log.h"
#include "span_node.h"

struct bounds {
    static const int SKIP = 1;
    static const int NO_OP = 2;
    static const int ADJUSTED = 3;
    
    int op; 
    int adjusted[2] = {0, 0};
};

class explore_helper {
    private:
        iapcv_log* logger;

    public:
        static const int COL = span_constants::COL;
        static const int ROW = span_constants::ROW;
 
    public:
        ~explore_helper();

        void adjustBounds(bounds& b, int begin, int end, const std::vector<int*>& v);
        bool contains(const std::vector<int*>& v, int n);
        bool containsOnMap(int which, const std::map<int, std::vector<int*>*>& m, int row, int col);
        span_node* createSpanNode(int type, int offset, int lower, int upper);
        void setLogger(iapcv_log* logger);
};
#endif