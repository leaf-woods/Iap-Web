#ifndef ABSR_EXPLORE_H
#define ABSR_EXPLORE_H

#include <deque>
#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "status.h"
#include "iapcv_log.h"
#include "region_desc.h"
#include "region_evaluator.h"
#include "region_print.h"
#include "span_node.h"

struct bounds {
    static const int SKIP = 1;
    static const int NO_OP = 2;
    static const int ADJUSTED = 3;
    
    int op; 
    int adjusted[2] = {0, 0};
};

class absr_explore {
    protected: 
        static const int INVALID = -1;

        static const int COL = span_constants::COL;
        static const int ROW = span_constants::ROW;

        int H;
        int W;
        RegionDesc desc;
        region_evaluator evaluator;
        region_print rpt;
        iapcv_log logger;

        bool_status* sta;

        std::deque<span_node*>* rows;
        std::deque<span_node*>* cols;
        std::map<int, std::vector<int*>*>* rows_map;
        std::map<int, std::vector<int*>*>* cols_map;

    protected:
        void adjustBounds(bounds& b, int begin, int end, const std::vector<int*>& v);
        bool contains(const std::vector<int*>& v, int n);
        span_node* createSpanNode(int type, int offset, int lower, int upper);

    public:
        absr_explore();
        ~absr_explore();
        void setLogger(iapcv_log& logger);
        void setRegionEvaluator(region_evaluator& eval);
        void setRegionDesc(RegionDesc desc);
        void setRegionPrint(region_print& p);
};

#endif