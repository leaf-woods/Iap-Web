#include "iapcv_env.h"
#include "sky_init_train.h"

using namespace std;
int main(int argc, char* argv[]) {
    iapcv_env* env = iapcv_env::getInstance();

    string basePath = env->getDevTestImgBase();
    basePath.append("/img64");
    
    string imgName = "IMG_4585_S_CR_R1_S64_00.JPG";

    sky_init_train* tr = new sky_init_train(basePath, imgName);
    
    tr->test_dist();
    delete tr;
    
    return 0;
}