#include <cstdlib>
#include <iostream>

#include "imagecolorvalues.h"
#include "pixel_comparator.h"

using namespace std;

/*
 * size: 341
Info: Total process time:  8606
Debug: mean: [  108.815  ,  165.425  ,  145.789  ] 
Debug: variance: [  0.151061  ,  42.3981  ,  2.90235  ] 
Debug: std dev: [  0.388666  ,  6.51138  ,  1.70363  ] 

size: 104
Info: Total process time:  3746
Debug: mean: [  108.99  ,  163.885  ,  145.846  ] 
Debug: variance: [  0.00961538  ,  6.35549  ,  2.79164  ] 
Debug: std dev: [  0.0980581  ,  2.52101  ,  1.67082  ] 
[109, 167, 142, 109, 165, 144, 109, 165, 144, 109, 166, 143, 109, 167, 145, 109, 166, 146, 109, 165, 147, 109, 165, 147, 109, 166, 146, 109, 164, 148, 109, 162, 146, 109, 164, 145, 109, 160, 145, 109, 158, 147, 109, 157, 148, 109, 157, 148, 108, 159, 146, 108, 160, 145, 108, 160, 145, 108, 161, 144, 109, 164, 145, 109, 162, 146, 108, 165, 145, 108, 168, 143, 109, 168, 146, 109, 169, 145, 109, 175, 146, 109, 176, 145, 109, 177, 144, 109, 177, 144, 109, 178, 143, 109, 178, 143]

 */
unordered_map<int, int> pixel_comparator::color_map = { {0, imagecolorvalues::BLACK}, 
                                                        {8323327, imagecolorvalues::PURPLE}, 
                                                        {255, imagecolorvalues::BLUE}, 
                                                        {65280, imagecolorvalues::GREEN},
                                                        {65407, imagecolorvalues::L50_GREEN},
                                                        {16776960, imagecolorvalues::YELLOW},
                                                        {8388607, imagecolorvalues::L75_YELLOW},
                                                        {16744192, imagecolorvalues::ORANGE},
                                                        {16711680, imagecolorvalues::RED} };
 
                                                        
int pixel_comparator::basic_color_table[3][3][3] = {imagecolorvalues::INVALID_KEY};
pixel_comparator::pixel_comparator() {
    if (basic_color_table[0][0][0] == imagecolorvalues::INVALID_KEY) {
        setupTable();
    }
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

bool pixel_comparator::similar(int which, const cv::Vec3b& color1, const cv::Vec3b& color2) {
    if (which == static_cast<int>(RegionDesc::sky)) {
        return color1[0]==color2[0];
    }
    return false;
}

/**
 * Compare color 1 and color 2 that are neighbors
 */
bool pixel_comparator::compareNeighbor(const cv::Vec3b& color1, const cv::Vec3b& color2) {  
    int c1_s = static_cast<int>(color1[1]);
    int c1_v = static_cast<int>(color1[2]);
  
    int c2_s = static_cast<int>(color2[1]);
    int c2_v = static_cast<int>(color2[2]);

    int delta_s = c1_s - c2_s;
    int delta_v = c1_v - c2_v;
    if (delta_s >= 0 && delta_s <= 2 && delta_v <=0 && delta_v >= -2 ) {
       return true;
    }
    if (delta_s <= 0 && delta_s >= -2 && delta_v >=0 && delta_v <= 2 ) {
       return true;
    }
    return false;
} 

bool pixel_comparator::compareStart(const cv::Vec3b& startColor, const cv::Vec3b& color2) {
    int c1_h = static_cast<int>(startColor[0]);
    int c1_s = static_cast<int>(startColor[1]);
  
    int c2_h = static_cast<int>(color2[0]);
    int c2_s = static_cast<int>(color2[1]);

    // _00.JPG, Row 0 (0, 0) and (0, 12) do not follow. But they are both on region of sky_init_train.
    if (abs(c1_h - c2_h) <= 1 && abs(c1_s - c2_s) <= 5) {
        return true;
    }

    // row 0 col 11 and col 12: 109, 164, 145, 109, 160, 145 
    // row 2 col 16 and col 17: 108, 160, 145, 108, 158, 147 weak cloud

    // row 1 col 11 and col 12: 109, 164, 145, 109, 159, 146
    return false;
}

/*
 * testBorder, testCloud
 * Sky: S > 160,  140 < V < 150 
 * Cloud: S < 140, V > 155
 */
RegionDesc pixel_comparator::compareValue_00(const cv::Vec3b& color) {
    if (color[1] > 160 && color[2] > 140 && color[2] < 150) {
        return RegionDesc::sky;
    }
    if (color[1] < 140 && color[2] > 155) {
        return RegionDesc::cloud;
    }
    return RegionDesc::na;
}

bool pixel_comparator::isSky_ma(int which, const cv::Vec3b& color) {
    if (which == static_cast<int>(RegionDesc::sky)) {
        return static_cast<int>(color[0])==1;
    }
    return false;
}

RegionDesc pixel_comparator::contents_sky_cloud_ma(const cv::Vec3b& color) {
  //cout << "Color: " << static_cast<int>(color[0]) << " , " << static_cast<int>(color[1]) << " , " << static_cast<int>(color[2]) << endl; 
    if (static_cast<int>(color[0]) == 1) {
        return RegionDesc::sky;
    }
    // return color[1] == 1: all cloud including weak.
    if (static_cast<int>(color[1]) == 1 ) {
        if (static_cast<int>(color[2]) == 0) {
            return RegionDesc::cloud;
        }
        else if (static_cast<int>(color[2]) == 1) {
            return RegionDesc::weakCloud;
        }
    }
    return RegionDesc::na;
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

bool pixel_comparator::equals(const cv::Vec3b& color1, const cv::Vec3b& color2) {
    return color1[0]==color2[0] && color1[1]==color2[1] && color1[2]==color2[2];
}

// https://stackoverflow.com/questions/39243121/embedded-c-choice-between-switch-case-hashtable
int pixel_comparator::getBasicColorKey(unsigned char b, unsigned char g, unsigned char r) {
    BasicNum b_color = getBasicNum(b);
    BasicNum g_color = getBasicNum(g);
    BasicNum r_color = getBasicNum(r);
    if (b_color == BasicNum::eminvalid || g_color == BasicNum::eminvalid || r_color == BasicNum::eminvalid) {
        return imagecolorvalues::INVALID_KEY;
    }
    return basic_color_table[static_cast<int>(b_color)][static_cast<int>(g_color)][static_cast<int>(r_color)];
}

BasicNum pixel_comparator::getBasicNum(unsigned char c) {
    if (c <= imagecolorvalues::DELTA) {
        return BasicNum::emzero_like; // 2^0 -1
    }
    if (c >= 127-imagecolorvalues::M_DELTA && c <= 127+imagecolorvalues::M_DELTA) {
        return BasicNum::em127_like; // 2^7 -1
    }
    if (c >= 255-imagecolorvalues::DELTA) {
        return BasicNum::em255_like; // 2^8 - 1
    }
    return BasicNum::eminvalid;
}

int pixel_comparator::getColor(cv::Vec3b color) {
    int key = getBasicColorKey(color[0], color[1], color[2]);
    if (key == imagecolorvalues::INVALID_KEY) {
        return imagecolorvalues::NOT_AVAILABLE;
    }
    auto search = color_map.find(key);
    if (search == color_map.end()) {
        return imagecolorvalues::NOT_AVAILABLE;   
    }
    return search->second;   
}