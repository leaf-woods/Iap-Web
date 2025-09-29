#include <cassert>

#include "sub_matr.h"

int main(int argc, char* agrv[]) {
    sub_matr* smatr = new sub_matr();

    smatr->setSubMat(0, 0, 32, 32);
    smatr->setUse(true);
    assert(smatr->use());
    assert(0==smatr->getTopRow());
    assert(0==smatr->getLeftCol());
    assert(32==smatr->getSubH());
    assert(32==smatr->getSubW());
    assert(31==smatr->getBottomRow());
    assert(31==smatr->getRightCol());
    
    int* sub_origin = smatr->getSubOriginal();
    int* sub_diag = smatr->getSubDiag();
    assert(0==sub_origin[0] && 0==sub_origin[1]);
    assert(31==sub_diag[0] && 31==sub_diag[1]);

    delete smatr;

    return 0;
}