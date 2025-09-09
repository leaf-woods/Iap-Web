#include <cassert>
#include <iostream>

#include "imagecolordesc.h"
#include "imagecontext.h"

int main(int argc, char* argv[]) {
    string imageName = "/home/linye020603/iap-web/cv-test/test-data/image/test-color-band-v.jpg";

    imagecontext* ctx = new imagecontext();
    ctx->setImgCtxLogsLevel(iapcv_log::INFO);

    ctx->desc->setLogLevel(iapcv_log::INFO);

    if (ctx->reader->read_image(false, imageName)) {
        ctx->desc->setColorType(imagecolorvalues::BGR);
        ctx->desc->setDescData(*(ctx->reader->getInputImage()));

        ctx->desc->printMap();
    }
    else {
        cout << "Failed to process image: " << imageName << endl;
    }

    assert(5*350==ctx->desc->countColor(imagecolorvalues::BLACK));
    
    delete ctx;
    return 0;
}