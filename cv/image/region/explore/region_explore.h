#ifndef REGION_EXPLORE_H
#define REGION_EXPLORE_H

#include "absr_explore.h"

class region_explore : public absr_explore{
    private:
        void explore_hort(const cv::Mat& mat, const span_node& row_sp);
        void explore_vert(const cv::Mat& mat, const span_node& col_sp);
        int get_top(const cv::Mat& mat, int c, int r);
        int get_bottom(const cv::Mat& mat, int c, int r);
        int get_left(const cv::Mat& mat, int c, int r);
        int get_right(const cv::Mat& mat, int c, int r);
        void get_col_span(const cv::Mat& mat, int c, int r);
        void get_row_span(const cv::Mat& mat, int c, int r);

    public:
        region_explore() { }
        ~region_explore() { }
        void explore(cv::Mat& mat, int row, int col, std::deque<span_node*>& rows, std::deque<span_node*>& cols, std::map<int, vector<int*>*>& rows_map, std::map<int, vector<int*>*>& cols_map);

};
#endif