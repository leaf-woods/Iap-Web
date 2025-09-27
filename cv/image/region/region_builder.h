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
#include "region_explore.h"
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

      int W = 0; int H = 0;

      RegionDesc desc = RegionDesc::na;

      std::deque<span_node*>* rows;
      std::deque<span_node*>* cols;

      std::map<int, vector<int*>*>* rows_map;
      std::map<int, vector<int*>*>* cols_map;

      iapcv_log logger;
      iap_print printer;
      region_print* rpt;

      int count;
      region_evaluator* evaluator;
      region_explore* exp;

      bool_status* sta;

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

      void countRegion();
      int countVector(const vector<int*>& v);
      void init();

    public:
      region_builder();
      ~region_builder();

      void clear();
      void explore(cv::Mat& mat, int r, int c);
      //void explore_r(const cv::Mat& mat, int row, int col);
      bool getNextStartPoint(size_t s, int* pixel);
      
      void setLogger(iapcv_log& logger);
      void setLogLevel(int level);
      void setPrint(iap_print& printer);
      void setRegionPrint(region_print* p);
      void setRegionDesc(RegionDesc desc);
      void setRegionEvaluator(region_evaluator* eval);
      void setRegionExplore(region_explore* exp);
      int size();
      
      
};
#endif