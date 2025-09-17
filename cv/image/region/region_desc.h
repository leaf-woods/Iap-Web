#ifndef REGION_DESC_H
#define REGION_DESC_H

#include "imagecolorvalues.h"

enum class RegionDesc { 
  na = imagecolorvalues::NOT_AVAILABLE,

  /*
   * /home/linye020603/iap-web/cv-test/test-data/image/img64/IMG_4585_S_CR_R1_S64_00.JPG
   * sky_init_train.cpp
   */
  sky = 1, cloud = 2, weakCloud = 3,

  black = imagecolorvalues::BLACK, 
  purple = imagecolorvalues::PURPLE,
  blue = imagecolorvalues::BLUE, 
  green = imagecolorvalues::GREEN,
  yellow = imagecolorvalues::YELLOW,
  orange = imagecolorvalues::ORANGE,
  red = imagecolorvalues::RED
};

class region_desc {
    public:
      static std::string toString(RegionDesc desc) {
          switch (desc) {
              case RegionDesc::na:
                  return "NA";
              case RegionDesc::sky:
                  return "SKY";
              case RegionDesc::cloud:
                  return "CLOUD";
              case RegionDesc::weakCloud:
                  return "WEAK CLOUD";
              case RegionDesc::black:
                  return "BLACK";
              case RegionDesc::purple:
                  return "PURPLE";
              case RegionDesc::blue:
                  return "BLUE";
              case RegionDesc::green:
                  return "GREEN";
              case RegionDesc::yellow:
                  return "YELLOW";
              case RegionDesc::orange:
                  return "ORANGE";
              case RegionDesc::red:
                  return "RED";
          break;  
          }
          return nullptr;
      }  
};
#endif