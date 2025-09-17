#ifndef REGION_EVALUATOR_H
#define REGION_EVALUATOR_H

#include <opencv2/core.hpp>

#include "pixel_comparator.h"
#include "region_desc.h"
#include "status.h"

/*
 * @20250916
 * At this moment, we can only evaluate color.
 * sky_init_train is for learning.
 */
class region_evaluator {
    private:
        pixel_comparator* comparator;

    public:
      region_evaluator();
      ~region_evaluator();

      void evaluate(RegionDesc desc, cv::Vec3b color, bool_status& sta);
      void setComparator(pixel_comparator* comparator);

      /*
       * @20250916 We keep this for learning purpose.
       */
      void evaluate(RegionDesc desc, cv::Vec3b color1, cv::Vec3b color2, bool_status& sta);
};

#endif