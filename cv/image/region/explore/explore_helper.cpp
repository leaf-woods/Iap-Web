#include "explore_helper.h"

using namespace std;

explore_helper::~explore_helper() {
    logger = nullptr;
}

/// TODO Test individually
void explore_helper::adjustBounds(bounds& b, int begin, int end, const vector<int*>& v) {
    logger->ftrace("snsns", "adjust bounds. begin: ", begin, " end: ", end, " To check in vector: ");
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
bool explore_helper::contains(const vector<int*>& v, int n) {
    for (int i=0; i<v.size(); i++) {
        if (v.at(i)[0] <= n && n <= v.at(i)[1]) {
            return true;
        }
    }
    return false;
}

/// TODO We can make it independant of map type, i.e., rows_map or cols_map
bool explore_helper::containsOnMap(int which, const map<int, vector<int*>*>& m, int row, int col) {
    //logger->ftrace("snsn", "Contains on map: row: ", row, " col: " << col);
    if (which == ROW) {
        auto sch = m.find(row);
        assert(sch != m.end());
        return contains(*sch->second, col);
    }
    if (which == COL) {
        auto sch = m.find(col);
        assert(sch != m.end());
        return contains(*sch->second, row);
    }
    logger->error("Invalid map type: ", which);
    return false;
}

span_node* explore_helper::createSpanNode(int type, int offset, int lower, int upper) {
    span_node* n = new span_node();
    n->type = type;
    n->offset = offset;
    n->span[0] = lower;
    n->span[1] = upper;
    return n;
}

void explore_helper::setLogger(iapcv_log* logger) {
    this->logger = logger;
}