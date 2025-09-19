#include <cassert>
#include <iostream>

#include "imagecolordesc.h"
#include "imagecontext.h"

int main() {
    string imageName = "/home/linye020603/iap-web/cv-test/test-data/image/test-color-band-v.jpg";

    imagecontext* ctx = new imagecontext();
    ctx->setImgCtxLogsLevel(iapcv_log::INFO);

    ctx->desc->setLogLevel(iapcv_log::INFO);

    cout << "Test setDescData" << endl;
    cout << "Use file: " << imageName << endl;
    if (ctx->reader->read_image(false, imageName)) {
        ctx->desc->setDescData(*ctx->reader->getInputImage(), imagecolorvalues::BGR);
        ctx->desc->printMap();
    }
    else {
        cout << "Failed to process image: " << imageName << endl;
    }

    assert(5*350==ctx->desc->countColor(imagecolorvalues::BLACK));
    cout << "Test setDescData: Done." << endl;
    cout << endl;

    // repeat previous action
    cout << "Test setDescData reuse" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getInputImage(), imagecolorvalues::BGR);
    ctx->desc->printMap();
    assert(5*350==ctx->desc->countColor(imagecolorvalues::BLACK));
    cout << "Test setDescData reuse: Done." << endl;
    cout << endl;

    // repeat previous action
    cout << "Test setDescData reuse: change color type" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->setDescData(*ctx->reader->getHsvImage(), imagecolorvalues::HSV);
    ctx->desc->printMap();
    assert(imagecolorvalues::HSV==ctx->desc->getColorType());
    cout << "Test setDescData reuse: change color type Done." << endl;
    cout << endl;

    cout << "Test clear" << endl;
    cout << "Use file: " << imageName << endl;
    ctx->desc->clear();
    ctx->desc->printState();
    cout << "Test clear: Done." << endl;
    cout << endl;

    delete ctx;
    return 0;
}