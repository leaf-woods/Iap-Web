#include <iostream>
#include "iapcv_env.h"

using namespace std;

iapcv_env* iapcv_env::envInstance = nullptr;
iapcv_env::iapcv_env(){}
iapcv_env::~iapcv_env(){
    delete envInstance;
};

iapcv_env* iapcv_env::getInstance(){
    if (envInstance == NULL){
        //std::lock_guard<std::mutex> lock(mtx);
        //if (singletonInstance == NULL)
            envInstance = new iapcv_env();
    }
    return envInstance;
}

/// TODO Test
void iapcv_env::print() {
    cout << "Print env" << endl;
}

string iapcv_env::getDevTestImgBase() {
    if (DEV_TST_IMGBASE.length() > 0) {
        return DEV_TST_IMGBASE;
    }
    string base;
    DEV_TST_IMGBASE.reserve(49);
    DEV_TST_IMGBASE.append(HOME);
    DEV_TST_IMGBASE.append("/");
    DEV_TST_IMGBASE.append(DEV);
    DEV_TST_IMGBASE.append("/");
    DEV_TST_IMGBASE.append(TEST_IMGDATA_BASE);
    return DEV_TST_IMGBASE;
}