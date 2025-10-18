#ifndef PIXEL_COMPARATOR_H
#define PIXEL_COMPARATOR_H

#include <unordered_map>

#include <opencv2/core.hpp>

#include "region_desc.h"

enum class BasicNum {
    emzero_like = 0,
    em127_like = 1,
    em255_like = 2,
    eminvalid 
};

// 
/*
 * https://stackoverflow.com/questions/11367141/how-to-declare-and-initialize-a-static-const-array-as-a-class-member
 * https://stackoverflow.com/questions/8782023/typedef-of-a-multidimensional-array
*/

/*
 * @20250915
 * We define a Basic Color as: a color[b, g, r] where b in [0, 127, 255], g in [0, 127, 255] and r in [0, 127, 255].
 * There are total 27 (each position 3 possibilities and total 3 positions which leads to
 * 3*3*3 combinations) such kind of colors.
 *  
 * We need a typedef of int array of [27][3]. We use such a type to build a lookup table which provides O(1) time 
 * when we get the color key based on basic color [b, g, r]. Otherwise we have to compute the color key either using
 * class convertnumber or manually.
 * 
 * We will check each pixel on the input image to determine whether it is a Basic Color.
 *
 * https://stackoverflow.com/questions/32190494/what-is-the-vec3b-type cv::Vec3b is: vector of 3 byte entries.
 * We don't use cv::Vec3b as the lookup table is fixed length even we can add more color on the lookup table.
 * 
 * Not able to figure out how to use static int array in this case. We use singleton pattern instead.
 */
//typedef int BasicColor [][3][3]; 

class pixel_comparator {
    private:
      static const int INVALID_KEY = -1;
      // Automatically allocated array cannot be deleted.
      static int basic_color_table[3][3][3]; 

      static std::unordered_map<int, int> color_map;

    private:
      static void setupTable();

      BasicNum getBasicNum(unsigned char c);

    public:
      pixel_comparator();

      RegionDesc compareValue_00(const cv::Vec3b& color);
      RegionDesc contents_sky_cloud_ma(const cv::Vec3b& color);

      bool compareNeighbor(const cv::Vec3b& color1, const cv::Vec3b& color2);
      bool compareStart(const cv::Vec3b& startColor, const cv::Vec3b& color2); 

      bool isColor(int which, const cv::Vec3b& color);
      bool isSky_ma(int which, const cv::Vec3b& color);
      bool equals(const cv::Vec3b& color1, const cv::Vec3b& color2) ;
      int getBasicColorKey(unsigned char b, unsigned char g, unsigned char r);

      bool similar(int which, const cv::Vec3b& color1, const cv::Vec3b& color2); 
};
#endif