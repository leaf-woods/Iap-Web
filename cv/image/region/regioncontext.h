#ifndef REGION_CONTEXT_H
#define REGION_CONTEXT_H

#include "iapcv_context.h"
#include "pixel_comparator.h"
#include "region_builder.h"
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

    public:
        regioncontext() {
            iap_ctx = new iapcv_context();

            builder = new region_builder();
            eval = new region_evaluator();
            compr = new pixel_comparator();
            rpt = new region_print();
            explore = new region_explore(); 

            eval->setComparator(compr);
            builder->setRegionEvaluator(eval);
            builder->setRegionPrint(rpt);
            builder->setRegionExplore(explore);

            builder->setPrint(*iap_ctx->printer);
            builder->setLogger(*iap_ctx->logger);

            explore->setRegionEvaluator(*eval);
            explore->setLogger(*iap_ctx->logger);
            explore->setRegionPrint(*rpt);
        }

        ~regioncontext() {
            delete builder;
            delete explore;
            delete eval;
            delete compr;
            delete rpt;
            delete iap_ctx;
        }
};
#endif