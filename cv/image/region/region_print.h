#ifndef REGION_PRINT_H
#define REGION_PRINT_H

#include <deque>
#include <map>
#include <vector>

#include "border_pixel_diff_node.h"
#include "span_node.h"

class region_print {
    public:
        void printMap(std::string which, const std::map<int, std::vector<int*>*>& m);
        void printQueue(std::string which, const std::deque<span_node*>& q);
        void printSpan(const span_node& sp);

        void printBorderPixelsDiff(const std::vector<border_pixel_diff_node*>& bv);
};
#endif