#ifndef simple_explore_H
#define simple_explore_H

#include <deque>
#include <map>
#include <vector>

#include <opencv2/core.hpp>

#include "abstract_explore.h"
#include "status.h"
#include "iapcv_log.h"
#include "matrix_bounds.h"
#include "region_desc.h"
#include "region_evaluator.h"
#include "region_print.h"
#include "span_node.h"

/**
 * @20251012
 * We use simple_explore to handle Policies::r_desc and to debug the basic exploration logic,
 * i.e., explore_hort and explore_vert
 *
 * Difference between simple_explore and region_explore:
 * get_top(), get_bottom(), get_left(), get_right(), explore()
 * 
 * These functions are same:
 * get_col_span(), get_row_span(), explore_hort(), explore_vert() 
 */
class simple_explore : public abstract_explore {
    private:
        RegionDesc desc;
        region_evaluator* evaluator;
        region_print* rpt;
        
        bool_status* sta;

        matrix_bounds* mbounds;

    protected:
        int get_top(const cv::Mat& mat, int c, int r);
        int get_bottom(const cv::Mat& mat, int c, int r);
        int get_left(const cv::Mat& mat, int c, int r);
        int get_right(const cv::Mat& mat, int c, int r);

    public:
        simple_explore();
        ~simple_explore();

        void explore(cv::Mat& mat, int row, int col, std::deque<span_node*>& rows, std::deque<span_node*>& cols, std::map<int, vector<int*>*>& rows_map, std::map<int, vector<int*>*>& cols_map);
        void setLogger(iapcv_log* logger);
        void setMatrixBounds(matrix_bounds* mb);
        void setRegionEvaluator(region_evaluator* eval);
        void setRegionDesc(RegionDesc desc);
        void setRegionPrint(region_print* p);
        
};
#endif