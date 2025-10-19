#include <cassert>
#include <iostream>

#include "fact_sky_init_train.h"
#include "sky_init_train.h"

using namespace std;
int main(int argc, char* argv[]) {
    fact_sky_init_train* ftrain = new fact_sky_init_train();
    sky_init_train* tr1 = ftrain->getSkyTrainInstance();
    sky_init_train* tr2 = ftrain->getSkyTrainInstance();

    cout << "tr1: " << tr1 << endl;
    cout << "tr2: " << tr2 << endl;
    assert(tr1 == tr2);

    delete ftrain;
    return 0;
}