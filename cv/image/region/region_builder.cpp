#include <cassert>
#include <chrono>
#include <iostream>
#include "region_builder.h"

using namespace std;

/*
 * @20250912
 * A region has a property desc to indicate what is the region, e.g. the region is 
 * sky on the photo.
 */
 /// TODO test smallest region which is one pixel
 /*
  * @20250916
  * A region_builder builds regions using the image matrix according to the region desc.
  */
region_builder::region_builder() {
    init();
    sta = new bool_status(status::NORMAL, false);
    logger = new iapcv_log(typeid(this).name());
    logger->setLevel(iapcv_log::DEBUG);
}

region_builder::~region_builder() {
    logger->info("Destruct region builder.");
    clear();
    evaluator = nullptr;
    printer = nullptr;
    delete sta;
    sta = nullptr;
    delete logger;
    logger = nullptr;
}

void region_builder::clearMap(map<int, vector<int*>*>& m) {
    if (m.size()>0) {
        vector<int*>* v;
        for (auto it=m.begin(); it!=m.end();) {
            v = it->second;
            v->clear(); 
            *v = vector<int*>();
            it = m.erase(it);
            delete v;
        }
    }
}

/*
 * Since region is reusable, clear() is not only called by destructor.
 */
void region_builder::clear() {
    if (sta != nullptr) {
        sta->clear();
    }
    
    // Just cleared.
    if (cols_map == nullptr || rows_map == nullptr || cols == nullptr || rows == nullptr) {
        return;
    }
    
    // Just created.
    if (cols_map->size()==0 && rows_map->size()==0 && cols->size()==0 && rows->size()==0) {
        delete cols_map; 
        cols_map = nullptr;
        delete rows_map; 
        rows_map = nullptr;
        delete cols; 
        cols = nullptr;
        delete rows; 
        rows = nullptr;
    }

    // Just used.
    if (cols_map->size()>0) {
        clearMap(*cols_map);
    }
    *cols_map = map<int, std::vector<int*>*>();
    delete cols_map;
    cols_map = nullptr;

    if (rows_map->size()>0) {
        clearMap(*rows_map);
    }
    *rows_map = map<int, std::vector<int*>*>();
    delete rows_map;
    rows_map = nullptr;

    //https://stackoverflow.com/questions/56688963/how-to-free-the-memory-occupied-by-a-queuestl
    if (cols->size()>0) {
        logger->error("Queue cols is not empty. Size: ", cols->size());
        cols->clear();
        deque<span_node*>().swap(*cols);
    }
    if (rows->size()>0) {
        logger->error("Queue rows is not empty. Size: ", rows->size());
        rows->clear();
        deque<span_node*>().swap(*rows);
    }
    delete rows;
    rows = nullptr;
    delete cols;
    cols = nullptr;
}

void region_builder::init() {
    rows = new deque<span_node*>();
    cols = new deque<span_node*>();

    rows_map = new map<int, vector<int*>*>();
    cols_map = new map<int, vector<int*>*>();
}
/*
 * @20250915 Reuse region.
 * Precondition: deque cols and rows, map cols_map and rows_map are newly created instances.
 */
void region_builder::explore(const cv::Mat& mat, int row, int col) {
    if (mat.rows <= 0 || mat.cols <= 0) {
        logger->info("Invalid matrix.");
        return;
    }
    if (row < 0 || row >= mat.rows) {
        logger->info("Row out of bound: ", row);
        return;
    }
    if (col < 0 || col >= mat.cols) {
        logger->info("Col out of bound: ", col);
        return;
    }

    assert(desc > RegionDesc::na);
    logger->info("Explore: ", region_desc::toString(desc));

    sta->clear();
    checkInBound(mat, row, col, *sta);
    if (! sta->getResult()) {
        if (sta->isNormal()) {
            logger->finfo("snsnsv", "Pixel not in region: row: ", row, " col: ", col, " for: ", region_desc::toString(desc));
        }
        else {
            logger->error(sta->getMsg());
        }
        return;
    }

    // Just cleared.
    if (cols_map == nullptr || rows_map == nullptr || cols == nullptr || rows == nullptr) {
        init();
    }
    // Just used.
    if (cols->size()>0 || rows->size()>0 || cols_map->size()>0 || rows_map->size()>0) {
        clear();
        init(); 
    }

    W = mat.cols;
    H = mat.rows;
    
    auto t1 = chrono::high_resolution_clock::now();

    get_col_span(mat, row, col);
    vector<int*>* v = new vector<int*>(); 
    cols_map->insert(make_pair(cols->front()->offset, v));
    v->push_back(cols->front()->span);

    int count = 0; 
    int count_exp_col = 0;
    int count_exp_row = 0;
    while (cols->size()>0 || rows->size()>0) { 
      logger->debug("Deque cols size: ", cols->size());
      logger->debug("Deque rows size: ", rows->size());
      count++;
      assert(count<2048);

      while (cols->size() > 0) {
        count_exp_col++;
        //logger->debug("Explore col span: ");
        //printQueue("cols", cols);
        span_node* first = cols->front();  
        explore_vert(mat, *first);
        cols->pop_front();  

        //logger->debug("Explore vert completed.");
        //printQueue("rows", rows);
        //printMap("rows", *rows_map);
        
        /*
         * cols->size(): 0
         * rows->size(): 9
         * cols_map->size(): 1
         * rows_map->size(): 0
         */
      }
    
      while (rows->size() > 0) {
        count_exp_row++;
        //logger->debug_inline("explore row span: ");
        //printQueue("rows", rows);

        span_node* first = rows->front();  
        explore_hort(mat, *first);
        rows->pop_front();
        //logger->debug("Explore hort completed.");
        //printQueue("cols", cols);
        //printMap("cols", *cols_map);
    }
  }
    logger->fdebug("snsnsn", "count: ", count, " count col: ", count_exp_col, " count row: ", count_exp_row);
    printMap("cols", *cols_map);
    cout << endl;
    printMap("rows", *rows_map);
    countRegion();
    cout << "size: " << size() << endl;

    auto t2 = chrono::high_resolution_clock::now();
    logger->info("Total process time: ", (int)chrono::duration_cast<chrono::microseconds>(t2-t1).count());
}

void region_builder::explore_r(const cv::Mat& mat, int row, int col) {
    if (mat.rows <= 0 || mat.cols <= 0) {
        logger->info("Invalid matrix.");
        return;
    }
    if (row < 0 || row >= mat.rows) {
        logger->info("Row out of bound: ", row);
        return;
    }
    if (col < 0 || col >= mat.cols) {
        logger->info("Col out of bound: ", col);
        return;
    }

    assert(desc > RegionDesc::na);
    logger->info("Explore: ", region_desc::toString(desc));

    sta->clear();
    checkInBound(mat, row, col, *sta);
    if (! sta->getResult()) {
        if (sta->isNormal()) {
            logger->info("Pixel not in region: ", "row: " + to_string(row) + " col: " + to_string(col) + " " + region_desc::toString(desc));
        }
        else {
            logger->error(sta->getMsg());
        }
        return;
    }

    // Just cleared.
    if (cols_map == nullptr || rows_map == nullptr || cols == nullptr || rows == nullptr) {
        init();
    }
    // Just used.
    if (cols->size()>0 || rows->size()>0 || cols_map->size()>0 || rows_map->size()>0) {
        clear();
        init(); 
    }

    W = mat.cols;
    H = mat.rows;
    
    auto t1 = chrono::high_resolution_clock::now();

    get_row_span(mat, row, col);
    vector<int*>* v = new vector<int*>();
    rows_map->insert(make_pair(rows->front()->offset, v));
    v->push_back(rows->front()->span);

    int count = 0; 
    int count_exp_col = 0;
    int count_exp_row = 0;
    while ( rows->size()>0 || cols->size()>0 ) { 
      //logger->debug("Deque cols size: ", cols->size());
      //logger->debug("Deque rows size: ", rows->size());
      count++;
      assert(count<2048);

      while (rows->size() > 0) {
        count_exp_row++;
        //logger->debug_inline("explore row span: ");
        //printQueue("rows", rows);

        span_node* first = rows->front();  
        explore_hort(mat, *first);
        rows->pop_front();
        //logger->debug("Explore hort completed.");
        //printQueue("cols", cols);
        //printMap("cols", *cols_map);
        //cout << endl;
      }

      while (cols->size() > 0) {
        count_exp_col++;
        //logger->debug("Explore col span: ");
        //printQueue("cols", cols);
        span_node* first = cols->front();  
        explore_vert(mat, *first);
        cols->pop_front();  

        //logger->debug("Explore vert completed.");
        //printQueue("rows", rows);
        //printMap("rows", *rows_map);
        //cout << endl;
        /*
         * cols->size(): 0
         * rows->size(): 9
         * cols_map->size(): 1
         * rows_map->size(): 0
         */
      }
  }
    logger->fdebug("snsnsn", "count: ", count, " count col: ", count_exp_col, " count row: ", count_exp_row);
    //printMap("cols", *cols_map);
    cout << endl;
    //printMap("rows", *rows_map);
    countRegion();
    cout << "size: " << size() << endl;

    auto t2 = chrono::high_resolution_clock::now();
    logger->info("Total process time: ", (int)chrono::duration_cast<chrono::microseconds>(t2-t1).count());
}

void region_builder::checkInBound(const cv::Mat& mat, int r, int c, bool_status& sta) {
    evaluator->evaluate(desc, mat.at<cv::Vec3b>(r, c), sta); 
}

span_node* region_builder::createSpanNode(int type, int offset, int lower, int upper) {
    span_node* n = new span_node();
    n->type = type;
    n->offset = offset;
    n->span[0] = lower;
    n->span[1] = upper;
    return n;
}

int region_builder::get_top(const cv::Mat& mat, int r, int c) { 
    if (r == 0) {
        return r;
    }
    
    for (int cursor=r; cursor >= 0; cursor--) { 
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(cursor, c), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        } 
        if (! sta->getResult()) {
            return cursor==H-1 ? H-1:cursor+1;
        }
    }
    return 0;
}

int region_builder::get_bottom(const cv::Mat& mat, int r, int c) { 
    if (r == H-1) {
        return r;
    }

    for (int cursor=r; cursor <= H-1; cursor++) {
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(cursor, c), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==0 ? 0:cursor-1;
        }
    }
    return H-1;
}

void region_builder::get_col_span(const cv::Mat& mat, int r, int c) {
    int top = get_top(mat, r, c);
    assert(top != INVALID);
    int bottom = get_bottom(mat, r, c);
    assert(bottom != INVALID);
    //logger->debug("top: ", top);
    //logger->debug("bottom: ", bottom);
    
    // we can assert
    cols->push_back(createSpanNode(COL, c, top, bottom));
}

int region_builder::get_left(const cv::Mat& mat, int r, int c) {
    if (c == 0) {
        // No left not available, i.e. (r, c) is on border.
        return c;
    }
    
    for (int cursor=c; cursor >= 0; cursor--) {
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(r, cursor), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==W-1 ? W-1:cursor+1;
        }
    }
    return 0;
}

int region_builder::get_right(const cv::Mat& mat, int r, int c) {
    if (c == W-1) {
        return c;
    }

    for (int cursor=c; cursor <= W-1; cursor++) {
        evaluator->evaluate(desc, mat.at<cv::Vec3b>(r, cursor), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==0 ? 0:cursor-1;
        }
    }
    return W-1;
}

void region_builder::get_row_span(const cv::Mat& mat, int r, int c) {
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
void region_builder::explore_vert(const cv::Mat& mat, const span_node& col_sp) {
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
void region_builder::explore_hort(const cv::Mat& mat, const span_node& row_sp) {
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

/*
 * Check whether integer n is within any span stored in v.
 * At this moment, elements are unordered in v.
 * If v has a large size and needs to be visited many times,
 * we can use a bstree to handle the scenario.
 */
bool region_builder::contains(const vector<int*>& v, int n) {
    for (int i=0; i<v.size(); i++) {
        if (v.at(i)[0] <= n && n <= v.at(i)[1]) {
            return true;
        }
    }
    return false;
}

void region_builder::printSpan(const span_node& sp) {
    if (sp.type == COL) {
        cout << "Col offset: ";
    }
    else {
        cout << "Row offset: ";
    }
    cout << sp.offset << " bounds: [ " << sp.span[0] << " , " << sp.span[1] << " ]" << endl;
}

void region_builder::printVector(const vector<int*>& v) {
    for (int i=0; i<v.size(); i++) {
        cout << " [ " << v.at(i)[0] << " , " << v.at(i)[1] << " ] ";
    }
    cout << endl;
}

void region_builder::printQueue(string which, deque<span_node*>* q) {
    logger->fdebug("snsn", "Print deque. ", which, " size: ", q->size());
    int s = q->size();
    if (s == 0) {
        logger->Info("Empty queue.");
        return;
    }
    for (span_node* p : *q) {
        cout << p->offset << " ; ";
    }
    cout << endl;
}

void region_builder::printMap(string which, const map<int, vector<int*>*>& m) {
    cout << "map: " << which << endl;
    for (auto it=m.begin(); it!=m.end(); it++) {
        cout << "offset: " << it->first << " vector size: " << it->second->size() << " { ";
        for (int i=0; i<it->second->size(); i++) {
            cout << " [" << it->second->at(i)[0] << ", " << it->second->at(i)[1] << "] ";   
        }
        cout << " }" << endl;
    }
}

void region_builder::adjustBounds(bounds& b, int begin, int end, const vector<int*>& v) {
    //logger->debug("adjust bounds. begin: ", begin, " end: ", end, " To check in vector: ");
    //printVector(v);

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

void region_builder::countRegion() {
    if (rows_map->size()==0 || cols_map->size()==0) {
        assert(cols_map->size()==rows_map->size());
        logger->info("Map is empty.");
        return;
    }
    count = 0;
    if (rows_map->size() < cols_map->size()) {
        // https://en.cppreference.com/w/cpp/container/map.html
        for (const auto& [key, value] : *rows_map) {
            count+=countVector(*value);
        }
        
    }
    else {
        for (const auto& [key, value] : *cols_map) {
            count+=countVector(*value);
        }
    }
    logger->debug("size: ", count);
}

int region_builder::countVector(const vector<int*>& v) {
    int ct = 0;
    for (int i=0; i<v.size(); i++) {
        ct+=v.at(i)[1] - v.at(i)[0] + 1;
    }
    return ct;
}

int region_builder::size() {
    return count;
}

void region_builder::setLogLevel(int level) {
    this->logger->setLevel(level);
}

void region_builder::setPrint(iap_print* print) {
    this->printer = print;
}

void region_builder::setRegionDesc(RegionDesc desc) {
    this->desc = desc;
}

void region_builder::setRegionEvaluator(region_evaluator* eval) {
    this->evaluator = eval;
}

bool region_builder::getNextStartPoint(size_t s, int* pixel) {
    assert(s==2 && pixel != nullptr);
    if (rows_map == nullptr) {
        logger->error("Map is null.");
        return false;
    }
    if (rows_map->size() == 0) {
        logger->error("Map is empty.");
        return false;
    }
    int count = 0; 
    for (auto it=rows_map->begin(); it!=rows_map->end(); it++) {
        if (it->second->at(0)[0] >= 1) {
                pixel[0] = count; pixel[1] = it->second->at(0)[0] - 1;
                logger->fdebug("snsns", "Found at [", pixel[0], ", ", pixel[1], "]");
                return true;
        }
        if (it->second->at(0)[1] <= W-2) {
                pixel[0] = count; pixel[1] = it->second->at(0)[1] + 1;
                logger->fdebug("snsns", "Found at [", pixel[0], ", ", pixel[1], "]");
                return true;
        }
        count++;
    }
    logger->error("Cannot find an available pixel.");
    return false;
}

