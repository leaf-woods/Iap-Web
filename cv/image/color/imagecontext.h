#ifndef IMAGECONTEXT_H
#define IMAGECONTEXT_H

#include <iostream>
#include <opencv2/core.hpp>

#include "convert_bgrhsv.h"
#include "convertnumber.h"
#include "iap_print.h"
#include "iapcv_context.h"
#include "iapcv_log.h"
#include "imagecolordesc.h"
#include "imagereader.h"
//#include "pixel_comparator.h"
#include "range.h"

class imagecontext {
    public:
        iapcv_context* iap_ctx;
        imagecolordesc* desc;
        imagereader* reader;
        range* rg;

    public:
        imagecontext() {
            iap_ctx = new iapcv_context();
        
            rg = new range();

            desc = new imagecolordesc();
            desc->setPrint(iap_ctx->printer);
            desc->setConvertHSV(iap_ctx->convertC);
            desc->setConvertNum(iap_ctx->convertN);
            desc->setRange(rg);
            desc->setLogger(iap_ctx->logger);

            reader = new imagereader();
            reader->setLogger(iap_ctx->logger);
        }

        ~imagecontext() {
            iap_ctx->logger->debug("Destructing imagecontext.");
            delete desc;
            delete rg;
            delete reader;
           
            delete iap_ctx;
        }

        /*
        convertnumber* getConvertNumber() { return convert; }
        convert_bgrhsv* getConvertBgrToHsv() {  return calc; }
        range* getRange() { return rg; }
*/
        void setLogLevel(int level) { iap_ctx->logger->setLevel(level); }
        
        /*
        void setImgCtxLogsLevel(int level) { 
            logger->setLevel(level);
            desc->setLogLevel(level);
            reader->setLogLevel(level);
        }
            */
};
#endif