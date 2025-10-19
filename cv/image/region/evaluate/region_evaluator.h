#ifndef REGION_EVALUATOR_H
#define REGION_EVALUATOR_H

#include <opencv2/core.hpp>

#include "eval_params.h"
#include "eval_policy.h"
#include "iap_print.h"
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

        iap_print* printer;

    private:
        void evaluateColorValue_00(eval_params& pm, bool_status& sta);
        void evaluateSimilarBase_00(eval_params& pm, bool_status& sta);
        void setError(bool_status& sta, std::string msg);

    public:
      region_evaluator();
      ~region_evaluator();

      bool equals(cv::Vec3b color1, cv::Vec3b color2);
      void evaluate(eval_policy& po, eval_params& pm,  bool_status& sta);
      void evaluate(RegionDesc desc, cv::Vec3b color, bool_status& sta);
      RegionDesc evaluatePixelColor(eval_policy& po, cv::Vec3b color);
      void setComparator(pixel_comparator* comparator);

      /*
       * @20250916 We keep this for learning purpose.
       */
      void evaluate(RegionDesc desc, cv::Vec3b color1, cv::Vec3b color2, bool_status& sta);
      
      void setPrint(iap_print* p);
};

#endif