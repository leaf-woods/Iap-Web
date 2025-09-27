#ifndef IAPCV_CONTEXT_H
#define IAPCV_CONTEXT_H

#include <iostream>

#include "iapcv_log.h"
#include "iap_print.h"
#include "convert_bgrhsv.h"
#include "convertnumber.h"


class iapcv_context {
    public:
        iap_print* printer;
        convert_bgrhsv* convertC;
        convertnumber* convertN;

        // Single threaded environment
        iapcv_log* logger;

    public:
        iapcv_context() {
            printer = new iap_print();
            convertC = new convert_bgrhsv();
            convertN = new convertnumber(); 
            logger = new iapcv_log(typeid(this).name());
        }

        ~iapcv_context() {
            delete printer;
            delete convertC;
            delete convertN;
            delete logger; 
        }
};
#endif