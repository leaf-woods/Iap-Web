#ifndef IMAGECOLORDESC_H
#define IMAGECOLORDESC_H

#include <unordered_map>
#include <vector>

#include <opencv2/core.hpp>

#include "vtree/colorvaluetree.h"
#include "convertnumber.h"
#include "convert_bgrhsv.h"
#include "htree/hsvtree.h"
#include "range.h"

class imagecolordesc : public iclearable{
    private:
      const std::string DEBUG_H;
      const std::string WARN_H;

      int W; int H;
      int BH[256]; int GS[256]; int RV[256];

      int color_type;
      int hsv_dim;

      std::unordered_map<int, std::vector<int*>*>  *color_map;
      colorvaluetree* t;
      hsvtree* ht;

      iap_print* printer;
      convert_bgrhsv* calc;
      convertnumber* convert;

      range* rg; 

    public:
      const static int DEBUG = 0;
      
    private:
      void clearSTDVector(std::vector<int*>* v);
      void printPixelIndex(int* array);
      void setColorValueTree();
      void setHsvTree();
      void setMinMax();
      
    public:
      imagecolordesc();
      ~imagecolordesc();
      
      void clear();
      void init();
      std::vector<int*>* containsBGR(uchar b, uchar g, uchar r);
      std::vector<uchar*>* findB(uchar b);
      std::vector<uchar*>* findPixelColors(uchar hue);
      iap_print* getPrint();
      void setDescData(cv::Mat &mat);
      void setPrint(iap_print* p);
      void setColorType(int ct);
      void setConvertHSV(convert_bgrhsv* calc);
      void setConvertNum(convertnumber* con);
      void setHsvDim(int hd);
      void setRange(range* rg);
      void printColorValueTree();
      void printHsvTree();
      void printMap();
      void printMinMax();
      std::string writeColorValueTreeContents(); 
      std::string writeContents(); 

      uchar* getLowerBoundHSV();
      uchar* getUpperBoundHSV();
};
#endif