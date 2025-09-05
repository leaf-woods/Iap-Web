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
#include "range.h"

class imagecontext {
    public:
        iapcv_log* logger;
        imagecolordesc* desc;

        iap_print* printer;
        convert_bgrhsv* calc;
        convertnumber* convert;

        range* rg;

        imagereader* reader;

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
        }

        ~imagecontext() {
            logger->debug("Destructing imagecontext.");
            delete printer;
            delete calc;
            delete convert;
            delete rg;
            delete desc;
            delete reader;
            delete logger;
        }

        void setLogLevel(int level) { logger->setLevel(level); }
        
        void setImgCtxLogsLevel(int level) { 
            logger->setLevel(level);
            desc->setLogLevel(level);
            reader->setLogLevel(level);
        }
};
#endif