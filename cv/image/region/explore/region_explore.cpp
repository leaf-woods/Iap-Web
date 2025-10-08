#include <chrono>
#include <iostream>

#include "region_explore.h"

using namespace std;

region_explore::region_explore() {
    sta = new bool_status(status::NORMAL, false);
}

region_explore::~region_explore() {
    cols = nullptr;
    rows = nullptr;
    cols_map = nullptr;
    rows_map = nullptr;  
    dv = nullptr;
    logger = nullptr;
    mbounds = nullptr;
    evaluator = nullptr;
    rpt = nullptr;
    
    delete sta;
}

void region_explore::adjustBounds(bounds& b, int begin, int end, const vector<int*>& v) {
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
bool region_explore::contains(const vector<int*>& v, int n) {
    for (int i=0; i<v.size(); i++) {
        if (v.at(i)[0] <= n && n <= v.at(i)[1]) {
            return true;
        }
    }
    return false;
}

span_node* region_explore::createSpanNode(int type, int offset, int lower, int upper) {
    span_node* n = new span_node();
    n->type = type;
    n->offset = offset;
    n->span[0] = lower;
    n->span[1] = upper;
    return n;
}

void region_explore::explore(cv::Mat& mat, int row, int col, std::deque<span_node*>& rs, std::deque<span_node*>& cs, map<int, vector<int*>*>& rs_map, map<int, vector<int*>*>& cs_map) {
    //cout << "Param: m: " << &m << endl;
    //cout << "Instance variable mat: " << &this->mat << endl;
    //cv::Mat mat2 = m;
    //cout << "Tmp variable: mat2: " << &mat2 << endl;
    //this->mat = m;   /// TODO: this line has no reason to produce SMF.
    //cout << "Instance variable mat: " << &this->mat << endl;
    //cout << "Param: m: " << &m << endl;
    this->rows = &rs;
    this->cols = &cs;
    this->rows_map = &rs_map;
    this->cols_map = &cs_map;

    W = mat.cols;
    H = mat.rows;
    
    get_col_span(mat, row, col);
    vector<int*>* v = new vector<int*>(); 
    cols_map->insert(make_pair(cols->front()->offset, v));
    v->push_back(cols->front()->span);
    
    int count = 0; 
    int count_exp_col = 0;
    int count_exp_row = 0;
    while (cols->size()>0 || rows->size()>0) { 
      //logger->debug("Deque cols size: ", cols->size());
      //logger->debug("Deque rows size: ", rows->size());
      count++;
      assert(count<2048);

      while (cols->size() > 0) {
        count_exp_col++;
        //logger->debug("Explore col span: ");
        //rpt->printQueue("cols", *cols);
        span_node* first = cols->front();  
        explore_vert(mat, *first);
        cols->pop_front();  

        //logger->debug("Explore vert completed.");
        //absr_explore::printQueue("rows", *rows);
        //printMap("rows", *rows_map);
      }
    
      while (rows->size() > 0) {
        count_exp_row++;
        //logger->debug_inline("explore row span: ");
        //printQueue("rows", *rows);

        span_node* first = rows->front();  
        explore_hort(mat, *first);
        rows->pop_front();
        //logger->debug("Explore hort completed.");
        //printQueue("cols", *cols);
        //printMap("cols", *cols_map);
    }
  }
    logger->fdebug("snsnsn", "count: ", count, " count col: ", count_exp_col, " count row: ", count_exp_row);
}

int region_explore::get_top(const cv::Mat& mat, int r, int c) {
    if (r == mbounds->top()) {
        return r;
    }
    
    for (int cursor=r; cursor >= mbounds->top(); cursor--) { 
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(cursor, c), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        } 
        if (! sta->getResult()) {
            return cursor==mbounds->bottom() ? mbounds->bottom():cursor+1;
        }
    }
    return mbounds->top();
}

int region_explore::get_bottom(const cv::Mat& mat, int r, int c) { 
    if (r == mbounds->bottom()) {
        return r;
    }

    for (int cursor=r; cursor <= mbounds->bottom(); cursor++) {
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(cursor, c), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==mbounds->top() ? mbounds->top():cursor-1;
        }
    }
    return mbounds->bottom();
}


void region_explore::get_col_span(const cv::Mat& mat, int r, int c) {
    int top = get_top(mat, r, c); 
    assert(top != INVALID);
    int bottom = get_bottom(mat, r, c);
    assert(bottom != INVALID);
    //logger->debug("top: ", top);
    //logger->debug("bottom: ", bottom);
    
    // we can assert
    cols->push_back(createSpanNode(COL, c, top, bottom));
}

int region_explore::get_left(const cv::Mat& mat, int r, int c) {
    if (c == mbounds->left()) {
        // No left not available, i.e. (r, c) is on border.
        return c;
    }
    
    for (int cursor=c; cursor >= mbounds->left(); cursor--) {
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(r, cursor), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==mbounds->right() ? mbounds->right():cursor+1;
        }
    }
    return mbounds->left();
}

int region_explore::get_right(const cv::Mat& mat, int r, int c) {
    if (c == mbounds->right()) {
        return c;
    }

    for (int cursor=c; cursor <= mbounds->right(); cursor++) {
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(r, cursor), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==mbounds->left() ? mbounds->left():cursor-1;
        }
    }
    return mbounds->right();
}

void region_explore::get_row_span(const cv::Mat& mat, int r, int c) {
    int left = get_left(mat, r, c);
    assert(left != INVALID);
    int right = get_right(mat, r, c);
    assert(right != INVALID);
    //logger->debug("left: ", left);
    //logger->debug("right: ", right);
    // we can assert
    assert(left<=c && right>=c);
    rows->push_back(createSpanNode(ROW, r, left, right));
}

/*
 * Calculate and create a set of row spans.
 */
void region_explore::explore_vert(const cv::Mat& mat, const span_node& col_sp) {
    int begin = col_sp.span[0];
    int end = col_sp.span[1];

    //logger->debug_inline("Explore vert: ");
    //printSpan(col_sp);
    
    if (col_sp.offset > 0) {
        auto sch = cols_map->find(col_sp.offset - 1);
        if (sch != cols_map->end()) {
            bounds* b = new bounds();
            adjustBounds(*b, begin, end, *sch->second);
            
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
                //logger->debug("Skip col span: ");
                //printSpan(col_sp);
                return;
            } 
            if (op == bounds::ADJUSTED) {
                //logger->debug("Adjusted col span: offset: ", col_sp.offset, "bounds: [", begin, " , ", end, "]");
            }
            else {
                //logger->debug("No adjustment on col span:");
                //printSpan(col_sp);
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
            v->push_back(rows->back()->span);  // SMF
            count_newentry++;
        }
        else {
            if (! contains( *search->second, col_sp.offset)) {
                get_row_span(mat, i, col_sp.offset);
                search->second->push_back(rows->back()->span);
                count_newbounds++;
            }
        }
    }
    //logger->debug("New entry generated: ", count_newentry, " New bounds generated: ", count_newbounds);
}

/*
 * Calculate and create a set of col spans.
 */
void region_explore::explore_hort(const cv::Mat& mat, const span_node& row_sp) {
    int begin = row_sp.span[0];
    int end = row_sp.span[1];

    //logger->debug_inline("Explore hort: ");
    //printSpan(row_sp);

    if (row_sp.offset > 0) {
        auto sch = rows_map->find(row_sp.offset - 1);
        if (sch != rows_map->end()) {
            bounds* b = new bounds(); 
            adjustBounds(*b, begin, end, *sch->second);
            
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
                //logger->debug("Skip row span: ");
                //printSpan(row_sp);
                return;
            } 
            if (op == bounds::ADJUSTED) {
                //logger->debug("Adjusted row span: offset: ", row_sp.offset, "bounds: [", begin, " , ", end, "]");
            }
            else {
                //logger->debug("No adjustment on row span:");
                //printSpan(row_sp);
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
            if (! contains( *search->second, row_sp.offset)) {
                get_col_span(mat, row_sp.offset, i);
                search->second->push_back(cols->back()->span);
                count_newbounds++; 
            }
        }
    }
    //logger->debug("New entry generated: ", count_newentry, " New bounds generated: ", count_newbounds);
}

void region_explore::explore_diag(const cv::Mat& mat, vector<int*>* dvec) {
    if (rows_map == nullptr || rows_map->size() == 0) {
        logger->info("Rows map not available.");
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
            //cout << "Processing: row: " << it->first << " left: " << left << " right: " << right << endl;
            if (it->first == 0) {
                if (left > 0) {
                    if (!containsOnMap(it->first+1, left-1)) { 
                        checkDiagnal(mat, it->first+1, left-1);
                    }
                }
                if (right < W-1) {
                    if (it->first == lastRowOnMap || !containsOnMap(it->first+1, right+1)) { 
                        checkDiagnal(mat, it->first+1, right+1);
                    } 
                }
            }
            else if (it->first == lastRowOnMap) {
                if (left > 0) {
                    if (!containsOnMap(it->first-1, left-1)) {
                        checkDiagnal(mat, it->first-1, left-1);
                    }
                }

                if (right < W-1) {
                    if (!containsOnMap(it->first-1, right+1)) {
                        checkDiagnal(mat, it->first-1, right+1);
                    }
                }
            }
            else {
                if (left > 0) {
                    if (!containsOnMap(it->first-1, left-1)) {
                        checkDiagnal(mat, it->first-1, left-1);
                    }
                    if ( !containsOnMap(it->first+1, left-1)) {
                        checkDiagnal(mat, it->first+1, left-1);
                    }
                }
                
                if (right < W-1) {
                    if (!containsOnMap(it->first-1, right+1)) {
                        checkDiagnal(mat, it->first-1, right+1);
                    }
                    if (it->first == lastRowOnMap && !containsOnMap(it->first+1, right+1)) {
                        checkDiagnal(mat, it->first+1, right+1);
                    }
                }
            }
        }  
    }
}

bool region_explore::containsOnMap(int row, int col) {
    //cout << "containsOnMap: row: " << row << " col: " << col << endl;
    auto sch = rows_map->find(row);
    assert(sch != rows_map->end());
    return contains(*sch->second, col);
}

void region_explore::checkDiagnal(const cv::Mat& mat, int r, int c) {
    //logger->fdebug("snsn", "Check diagonal pixel. Row: ", r, " Col: ", c);
    evaluator->evaluate(desc, mat.at<cv::Vec3b>(r, c), *sta); 
    if (! sta->isNormal()) {
        logger->error(sta->getMsg());
    }
    else if (! sta->getResult()) {
        //logger->finfo("snsns", "Diagnol pixel: row ", r, " col: ", c, " not connected.");
    }
    else {
        logger->finfo("snsns", "Diagnol pixel: row ", r, " col: ", c, " is connected.");
        dv->push_back(new int[]{r, c});
    }
}

void region_explore::setLogger(iapcv_log* logger) {
    this->logger = logger;
}

void region_explore::setMatrixBounds(matrix_bounds* mb) {
    this->mbounds = mb;
}

void region_explore::setRegionEvaluator(region_evaluator* eval) {
    this->evaluator = eval;
}
        
void region_explore::setRegionDesc(RegionDesc desc){
    this->desc = desc;
}
        
void region_explore::setRegionPrint(region_print* p){
    this->rpt = p;
}




