#include "abstract_explore.h"

abstract_explore::~abstract_explore() {
    cols = nullptr;
    rows = nullptr;
    cols_map = nullptr;
    rows_map = nullptr; 
     
    dv = nullptr;
    helper = nullptr;
    logger = nullptr;
}

void abstract_explore::get_col_span(const cv::Mat& mat, int r, int c) {
    int top = get_top(mat, r, c); 
    assert(top != INVALID);
    int bottom = get_bottom(mat, r, c);
    assert(bottom != INVALID);
    // @20251012 At this moment we still need to manually debug using these two lines.
    //logger->debug("top: ", top);
    //logger->debug("bottom: ", bottom);
    
    // we can assert
    cols->push_back(helper->createSpanNode(explore_helper::COL, c, top, bottom));
}

void abstract_explore::get_row_span(const cv::Mat& mat, int r, int c) {
    int left = get_left(mat, r, c);
    assert(left != INVALID);
    int right = get_right(mat, r, c);
    assert(right != INVALID);
    //logger->debug("left: ", left);
    //logger->debug("right: ", right);
    // we can assert
    assert(left<=c && right>=c);
    rows->push_back(helper->createSpanNode(explore_helper::ROW, r, left, right));
}

/*
 * Calculate and create a set of col spans.
 */
void abstract_explore::explore_hort(const cv::Mat& mat, const span_node& row_sp) {
    int begin = row_sp.span[0];
    int end = row_sp.span[1];

    //logger->trace_inline("Explore hort: ");
    //rpt->printSpan(row_sp);

    if (row_sp.offset > 0) {
        auto sch = rows_map->find(row_sp.offset - 1);
        if (sch != rows_map->end()) {
            bounds* b = new bounds(); 
            helper->adjustBounds(*b, begin, end, *sch->second);
            
            int op = b->op;
            if (op == bounds::ADJUSTED) {
                if (begin != b->adjusted[0]) {
                    begin = b->adjusted[0];
                }
                if (end != b->adjusted[1]) {
                    end = b->adjusted[1];
                }
            }
            //delete b->adjusted;
            delete b;
            b = nullptr;
            
            if (op == bounds::SKIP) {
                //logger->trace("Skip row span: ");
                //rpt->printSpan(row_sp);
                return;
            } 
            if (op == bounds::ADJUSTED) {
                //logger->trace("Adjusted row span: offset: ", row_sp.offset, "bounds: [", begin, " , ", end, "]");
            }
            else {
                //logger->trace("No adjustment on row span:");
                //rpt->printSpan(row_sp);
            }
        }
    }

    int count_newentry = 0;
    int count_newbounds = 0;
    for (int i=begin; i<=end; i++) { // i: a span of col_no
        // when we call get_col_span() on (, i), it is possible other row
        // have already set the col_span for (, i).
        auto search = cols_map->find(i);
        if (search == cols_map->end()) {
            get_col_span(mat, row_sp.offset, i);
            vector<int*>* v = new vector<int*>();
            cols_map->insert(make_pair(i, v));
            v->push_back(cols->back()->span);
            count_newentry++;
        }
        else {
            if (! helper->contains( *search->second, row_sp.offset)) {
                get_col_span(mat, row_sp.offset, i);
                search->second->push_back(cols->back()->span);
                count_newbounds++; 
            }
        }
    }
    //logger->trace("New entry generated: ", count_newentry, " New bounds generated: ", count_newbounds);
}

/*
 * Calculate and create a set of row spans.
 */
void abstract_explore::explore_vert(const cv::Mat& mat, const span_node& col_sp) {
    int begin = col_sp.span[0];
    int end = col_sp.span[1];

    //logger->trace_inline("Explore vert: ");
    //rpt->printSpan(col_sp);
    
    if (col_sp.offset > 0) {
        auto sch = cols_map->find(col_sp.offset - 1);
        if (sch != cols_map->end()) {
            bounds* b = new bounds();
            helper->adjustBounds(*b, begin, end, *sch->second);
            
            int op = b->op;
            if (op == bounds::ADJUSTED) {
                if (begin != b->adjusted[0]) {
                    begin = b->adjusted[0];
                }
                if (end != b->adjusted[1]) {
                    end = b->adjusted[1];
                }
            }
            //delete b->adjusted;
            delete b;
            b = nullptr;

            if (op == bounds::SKIP) {
                //logger->trace("Skip col span: ");
                //rpt->printSpan(col_sp);
                return;
            } 
            if (op == bounds::ADJUSTED) {
                //logger->trace("Adjusted col span: offset: ", col_sp.offset, "bounds: [", begin, " , ", end, "]");
            }
            else {
                //logger->trace("No adjustment on col span:");
                //rpt->printSpan(col_sp);
            }
        }
    }
    
    int count_newentry = 0;
    int count_newbounds = 0;

    for (int i=begin; i<=end; i++) {  // i: a span of row_no
        auto search = rows_map->find(i);
        if (search == rows_map->end()) {
            get_row_span(mat, i, col_sp.offset);
            vector<int*>* v = new vector<int*>();
            rows_map->insert(make_pair(i, v));
            v->push_back(rows->back()->span);
            count_newentry++;
        }
        else {
            if (! helper->contains( *search->second, col_sp.offset)) {
                get_row_span(mat, i, col_sp.offset);
                search->second->push_back(rows->back()->span);
                count_newbounds++;
            }
        }
    }
    //logger->ftrace("snsn", "New entry generated: ", count_newentry, " New bounds generated: ", count_newbounds);
}

void abstract_explore::explore_diag(const cv::Mat& mat, vector<int*>* dvec) {
    if (rows_map == nullptr || rows_map->size() == 0) {
        logger->info("Explore diagonal: Rows map not available.");
        return;
    }
    this->dv = dvec;

    // https://www.geeksforgeeks.org/cpp/how-to-find-the-last-element-in-a-map-in-cpp/
    auto lastPair = prev(rows_map->end());
    int lastRowOnMap = lastPair->first;

    int left = 0; 
    int right = 0;
    for (auto it=rows_map->begin(); it!=rows_map->end(); it++) {
        for (int i=0; i<it->second->size(); i++) {
            left = it->second->at(i)[0];
            right = it->second->at(i)[1];
            //logger->ftrace("snsnsn", "Processing: row: ", it->first, " left: ", left, " right: ", right);
            if (it->first == 0) {
                if (left > 0) {
                    if (!helper->containsOnMap(explore_helper::ROW, *rows_map, it->first+1, left-1)) { 
                        checkDiagnal(mat, it->first+1, left-1);
                    }
                }
                if (right < W-1) {
                    if (it->first == lastRowOnMap || !helper->containsOnMap(explore_helper::ROW, *rows_map, it->first+1, right+1)) { 
                        checkDiagnal(mat, it->first+1, right+1);
                    } 
                }
            }
            else if (it->first == lastRowOnMap) {
                if (left > 0) {
                    if (!helper->containsOnMap(explore_helper::ROW, *rows_map, it->first-1, left-1)) {
                        checkDiagnal(mat, it->first-1, left-1);
                    }
                }

                if (right < W-1) {
                    if (!helper->containsOnMap(explore_helper::ROW, *rows_map, it->first-1, right+1)) {
                        checkDiagnal(mat, it->first-1, right+1);
                    }
                }
            }
            else {
                if (left > 0) {
                    if (!helper->containsOnMap(explore_helper::ROW, *rows_map, it->first-1, left-1)) {
                        checkDiagnal(mat, it->first-1, left-1);
                    }
                    if ( !helper->containsOnMap(explore_helper::ROW, *rows_map, it->first+1, left-1)) {
                        checkDiagnal(mat, it->first+1, left-1);
                    }
                }
                
                if (right < W-1) {
                    if (!helper->containsOnMap(explore_helper::ROW, *rows_map, it->first-1, right+1)) {
                        checkDiagnal(mat, it->first-1, right+1);
                    }
                    if (!helper->containsOnMap(explore_helper::ROW, *rows_map, it->first+1, right+1)) {
                        checkDiagnal(mat, it->first+1, right+1);
                    }
                }
            }
        }  
    }
}

void abstract_explore::setExploreHelper(explore_helper* h) {
    this->helper = h;
}

void abstract_explore::setLogger(iapcv_log* logger) {
    this->logger = logger;
}

