#ifndef REGION_EXPLORE_H
#define REGION_EXPLORE_H

#include <deque>
#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "explore_helper.h"
#include "eval_params.h"
#include "eval_policy.h"
#include "iapcv_log.h"
#include "matrix_bounds.h"
#include "region_evaluator.h"
#include "region_print.h"
#include "span_node.h"
#include "status.h"

/**
 * @20251014 
 * We are still trying some policies for a solution. Time efficiency is less important than flexibilty. 
 */
class region_explore {
    private:
        static const int INVALID = -1;

        static const int COL = span_constants::COL;
        static const int ROW = span_constants::ROW;

        int H;
        int W;
        
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

        eval_policy* po;
        eval_params* pm;

        RegionDesc start;

        explore_helper* helper;

    private:
        void checkDiagnal(const cv::Mat& mat, int r, int c);
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
        void explore_r(cv::Mat& mat, int row, int col, std::deque<span_node*>& rows, std::deque<span_node*>& cols, std::map<int, vector<int*>*>& rows_map, std::map<int, vector<int*>*>& cols_map);
       
        void explore_diag(const cv::Mat& mat, vector<int*>* dv);
        void setEvalPolicy(eval_policy* po);
        void setExploreHelper(explore_helper* helper);
        void setLogger(iapcv_log* logger);
        void setMatrixBounds(matrix_bounds* mb);
        void setRegionEvaluator(region_evaluator* eval);
        void setRegionPrint(region_print* p);
        void setStartPixelRegionDesc(RegionDesc d);
};
#endif