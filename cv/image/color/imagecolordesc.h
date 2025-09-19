#ifndef IMAGECOLORDESC_H
#define IMAGECOLORDESC_H

#include <unordered_map>
#include <vector>

#include <opencv2/core.hpp>

#include "convertnumber.h"
#include "convert_bgrhsv.h"
#include "iapcv_log.h"
#include "htree/hsvtree.h"
#include "range.h"
#include "vtree/colorvaluetree.h"

class imagecolordesc : public iclearable{
    private:
      iapcv_log* logger;

      int W; int H;
      int BH[256]; int GS[256]; int RV[256];

      int color_type = imagecolorvalues::NOT_AVAILABLE;

      std::unordered_map<int, std::vector<int*>*>  *color_map;
      std::unordered_map<int, std::vector<int*>*>  *compact_map;
      colorvaluetree* t;
      hsvtree* ht;

      iap_print* printer;
      convert_bgrhsv* calc;
      convertnumber* convert;

      range* rg; 
      
    private:
      void clearMap(unordered_map<int, vector<int*>*>& m);
      void clearSTDVector(std::vector<int*>* v);
      void setMinMax();
      
    public:
      imagecolordesc();
      ~imagecolordesc();
      
      void clear();
      void init();
      std::vector<int*>* containsBGR(uchar b, uchar g, uchar r);
      std::vector<uchar*>* findB(uchar b);
      std::vector<uchar*>* findPixelColors(uchar hue);
      int getColorType();
      void setDescData(const cv::Mat &mat, int type);
      void setLogLevel(int level);
      void setPrint(iap_print* p);
      void setConvertHSV(convert_bgrhsv* calc);
      void setConvertNum(convertnumber* con);
      void setColorValueTree();
      void setHsvTree(int hsv_dim);
      void setRange(range* rg);
      void printColorValueTree();
      void printHsvTree();
      void printMap();
      void printMinMax();
      void printState();
      std::string writeColorValueTreeContents(); 
      std::string writeContents(); 

      uchar* getLowerBoundHSV();
      uchar* getUpperBoundHSV();

      void getAllHue(std::vector<int>* vh);
      int getImageSize();

      int countColor(int color);

};
#endif