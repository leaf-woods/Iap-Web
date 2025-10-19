#include "fact_sky_init_train.h"

using namespace std;

sky_init_train* fact_sky_init_train::skyTrainInstance = nullptr;
fact_sky_init_train::fact_sky_init_train() {}
fact_sky_init_train::~fact_sky_init_train() {
    delete skyTrainInstance;
}

sky_init_train* fact_sky_init_train::getSkyTrainInstance(){
    if (skyTrainInstance == NULL){
        iapcv_env* env = iapcv_env::getInstance();

        string basePath = env->getDevTestImgBase();
        basePath.append("/img64");
    
        string imgName = "IMG_4585_S_CR_R1_S64_00.JPG";

        skyTrainInstance = new sky_init_train(basePath, imgName);
    }
    return skyTrainInstance;
}

