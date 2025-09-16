#include <chrono>

#include "sky.h"
#include "status.h"

using namespace std;

sky::sky() {
    logger = new iapcv_log(typeid(this).name());
}

sky::~sky() {
    blue = nullptr;
    ctx = nullptr;

    delete logger;
    logger = nullptr;
}

void sky::setBlueSpace(blue_space* blue) {
    this->blue = blue;
}

void sky::setImageContext(imagecontext* ctx) {
    this->ctx = ctx;
}

void sky::setLogLevel(int level) {
    logger->setLevel(level);
}

bool_status* sky::isSky(string imageName) {
    auto t1 = chrono::high_resolution_clock::now();

    if (! ctx->reader->read_image(false, imageName)) {
        return new bool_status(status::ERROR, false, "Cannot proceed with image: " + imageName);
    }
    ctx->desc->setColorType(imagecolorvalues::HSV);
    ctx->desc->setDescData(*(ctx->reader->getHsvImage()));
    ctx->desc->setHsvTree(hsvtree::HUE);
    auto t2 = chrono::high_resolution_clock::now();
    logger->info("Image data collection time: ", (int)chrono::duration_cast<chrono::microseconds>(t2-t1).count());
    
    vector<int>* vh = new vector<int>();
    /// TODO: we can use imagecolordesc: BH[256] directly. Performance is
    /// a little slower since for some of test images, hsvtree has size under 10.
    ctx->desc->getAllHue(vh);
    logger->debug("HSV tree size: ", vh->size());
    int count = 0;
    for (auto it=(*vh).begin(); it!=(*vh).end(); it++) {
        if ( blue->isBlue(*it) ) {
            count++;
        }
    }
    double blue_percent = count/(ctx->desc->getImageSize());
    bool result = blue_percent>=0.5? true : false;
    
    logger->debug("Test blue: ", blue_percent);
    logger->info("Is sky:", (result ? "true" : "false"));
    auto t3 = chrono::high_resolution_clock::now();
    logger->info("Total process time: ", (int)chrono::duration_cast<chrono::microseconds>(t3-t1).count());
    
    delete vh;
    return new bool_status(status::NORMAL, result);
}