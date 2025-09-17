#ifndef IAP_PRINT_H
#define IAP_PRINT_H

#include <iostream>
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
        void printPixelColor(size_t channel, uchar* array);
        void printPixelColor(cv::Vec<unsigned char, 3> entry, std::string type);
        void printPixelIndex(size_t dim, int* array);
        void printKV(int key, int value);

        std::string formattedNumToStr(int num);
};

#endif