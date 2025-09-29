#ifndef MATRIX_BOUNDS_H
#define MATRIX_BOUNDS_H

#include "sub_matr.h"

class matrix_bounds {
    private:
        sub_matr* smatr;
        int OW;
        int OH;

    public:
        matrix_bounds();
        ~matrix_bounds();

        bool isSubMatrix();
        int getH();
        int getW();
        int top();
        int bottom();
        int left();
        int right();
        void setOH(int H);
        void setOW(int W);
        void setSubMatrix(int r, int c, int num_rs, int num_cs);
        void useMatrix();

        void print();
};
#endif