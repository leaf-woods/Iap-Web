#include <iostream>

#include "matrix_bounds.h"

using namespace std;
matrix_bounds::matrix_bounds() {
    smatr = new sub_matr();
}

matrix_bounds::~matrix_bounds() {
    delete smatr;
}

bool matrix_bounds::isSubMatrix() {
    return smatr->use();
}

int matrix_bounds::getH() {
    return OH;
}

int matrix_bounds::getW() {
    return OW;
}

void matrix_bounds::setOH(int H) {
    OH = H;
}

void matrix_bounds::setOW(int W) {
    OW = W;
}

void matrix_bounds::setSubMatrix(int r, int c, int num_rs, int num_cs) {
    smatr->setSubMat(r, c, num_rs, num_cs);
    smatr->setUse(true);
    OH = 0;
    OW = 0;
}

void matrix_bounds::useMatrix() {
    smatr->setUse(false);
}

int matrix_bounds::top() {
    if (smatr->use()) {
        return smatr->getTopRow();
    }
    else {
        return 0;
    }
}

int matrix_bounds::bottom() {
    if (smatr->use()) {
        return smatr->getBottomRow();
    }
    else {
        return OH-1;
    }
}

int matrix_bounds::left() {
    if (smatr->use()) {
        return smatr->getLeftCol();
    }
    else {
        return 0;
    }
}

int matrix_bounds::right() {
    if (smatr->use()) {
        return smatr->getRightCol();
    }
    else {
        return OW-1;
    }
}

void matrix_bounds::print() {
    cout << "Print matrix_bounds: " ;
    cout << "H: " << OH << " W: " << OW << " top: " << top() << " bottom: " << bottom() << " left: " << left() << " right: " << right() << endl;
}
