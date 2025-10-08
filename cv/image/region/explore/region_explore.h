#ifndef REGION_EXPLORE_H
#define REGION_EXPLORE_H

#include <deque>
#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "status.h"
#include "iapcv_log.h"
#include "matrix_bounds.h"
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
class region_explore {
    private:
        static const int INVALID = -1;

        static const int COL = span_constants::COL;
        static const int ROW = span_constants::ROW;

        int H;
        int W;
        RegionDesc desc;
        region_evaluator* evaluator;
        region_print* rpt;
        iapcv_log* logger;

        bool_status* sta;

        std::deque<span_node*>* rows;
        std::deque<span_node*>* cols;
        std::map<int, std::vector<int*>*>* rows_map;
        std::map<int, std::vector<int*>*>* cols_map;

        std::vector<int*>* dv;

        matrix_bounds* mbounds;

    private:
        void adjustBounds(bounds& b, int begin, int end, const std::vector<int*>& v);
        void checkDiagnal(const cv::Mat& mat, int r, int c);
        bool contains(const std::vector<int*>& v, int n);
        bool containsOnMap(int row, int col);
        span_node* createSpanNode(int type, int offset, int lower, int upper);
        void explore_hort(const cv::Mat& mat, const span_node& row_sp);
        void explore_vert(const cv::Mat& mat, const span_node& col_sp);
        void get_col_span(const cv::Mat& mat, int c, int r);
        void get_row_span(const cv::Mat& mat, int c, int r);

        int get_top(const cv::Mat& mat, int c, int r);
        int get_bottom(const cv::Mat& mat, int c, int r);
        int get_left(const cv::Mat& mat, int c, int r);
        int get_right(const cv::Mat& mat, int c, int r);
        
    public:
        region_explore();
        ~region_explore();

        void explore(cv::Mat& mat, int row, int col, std::deque<span_node*>& rows, std::deque<span_node*>& cols, std::map<int, vector<int*>*>& rows_map, std::map<int, vector<int*>*>& cols_map);
        void explore_diag(const cv::Mat& mat, vector<int*>* dv);
        void setLogger(iapcv_log* logger);
        void setMatrixBounds(matrix_bounds* mb);
        void setRegionEvaluator(region_evaluator* eval);
        void setRegionDesc(RegionDesc desc);
        void setRegionPrint(region_print* p);
        
};
#endif