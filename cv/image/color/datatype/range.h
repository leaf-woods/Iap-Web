#ifndef RANGE_H
#define RANGE_H

#include <cassert>

#include <opencv2/core.hpp>

#include "iclearable.h"
#include "imagecolorvalues.h"

class range : public iclearable {
    private:
      ColorType color_type;

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

      void setColorType(ColorType type) {
        assert(type==ColorType::BGR || type==ColorType::HSV);
        color_type = type;
      }

      ColorType getColorType() {
        return color_type;
      }

      uchar* getLower() { return lower;}
      uchar* getUpper() { return upper;}

      void setBGRMax(uchar b, uchar g, uchar r) { assert(color_type==ColorType::BGR); lower[0] = b; lower[1] = g; lower[2] = r; }
      void setBGRMin(uchar b, uchar g, uchar r) { assert(color_type==ColorType::BGR); upper[0] = b; upper[1] = g; upper[2] = r; }
      
      void setHSVMax(uchar h, uchar s, uchar v) { assert(color_type==ColorType::HSV); upper[0] = h; upper[1] = s; upper[2] = v; }
      void setHSVMin(uchar h, uchar s, uchar v) { assert(color_type==ColorType::HSV); lower[0] = h; lower[1] = s; lower[2] = v; }
      
};
#endif