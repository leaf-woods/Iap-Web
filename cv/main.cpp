#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include "blue_space.h"
#include "imagecontext.h"
#include "sky.h"

using namespace std;

inline bool exists(const string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

int main(int argc, char* argv[]) {
    string fname;

    if (argc > 2) {
        cout << "Input image name." << endl;
        return 1;
    }
    if (argc == 2) {
        fname = argv[1];
        cout << "Use file: " << fname << endl;
        if (!exists(fname)) {
            cout << "File: " << fname << " does not exist." << endl;
            string exec_name = argv[0];
            size_t found = exec_name.find_last_of("/");
            string fn;
            if (fname.find_first_of("/")==0) {
                fn = exec_name.substr(0, found) + fname;
            }
            else {
                fn = exec_name.substr(0, found+1) + fname;
            }
             
            if (!exists(fn)) {
                cout << "Retried. File: " << fn << " does not exist." << endl;
                return 1;
            }
            fname = fn;
        }
    }
    else {
        fname = "/home/linye020603/iap-web/cv/test/image/data/img64/IMG_4585_S_CR_R1_S64_11.JPG";
        //fname = "/home/linye020603/iap-web/cv/test/image/data/IMG_4585.JPG";
    }
   
    cout << "IAP-CV" << endl;
    cout << "Given an input image, it detects whether the image is taken focus on sky. " << endl;
    cout << endl;

    sky* sk = new sky();
    blue_space* blue = new blue_space();
    imagecontext* ctx = new imagecontext();
    ctx->setImgCtxLogsLevel(iapcv_log::INFO);

    sk->setBlueSpace(blue);
    sk->setImageContext(ctx);
    sk->setLogLevel(iapcv_log::INFO);

    b_status* sta = sk->isSky(fname);
    if (!sta->isOK()) {
        cout << "Status: " << sta->getMsg()<< endl;
    }
    
    cout << "Done." << endl;
    delete sta;
    delete blue;
    delete ctx;
    delete sk;
    
    return 0;
}