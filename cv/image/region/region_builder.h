#ifndef REGION_BUILDER_H
#define REGION_BUILDER_H

#include <bitset>
#include <deque>
#include <map>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "abstract_explore.h"
#include "border_pixel_diff_node.h"
#include "explore_helper.h"
#include "eval_policy.h"
#include "imagecolorvalues.h"
#include "iapcv_log.h"
#include "iap_print.h"
#include "iclearable.h"
#include "matrix_bounds.h"
#include "pixel_comparator.h"
#include "region_colors_provider.h"
#include "region_evaluator.h"
#include "region_explore.h"
#include "simple_explore.h"
#include "span_node.h"

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

      int H=0; int W=0;

      std::deque<span_node*>* rows;
      std::deque<span_node*>* cols;

      std::map<int, vector<int*>*>* rows_map;
      std::map<int, vector<int*>*>* cols_map;

      iapcv_log* logger;
      iap_print* printer;
      region_print* rpt;

      int count;
      int count_internal;
      region_evaluator* evaluator;
      region_explore* exp;

      simple_explore* sexp;

      bool_status* sta;
      matrix_bounds* mbounds;

      vector<int*>* dv;
      vector<border_pixel_diff_node*>* bv;

      eval_policy* po;
      RegionDesc start;

      region_colors_provider* prov;

    public:

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
      void checkNorth(int row, int col, std::bitset<8>& x);
      void checkSouth(int row, int col, std::bitset<8>& x);
      void clearMap(map<int, vector<int*>*>& m);

      
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
      void computeDelta(cv::Vec<unsigned char, 3>& entry, cv::Vec<unsigned char, 3>& neighbor, cv::Vec<int, 3>& df);
      void containsNorth(const vector<int*>& v, int n, std::bitset<8>& x);
      void containsSouth(const vector<int*>& v, int n, std::bitset<8>& x);
      void countRegionPixels();
      int countVector(const vector<int*>& v);
      void init();
      void setBorderPixelsDiff(const cv::Mat& mat, int row, int col, bitset<8>& x);
      void setPixelDiff(const cv::Mat& mat, int row, int col, border_pixel_diff_node& bn, direction dr);
      bool verifyBorderPixels(const border_pixel_diff_node& bn);

    public:
      region_builder();
      ~region_builder();

      void clear();
      void computeBorders(const cv::Mat& mat);
      void explore(cv::Mat& mat, int r, int c, int start_direction);

      void explore(simple_explore* sp, cv::Mat& mat, int r, int c);

      void getAllBorderPixels(const cv::Mat& mat);
      bool getNextStartPoint(size_t s, int* pixel);
      void getRegionColorsIndices(const cv::Mat& mat, std::vector<int*>* colorIndices, size_t t);
      void printMapOnMatrix(const cv::Mat& mat);
      void setLogger(iapcv_log* logger);
      void setLogLevel(int level);
      void setMatrixBounds(matrix_bounds* mb);
      void setEvalPolicy(eval_policy* po);
      void setPrint(iap_print* printer);
      void setRegionPrint(region_print* p);
      void setRegionEvaluator(region_evaluator* eval);
      void setRegionExplore(region_explore* exp);
      void setRegionColorProvider(region_colors_provider* prov);
      void setSubMatrix(int r, int c, int num_rs, int num_cs);
      int size();
      void useMatrix();
      
};
#endif