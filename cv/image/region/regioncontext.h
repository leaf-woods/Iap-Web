#ifndef REGION_CONTEXT_H
#define REGION_CONTEXT_H

#include "explore_helper.h"
#include "get_stddev.h"
#include "iapcv_context.h"
#include "matrix_bounds.h"
#include "pixel_comparator.h"
#include "region_builder.h"
#include "region_colors_provider.h"
#include "region_evaluator.h"
#include "region_explore.h"
#include "region_print.h"

class regioncontext {
    private:
        iapcv_context* iap_ctx;

    public:
        region_builder* builder;
        region_evaluator* eval;
        pixel_comparator* compr;
        region_explore* explore;
        region_print* rpt;
        matrix_bounds* mbounds;
        region_colors_provider* prov;
        get_stddev* stddev;
        explore_helper* helper;

    public:
        regioncontext() {
            iap_ctx = new iapcv_context();

            builder = new region_builder();
            mbounds = new matrix_bounds();
            eval = new region_evaluator();
            compr = new pixel_comparator();
            rpt = new region_print();
            explore = new region_explore(); 
            prov = new region_colors_provider();
            stddev = new get_stddev();
            helper = new explore_helper();

            helper->setLogger(iap_ctx->logger);

            prov->setLogger(iap_ctx->logger);
            stddev->setLogger(iap_ctx->logger);

            eval->setComparator(compr);
            eval->setPrint(iap_ctx->printer);
            
            builder->setRegionColorProvider(prov);
            builder->setRegionEvaluator(eval);
            builder->setRegionExplore(explore);
            builder->setRegionPrint(rpt);
            
            builder->setMatrixBounds(mbounds);

            builder->setPrint(iap_ctx->printer);
            builder->setLogger(iap_ctx->logger);

            explore->setRegionEvaluator(eval);
            explore->setLogger(iap_ctx->logger);
            explore->setRegionPrint(rpt);
            explore->setMatrixBounds(mbounds);
            explore->setExploreHelper(helper);
        }

        ~regioncontext() {
            delete explore;
            delete builder;
            delete mbounds;
            delete eval;
            delete compr;
            delete rpt;
            delete prov;
            delete stddev;
            delete helper;
            delete iap_ctx;
        }
};
#endif