#ifndef IAP_CONTEXT_H
#define IAP_CONTEXT_H

#include <iostream>
#include <opencv2/core.hpp>

#include "convert_bgrhsv.h"
#include "convertnumber.h"
#include "iap_print.h"
#include "imagecolordesc.h"
#include "imagecolormatrices.h"
#include "range.h"

class iap_context {
    public:
        imagecolordesc* desc;

        iap_print* printer;
        convert_bgrhsv* calc;
        convertnumber* convert;

        range* rg;

        imagecolormatrices* mats;

    public:
        iap_context() {
            printer = new iap_print();
            calc = new convert_bgrhsv();
            convert = new convertnumber(); 
            rg = new range();

            desc = new imagecolordesc();
            desc->setPrint(printer);
            desc->setConvertHSV(calc);
            desc->setConvertNum(convert);
            desc->setRange(rg);

            mats = new imagecolormatrices();
        }

        ~iap_context() {
            std::cout << "Destructing iap_context." << std::endl;
            delete printer;
            delete calc;
            delete convert;
            delete rg;
            delete desc;
            delete mats;
        }
};
#endif