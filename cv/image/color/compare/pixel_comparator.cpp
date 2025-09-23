#include "imagecolorvalues.h"
#include "pixel_comparator.h"
#include "region_desc.h"


pixel_comparator::pixel_comparator() {
    setupTable();
}

bool pixel_comparator::similar(int which, const cv::Vec3b& color1, const cv::Vec3b& color2) {
    if (which == static_cast<int>(RegionDesc::sky)) {
        return color1[0]==color2[0];
    }
    return false;
}

bool pixel_comparator::isSky(int which, const cv::Vec3b& color) {
    if (which == static_cast<int>(RegionDesc::sky)) {
        return color[0]==1;
    }
    return false;
}

/*
 * /home/linye020603/iap-web/cv-test/test-data/image/test-color-band-v.jpg
 */
bool pixel_comparator::isColor(int which, const cv::Vec3b& color) {
    switch (which) {
      case imagecolorvalues::BLACK:
        return color[0]<=imagecolorvalues::DELTA && color[1]<=imagecolorvalues::DELTA && color[2]<=imagecolorvalues::DELTA;

      case imagecolorvalues::PURPLE:  // 127, 0, 255  R, G, B
        return (color[2]<=127+imagecolorvalues::M_DELTA || color[2]>=127-imagecolorvalues::M_DELTA) \
               && color[1]<=imagecolorvalues::DELTA && color[0]>=255-imagecolorvalues::DELTA;

      case imagecolorvalues::BLUE:  // 0, 0, 255
        return color[2]<=imagecolorvalues::DELTA  \
               && color[1]<=imagecolorvalues::DELTA && color[0]>=255-imagecolorvalues::DELTA;

      case imagecolorvalues::GREEN:  // 0, 255, 0
        return color[2]<=imagecolorvalues::DELTA  \
               && color[1]>=255-imagecolorvalues::DELTA && color[0]<=imagecolorvalues::DELTA;

      case imagecolorvalues::L50_GREEN:  // 127, 255, 0
        return color[2]>=127-imagecolorvalues::M_DELTA && color[2]<=127+imagecolorvalues::M_DELTA \
               && color[1]>=255-imagecolorvalues::DELTA && color[0]<=imagecolorvalues::DELTA;

      case imagecolorvalues::YELLOW:  // 255, 255, 0
        return color[2]>=255-imagecolorvalues::DELTA  \
               && color[1]>=255-imagecolorvalues::DELTA && color[0]<=imagecolorvalues::DELTA;

      case imagecolorvalues::L75_YELLOW:  // 255, 255, 127
        return color[2]>=255-imagecolorvalues::DELTA  \
               && color[1]>=255-imagecolorvalues::DELTA && \
               color[0]>=127-imagecolorvalues::M_DELTA && color[0]<=127 + imagecolorvalues::M_DELTA;

      case imagecolorvalues::ORANGE:  // 255, 127, 0
        return color[2]>=255-imagecolorvalues::DELTA \
               && (color[1]<=127+imagecolorvalues::M_DELTA || color[1]>=127-imagecolorvalues::M_DELTA) \
               && color[0]<=imagecolorvalues::DELTA;

      case imagecolorvalues::RED:  // 255, 0, 0
        return color[2]>=255-imagecolorvalues::DELTA  \
               && color[1]<=imagecolorvalues::DELTA && color[0]<=imagecolorvalues::DELTA;

    break;
    }
    return false;
}

// https://stackoverflow.com/questions/39243121/embedded-c-choice-between-switch-case-hashtable
int pixel_comparator::getBasicColorKey(unsigned char b, unsigned char g, unsigned char r) {
    BasicNum b_color = getBasicNum(b);
    BasicNum g_color = getBasicNum(g);
    BasicNum r_color = getBasicNum(r);
    if (b_color == BasicNum::eninvalid || g_color == BasicNum::eninvalid || r_color == BasicNum::eninvalid) {
        return imagecolorvalues::NOT_AVAILABLE;
    }
    return basic_color_table[static_cast<int>(b_color)][static_cast<int>(g_color)][static_cast<int>(r_color)];
}

BasicNum pixel_comparator::getBasicNum(unsigned char c) {
    if (c <= imagecolorvalues::DELTA) {
        return BasicNum::enzero_like; // 2^0 -1
    }
    if (c >= 127-imagecolorvalues::M_DELTA && c <= 127+imagecolorvalues::M_DELTA) {
        return BasicNum::en127_like; // 2^7 -1
    }
    if (c >= 255-imagecolorvalues::DELTA) {
        return BasicNum::en255_like; // 2^8 - 1
    }
    return BasicNum::eninvalid;
}

void pixel_comparator::setupTable() {
          //(b<<16) + (g<<8) + r
          unsigned char b=0; 
          unsigned char g=0;
          unsigned char r=0;

          int val_b = 0; int val_g = 0; int val_r = 0;
          for ( b=0; b<3; b++) {
            for ( g=0; g<3; g++) {
              for ( r=0; r<3; r++) {
                if (b == 0) {
                  val_b = 0;
                }
                else if (b == 1) {
                  val_b = 127;
                }
                else {
                  val_b = 255;
                }

                if (g == 0) {
                  val_g = 0;
                }
                else if (g == 1) {
                  val_g = 127;
                }
                else {
                  val_g = 255;
                }

                if (r == 0) {
                  val_r = 0;
                }
                else if (r == 1) {
                  val_r = 127;
                }
                else {
                  val_r = 255;
                }  
                basic_color_table[b][g][r] =  (val_b<<16) + (val_g<<8) + val_r;
            }
          }
        }
      }