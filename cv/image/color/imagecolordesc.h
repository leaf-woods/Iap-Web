#ifndef IMAGECOLORDESC_H
#define IMAGECOLORDESC_H

#include <unordered_map>
#include <vector>

#include <opencv2/core.hpp>

#include "convertnumber.h"
#include "convert_bgrhsv.h"
#include "d3tree.h"
#include "dimensions.h"
#include "iapcv_log.h"
#include "imagecolorvalues.h"
#include "range.h"
#include "vtree/colorvaluetree.h"

struct color_desc_state {
    public:
        ClearableState s_color_map; 
        ColorType s_color_type;
        ClearableState s_tree_cvt;
        ClearableState s_tree_d3t;
};
class imagecolordesc : public iclearable{
    private:
      iapcv_log* logger;

      int W; int H;
      int BH[256]; int GS[256]; int RV[256];

      ColorType color_type = ColorType::NA;

      std::unordered_map<int, std::vector<int*>*>  *color_map;
      //std::unordered_map<int, std::vector<int*>*>  *compact_map;
      colorvaluetree* t;
      d3tree* d3t;

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
      //@NOT USED
      std::vector<int*>* containsBGR(uchar b, uchar g, uchar r);
      //@NOT USED
      std::vector<uchar*>* findB(uchar b);
      //@NOT USED
      std::vector<uchar*> findPixelColors(uchar hue);
      ColorType getColorType();
      void setDescData(const cv::Mat &mat, ColorType type);
      void setLogger(iapcv_log* logger);
      void setLogLevel(int level);
      void setPrint(iap_print* p);
      void setConvertHSV(convert_bgrhsv* calc);
      void setConvertNum(convertnumber* con);
      void setColorValueTree();
      void setD3Tree(DimType type, int dim);
      void setRange(range* rg);
      void printColorValueTree();
      void printD3Tree();
      void printMap();
      void printMinMax();
      void printState();
      //@NOT USED
      std::string writeColorValueTreeContents(); 
      //@NOT USED
      std::string writeContents(); 

      uchar* getLowerBoundHSV();
      uchar* getUpperBoundHSV();

      void getAllHue(std::vector<int>* vh);
      int getImageSize();

      int countColor(int color);
      bool verifyState(const color_desc_state& cst);

};
#endif