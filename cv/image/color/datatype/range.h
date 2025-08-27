#ifndef RANGE_H
#define RANGE_H

#include <cassert>

#include <opencv2/core.hpp>

#include "iclearable.h"
#include "imagecolorvalues.h"

class range : public iclearable {
    private:
      int color_type;

      uchar* lower;
      uchar* upper;

    public:
      range() {
          lower = new uchar[3]{0};
          upper = new uchar[3]{0};
      }

      ~range() {
          delete lower;
          delete upper;    
      }

      void clear() {
        if (lower) {
          lower[0] = '\0'; lower[1] = '\0'; lower[2] = '\0';
        }
        if (upper) {
          upper[0] = '\0'; upper[1] = '\0'; upper[2] = '\0';
        }
      }

      void setColorType(int type) {
        assert(type==imagecolorvalues::BGR || type==imagecolorvalues::HSV);
        color_type = type;
      }

      int getColorType() {
        return color_type;
      }

      uchar* getLower() { return lower;}
      uchar* getUpper() { return upper;}

      /*
      uchar getBMax() { assert(color_type==imagecolorvalues::BGR); return upper[0]; }

      uchar getGMax() { assert(color_type==imagecolorvalues::BGR); return upper[1]; }

      uchar getRMax() { assert(color_type==imagecolorvalues::BGR); return upper[2]; }

      uchar getBMin() { assert(color_type==imagecolorvalues::BGR); return lower[0]; }

      uchar getGMin() { assert(color_type==imagecolorvalues::BGR); return lower[1]; }

      uchar getRMin() { assert(color_type==imagecolorvalues::BGR); return lower[2]; }
      */
      void setBGRMax(uchar b, uchar g, uchar r) { assert(color_type==imagecolorvalues::BGR); lower[0] = b; lower[1] = g; lower[2] = r; }
      void setBGRMin(uchar b, uchar g, uchar r) { assert(color_type==imagecolorvalues::BGR); upper[0] = b; upper[1] = g; upper[2] = r; }
      
      /*
      uchar getHMax() { assert(color_type==imagecolorvalues::HSV); return upper[0]; }

      uchar getSMax() { assert(color_type==imagecolorvalues::HSV); return upper[1]; }

      uchar getVMax() { assert(color_type==imagecolorvalues::HSV); return upper[2]; }

      uchar getHMin() { assert(color_type==imagecolorvalues::HSV); return lower[0]; }

      uchar getSMin() { assert(color_type==imagecolorvalues::HSV); return lower[1]; }

      uchar getVMin() { assert(color_type==imagecolorvalues::HSV); return lower[2]; }
      */
      void setHSVMax(uchar h, uchar s, uchar v) { assert(color_type==imagecolorvalues::HSV); upper[0] = h; upper[1] = s; upper[2] = v; }
      void setHSVMin(uchar h, uchar s, uchar v) { assert(color_type==imagecolorvalues::HSV); lower[0] = h; lower[1] = s; lower[2] = v; }
      
};
#endif