#ifndef REGION_EVALUATOR_H
#define REGION_EVALUATOR_H

#include <opencv2/core.hpp>

#include "eval_params.h"
#include "eval_policy.h"
#include "pixel_comparator.h"
#include "status.h"

/*
 * @20250916
 * At this moment, we can only evaluate color.
 * sky_init_train is for learning.
 */
class region_evaluator {
    private:
        pixel_comparator* comparator;

    private:
        void evaluateDesc(RegionDesc desc, cv::Vec3b color, bool_status& sta);

    public:
      region_evaluator();
      ~region_evaluator();

      void evaluateInBound(eval_policy& po, cv::Vec3b color, bool_status& sta);
      void evaluate(eval_policy& po, eval_params& pm,  bool_status& sta);
      void setComparator(pixel_comparator* comparator);

      /*
       * @20250916 We keep this for learning purpose.
       */
      void evaluate(RegionDesc desc, cv::Vec3b color1, cv::Vec3b color2, bool_status& sta);
};

#endif