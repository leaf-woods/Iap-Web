#include "region.h"
#include "sky_init_train.h"

int main(int argc, char* argv[]) {
    sky_init_train* tr = new sky_init_train();
    region* reg = new region();
    
    // Begin to test.
    /*
    reg->get_col_span(*(tr->getMatrix()), 0, 0);

    reg->get_row_span(*(tr->getMatrix()), 0, 0);

    reg->get_col_span(*(tr->getMatrix()), 15, 15);

    reg->get_row_span(*(tr->getMatrix()), 15, 15);

    reg->get_col_span(*(tr->getMatrix()), 9, 2);

    reg->get_row_span(*(tr->getMatrix()), 9, 2);
    */
    reg->explore(*(tr->getMatrix()), 0, 0);

    delete tr;
    delete reg;
    return 0;
}