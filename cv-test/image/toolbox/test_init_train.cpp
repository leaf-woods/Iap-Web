#include "sky_init_train.h"

int main(int argc, char* argv[]) {
    sky_init_train* tr = new sky_init_train();
    tr->test_dist();
    delete tr;
    return 0;
}