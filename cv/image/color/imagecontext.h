#ifndef IMAGECONTEXT_H
#define IMAGECONTEXT_H

#include <iostream>
#include <opencv2/core.hpp>

#include "convert_bgrhsv.h"
#include "convertnumber.h"
#include "iap_print.h"
#include "iapcv_log.h"
#include "imagecolordesc.h"
#include "imagereader.h"
//#include "pixel_comparator.h"
#include "range.h"
//#include "region_builder.h"
//#include "region_evaluator.h"

class imagecontext {
    public:
        iapcv_log* logger;
        imagecolordesc* desc;

        iap_print* printer;
        convert_bgrhsv* calc;
        convertnumber* convert;

        range* rg;

        imagereader* reader;

        /*
        pixel_comparator* compt;
        region_evaluator* evaluator;
        region_builder* builder;
        */

    public:
        imagecontext() {
            logger = new iapcv_log(typeid(this).name());

            printer = new iap_print();
            calc = new convert_bgrhsv();
            convert = new convertnumber(); 
            rg = new range();

            desc = new imagecolordesc();
            desc->setPrint(printer);
            desc->setConvertHSV(calc);
            desc->setConvertNum(convert);
            desc->setRange(rg);

            reader = new imagereader();

            /*
            compt = new pixel_comparator();
            evaluator = new region_evaluator();
            evaluator->setComparator(compt);
            builder = new region_builder();
            builder->setRegionEvaluator(evaluator);
            builder->setPrint(printer);
            */
        }

        ~imagecontext() {
            logger->debug("Destructing imagecontext.");
            delete desc;
            delete rg;
            delete reader;
            //delete builder;
            //delete evaluator;
            //delete compt;
            delete printer;
            delete calc;
            delete convert;
            delete logger;
        }

        iap_print* getPrint() { return printer; }
        convertnumber* getConvertNumber() { return convert; }
        convert_bgrhsv* getConvertBgrToHsv() {  return calc; }
        range* getRange() { return rg; }

        void setLogLevel(int level) { logger->setLevel(level); }
        
        void setImgCtxLogsLevel(int level) { 
            logger->setLevel(level);
            desc->setLogLevel(level);
            reader->setLogLevel(level);
            //region_builder->setLogLevel(level);
        }
};
#endif