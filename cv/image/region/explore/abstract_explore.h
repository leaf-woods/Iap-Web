#ifndef ABSTRACT_EXPLORE_H
#define ABSTRACT_EXPLORE_H

#include <deque>
#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "explore_helper.h"
#include "iapcv_log.h"
#include "span_node.h"

/**
 * @20251013 
 * We don't provide evaluator in abstract_explore since it does not use it.
 * Being common between simple_explore and region_explore does not lead to 
 * an instance variable of abstract_explore.
 */
class abstract_explore {
    private:
        explore_helper* helper;

    protected:
        static const int INVALID = -1;

        int H;
        int W;

        iapcv_log* logger;

        std::deque<span_node*>* rows;
        std::deque<span_node*>* cols;
        std::map<int, std::vector<int*>*>* rows_map;
        std::map<int, std::vector<int*>*>* cols_map;

        std::vector<int*>* dv;

    protected:
        virtual void checkDiagnal(const cv::Mat& mat, int r, int c)=0;
        void explore_diag(const cv::Mat& mat, vector<int*>* dvec);

        virtual int get_top(const cv::Mat& mat, int c, int r)=0;
        virtual int get_bottom(const cv::Mat& mat, int c, int r)=0;
        virtual int get_left(const cv::Mat& mat, int c, int r)=0;
        virtual int get_right(const cv::Mat& mat, int c, int r)=0;
        
        void explore_hort(const cv::Mat& mat, const span_node& row_sp);
        void explore_vert(const cv::Mat& mat, const span_node& col_sp);
        void get_col_span(const cv::Mat& mat, int c, int r);
        void get_row_span(const cv::Mat& mat, int c, int r);

    public:
        ~abstract_explore();
        
        void setExploreHelper(explore_helper* h);
        void setLogger(iapcv_log* logger);
        
};
#endif