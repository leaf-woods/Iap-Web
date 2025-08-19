#ifndef CALCBGRHSV_H
#define CALCBGRHSV_H

#include <opencv2/core.hpp>

class calcBgrHsv{

    public:
      calcBgrHsv();
      ~calcBgrHsv();

      double diffBGR(uchar b1, uchar g1, uchar r1, uchar b2, uchar g2, uchar r2);
      double diffHSV(int h1, int s1, int v1, int h2, int s2, int v2);
      void toHsvCV(int* hsv, uchar b, uchar g, uchar r);
      
}; 
#endif

