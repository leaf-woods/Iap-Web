#include <chrono>
#include <iostream>

#include "absr_explore.h"

using namespace std;

absr_explore::absr_explore() {
    sta = new bool_status(status::NORMAL, false);
}
absr_explore::~absr_explore() {
    //mat = nullptr;
    cols = nullptr;
    rows = nullptr;
    cols_map = nullptr;
    rows_map = nullptr;

    delete sta;
}

void absr_explore::adjustBounds(bounds& b, int begin, int end, const vector<int*>& v) {
    //logger->debug("adjust bounds. begin: ", begin, " end: ", end, " To check in vector: ");
    //printer->printVector(v, 2);

    for (int i=0; i<v.size(); i++) {
        if (v.at(i)[0] > end || v.at(i)[1] < begin) {
            continue;
        }
        if (begin < v.at(i)[0] && v.at(i)[1] <= end) {
            // begin, v.at(i)[0]-1
            b.op = bounds::ADJUSTED;
            b.adjusted[0] = begin;
            b.adjusted[1] = v.at(i)[0] - 1;
            return;
        }
        if (begin >= v.at(i)[0] && end <= v.at(i)[1]) {
            b.op = bounds::SKIP;
            return;
        }
        if (begin >= v.at(i)[0] && end > v.at(i)[1]) {
            // v.at(i)[1]+1, end
            b.op = bounds::ADJUSTED;
            b.adjusted[0] = v.at(i)[1]+1;
            b.adjusted[1] = end;
            return;
        }
        else { /// TODO
            // begin, v.at(i)[0]-1 and v.at(i)+1, end
            b.op = bounds::NO_OP;
            return;
        }
    }
    b.op = bounds::NO_OP;
}

/*
 * Check whether integer n is within any span stored in v.
 * At this moment, elements are unordered in v.
 * If v has a large size and needs to be visited many times,
 * we can use a bstree to handle the scenario.
 */
bool absr_explore::contains(const vector<int*>& v, int n) {
    for (int i=0; i<v.size(); i++) {
        if (v.at(i)[0] <= n && n <= v.at(i)[1]) {
            return true;
        }
    }
    return false;
}

span_node* absr_explore::createSpanNode(int type, int offset, int lower, int upper) {
    span_node* n = new span_node();
    n->type = type;
    n->offset = offset;
    n->span[0] = lower;
    n->span[1] = upper;
    return n;
}

void absr_explore::setLogger(iapcv_log& logger) {
    this->logger = logger;
}

void absr_explore::setRegionEvaluator(region_evaluator& eval) {
    this->evaluator = eval;
}
        
void absr_explore::setRegionDesc(RegionDesc desc){
    this->desc = desc;
}
        
void absr_explore::setRegionPrint(region_print& p){
    this->rpt = p;
}
