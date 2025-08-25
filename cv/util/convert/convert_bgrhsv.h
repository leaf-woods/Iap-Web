#ifndef CONVERT_BGRHSV_H
#define CONVERT_BGRHSV_H

#include <opencv2/core.hpp>

class convert_bgrhsv{

    public:
      convert_bgrhsv();
      ~convert_bgrhsv();

      double diffBGR(uchar b1, uchar g1, uchar r1, uchar b2, uchar g2, uchar r2);
      double diffHSV(uchar h1, uchar s1, uchar v1, uchar h2, uchar s2, uchar v2);
      void toHsvCV(uchar* hsv, uchar b, uchar g, uchar r);
      
}; 
#endif

