#ifndef REGION_BUILDER_H
#define REGION_BUILDER_H

#include <deque>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "imagecolorvalues.h"
#include "iapcv_log.h"
#include "iap_print.h"
#include "iclearable.h"
#include "pixel_comparator.h"
#include "region_desc.h"
#include "region_evaluator.h"

struct span_node {
    // row_no or col_no
    int offset;  
    int type;
    int span[2] = {0, 0};
}; 

struct bounds {
    static const int SKIP = 1;
    static const int NO_OP = 2;
    static const int ADJUSTED = 3;
    
    int op; 
    int adjusted[2] = {0, 0};
};

/*
 * @20250915
 * A region is a connected area on an image where all pixels in the region has common features 
 * defined by the definition of "being connected". For example in region r, all pixels have same color.

 Seems like an explorer class provides the function explore() and returns a region instance.
 */
class region_builder : public iclearable {
    private:
      /*
       * Region builder cannot find any region (smallest is one pixel) based on the given region description desc.
       */  
      //static const int NOT_EXPLORABLE = -1;

      static const int INVALID = -1;

      int W = 0; int H = 0;

      RegionDesc desc = RegionDesc::na;

      std::deque<span_node*>* rows;
      std::deque<span_node*>* cols;

      std::map<int, vector<int*>*>* rows_map;
      std::map<int, vector<int*>*>* cols_map;

      iapcv_log* logger;
      iap_print* printer;

      int count;
      region_evaluator* evaluator;

      bool_status* sta;

    public:
      static const int ROW = 1000;
      static const int COL = 2000;

      static const int IN_BOUND = 10000;
      static const int FREE = 20000;

      /*
       * Free exploration: pixel (r, c) may not be in the generated region.
       * This means for IN_BOUND exploration, we check the start pixel(r, c). 
       * If it is not satisfied with region description desc, we return NOT_EXPLORABLE.
       * For free exploration, we search the image for a qualified pixel P-Qualified, i.e., satified
       * region description desc given the start pixel P-Start. Then we run the exploration using P-Qualified.
       */

    private:
      void adjustBounds(bounds& b, int begin, int end, const vector<int*>& v);
      void checkInBound(const cv::Mat& mat, int r, int c, bool_status& sta);
      void clearMap(map<int, vector<int*>*>& m);

      /*
      template<typename T>
      void clearVector(vector<T*>& v) {
          logger->debug("clear vector: size: ", v.size());
    
          int s = v.size();
          for (int i=0; i < s; i++) {
              delete v.at(i);
          }
          v = vector<T*>();
          logger->debug("clear vector: vector elements deleted.");
      }
      */

      bool contains(const vector<int*>& v, int n);
      void countRegion();
      int countVector(const vector<int*>& v);
      span_node* createSpanNode(int type, int offset, int lower, int upper);
      int get_top(const cv::Mat& mat, int c, int r);
      int get_bottom(const cv::Mat& mat, int c, int r);
      int get_left(const cv::Mat& mat, int c, int r);
      int get_right(const cv::Mat& mat, int c, int r);
      void init();
      void printSpan(const span_node& sp);
      void printVector(const vector<int*>& v);

    public:
      region_builder();
      ~region_builder();

      void clear();
      void explore_hort(const cv::Mat& mat, const span_node& row_sp);
      void explore_vert(const cv::Mat& mat, const span_node& col_sp);
      void explore(const cv::Mat& mat, int r, int c);
      void explore_r(const cv::Mat& mat, int row, int col);
      void get_col_span(const cv::Mat& mat, int c, int r);
      void get_row_span(const cv::Mat& mat, int c, int r);
      bool getNextStartPoint(size_t s, int* pixel);
      void printMap(string which, const map<int, vector<int*>*>& m);
      void printQueue(string which, std::deque<span_node*>* q);
      void setLogLevel(int level);
      void setPrint(iap_print* printer);
      void setRegionDesc(RegionDesc desc);
      void setRegionEvaluator(region_evaluator* eval);
      int size();
};
#endif