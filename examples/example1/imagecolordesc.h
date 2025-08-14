#ifndef IMAGECOLORDESC_H
#define IMAGECOLORDESC_H

#include <unordered_map>
#include <vector>

#include <opencv2/core.hpp>

#include "vtree/colorvaluetree.h"
#include "convertnumber.h"

class imagecolordesc {
    private:
      std::unordered_map<int, std::vector<int*>*>  *color_map;
      convertnumber* convert;

      int B[256]; int G[256]; int R[256];
      colorvaluetree* t;

    public:
      int W; int H;

      uchar b_max;
      uchar b_min;
      uchar g_max; 
      uchar g_min;
      uchar r_max;
      uchar r_min;

    private:
      void clearSTDVector(std::vector<int*>* v);
      void printBGR(uchar* array);
      void printPixelIndex(int* array);
      void setColorValueTree();
      
    public:
      imagecolordesc();
      ~imagecolordesc();

      void setDescData(cv::Mat &mat);
      void setMinMax();
      void printColorValueTree();
      void printMap();
      void printMinMax(); 
};
#endif
