#ifndef SPAN_NODE_H
#define SPAN_NODE_H
struct span_node {
    // row_no or col_no
    int offset;  
    int type;
    int span[2] = {0, 0};
}; 

class span_constants {
    public:
        static const int ROW = 1000;
        static const int COL = 2000;
};
#endif