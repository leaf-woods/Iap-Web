#include <cassert>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sys/stat.h>

#include "blue_space.h"
#include "imagecontext.h"
#include "sky.h"

using namespace std;

//https://stackoverflow.com/questions/229012/getting-absolute-path-of-a-file
//https://stackoverflow.com/questions/13294067/how-to-convert-string-to-char-array-in-c
string getAbsPath(const string& fname) {
    char filename[1024];
    strcpy(filename, fname.c_str());

    // Only works when filename exists, otherwise exception thrown.
    char* path = realpath(filename, NULL);
    if(path == NULL){
        printf("cannot find file with name[%s]\n", filename);
        return nullptr;
    } 
   
    //printf("path[%s]\n", path);
    string p = string(path);
    free(path);
    return p;
}

inline bool exists(const string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

/*
 * User case:
 * ./main fn (relative)
 * ./main fn (absolute)
 */
int main(int argc, char* argv[]) {

    string exec_path = getAbsPath(argv[0]);
    //cout << "path: " << exec_path << endl;

    size_t found = exec_path.find_last_of("/");
    string exec_base = exec_path.substr(0, found);
    //exec_base: /home/linye020603/iap-web/cv
    //cout << "Use base: " << exec_base << endl;

    /*
     * Project requires two directories: cv and cv-test.
     */
    // Manually setup cv-test
    string test_base = exec_base + "-test/";
    string test_base_data = test_base + "test-data/";

    string fname;

    if (argc > 2) {
        cout << "Input image name." << endl;
        return 1;
    }
    if (argc == 2) {
        fname = argv[1];
        if (exists(fname)) {
            string path = getAbsPath(fname); 
            cout << "Use file: " << path << endl;
        }
        else  {
            cout << "File: " << exec_base << "/" << fname << " does not exist." << endl;
            return 1;
        }
    }
    else {
        //fname = test_base_data + "image/img64/IMG_4585_S_CR_R1_S64_11.JPG";
        //fname = test_base_data + "image/IMG_4585.JPG";
        fname = test_base_data + "image/test-color-band-v.jpg";
        cout << "fname: " << fname << endl;
        assert(exists(fname));
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

    bool_status* sta = sk->isSky(fname);
    if (!sta->isNormal()) {
        cout << "Status: " << sta->getMsg()<< endl;
    }
    
    cout << "Done." << endl;
    delete sta;
    delete blue;
    delete ctx;
    delete sk;
    
    return 0;
}

