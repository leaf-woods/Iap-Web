#ifndef CONVERTNUMBER_H
#define CONVERTNUMBER_H

#include <opencv2/core.hpp>

class convertnumber {
    public:
        static const int MAX=16777215; 
    public:
        int getInt(uchar b, uchar g, uchar r);
        uchar getUChar(int n);
        void setBGR(int n, uchar* p_bgr);
};
#endif
