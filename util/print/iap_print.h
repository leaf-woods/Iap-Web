#ifndef IAP_PRINT_H
#define IAP_PRINT_H

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core.hpp>

class iap_print {
    public:
        /*
         * @20250821
         * We handle printVector() for hsvtree node std::vector<uchar*>* vecHsv 
         * and colorvaluetree node std::vector<int>* keys 
         */
        
        void printVector(std::vector<uchar*>* v);
        void printVector(std::vector<int>* v);
        void printPixelColor(uchar* array);
};

#endif
