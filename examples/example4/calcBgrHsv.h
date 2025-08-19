#ifndef CALCBGRHSV_H
#define CALCBGRHSV_H

#include <opencv2/core.hpp>

class calcBgrHsv{

    public:
      calcBgrHsv();
      ~calcBgrHsv();

      double diffBGR(uchar b1, uchar g1, uchar r1, uchar b2, uchar g2, uchar r2);
      double diffHSV(uchar h1, uchar s1, uchar v1, uchar h2, uchar s2, uchar v2);
      void toHsvCV(uchar* hsv, uchar b, uchar g, uchar r);
      
}; 
#endif



