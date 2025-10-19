#include <chrono>
#include <iostream>

#include "region_explore.h"

using namespace std;

region_explore::region_explore() {
    sta = new bool_status(status::NORMAL, false);
    pm = new eval_params();
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
    po = nullptr;
    helper = nullptr;

    delete sta;
    pm->clearParams();
    delete pm;
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
    
    W = mbounds->getW();
    H = mbounds->getH();
    
    /*
     * @20251012 Current policies:
     * If Policies::r_desc, we ignore param1. We set param2 in get_x().
     * If Policies::similar_base_00, we set param1 and param2 in get_x(). We don't compare pixels with start pixel.
     * If Policies::color_value_00, we set param3 in explore() and we set param2 in get_x().
     */
    pm->clearParams();
    
    if (po->getPolicy() != Policies::r_desc) {
        pm->setParam(ParamName::startDesc, start);
        pm->setParam(ParamName::startPixelColor, mat.at<cv::Vec3b>(row, col));
    }
    
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

void region_explore::explore_r(cv::Mat& mat, int row, int col, std::deque<span_node*>& rs, std::deque<span_node*>& cs, map<int, vector<int*>*>& rs_map, map<int, vector<int*>*>& cs_map) {
    this->rows = &rs;
    this->cols = &cs;
    this->rows_map = &rs_map;
    this->cols_map = &cs_map;

    W = mbounds->getW();
    H = mbounds->getH();
    
    pm->clearParams();
    //if (po->getPolicy() == Policies::similar_base_00) {
        //pm->setParam1(ParamName::color1, mat.at<cv::Vec3b>(row, col));
    //}

    get_row_span(mat, row, col);
    vector<int*>* v = new vector<int*>(); 
    rows_map->insert(make_pair(rows->front()->offset, v));
    v->push_back(rows->front()->span);

    int count = 0; 
    int count_exp_col = 0;
    int count_exp_row = 0;
    while (rows->size()>0 || cols->size()>0) { 
      //logger->debug("Deque cols size: ", cols->size());
      //logger->debug("Deque rows size: ", rows->size());
      count++;
      assert(count<2048);

      while (rows->size() > 0) {
        count_exp_row++;
        //logger->debug("Explore col span: ");
        //rpt->printQueue("cols", *cols);
        span_node* first = rows->front();  
        explore_hort(mat, *first);
        rows->pop_front();  

        //logger->debug("Explore vert completed.");
        //printMap("rows", *rows_map);
      }
    
      while (cols->size() > 0) {
        count_exp_col++;
        //logger->debug_inline("explore row span: ");
        //printQueue("rows", *rows);

        span_node* first = cols->front();  
        explore_vert(mat, *first);
        cols->pop_front();
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
        if (po->getPolicy() != Policies::r_desc ) { /// TODO
            if ( cursor < mbounds->bottom()) {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(cursor+1, c));
            }
            else {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(cursor, c));
            }   
        }
        
        pm->setParam(ParamName::color2, mat.at<cv::Vec3b>(cursor, c));
        evaluator->evaluate(*po, *pm, *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        } 
        if (! sta->getResult()) {
            if (cursor == r) {
                return cursor;
            }
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
        if (po->getPolicy() != Policies::r_desc ) { /// TODO
            if ( cursor > mbounds->top()) {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(cursor-1, c));
            }
            else {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(cursor, c));
            }        
        }
        
        pm->setParam(ParamName::color2, mat.at<cv::Vec3b>(cursor, c));
        evaluator->evaluate(*po, *pm, *sta); 
        if (! sta->isNormal()) {
            logger->error(sta->getMsg());
            return INVALID;
        }
        if (! sta->getResult()) {
            if (cursor == r) {
                return cursor;
            }
            return cursor==mbounds->top() ? mbounds->top():cursor-1;
        }
    }
    return mbounds->bottom();
}


void region_explore::get_col_span(const cv::Mat& mat, int r, int c) {
    //cout << "get_col_span: row: " << r << " col: " << c << endl;
    int top = get_top(mat, r, c); 
    assert(top != INVALID);
    int bottom = get_bottom(mat, r, c);
    assert(bottom != INVALID);
    logger->debug("top: ", top);
    logger->debug("bottom: ", bottom);
    
    // we can assert
    assert(top<=r && bottom>=r);
    cols->push_back(helper->createSpanNode(COL, c, top, bottom));
}

int region_explore::get_left(const cv::Mat& mat, int r, int c) {
    if (c == mbounds->left()) {
        // No left not available, i.e. (r, c) is on border.
        return c;
    }
    
    for (int cursor=c; cursor >= mbounds->left(); cursor--) {

        if (po->getPolicy() != Policies::r_desc ) { /// TODO
            if ( cursor < mbounds->right() ) {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(r, cursor+1));
            }
            else {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(r, cursor));
            }   
        }
        
        pm->setParam(ParamName::color2, mat.at<cv::Vec3b>(r, cursor));
        evaluator->evaluate(*po, *pm, *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            if (cursor == c) {
                return cursor;
            }
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
        // /*
        if (po->getPolicy() != Policies::r_desc) { /// TODO
            if (cursor > mbounds->left()) {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(r, cursor-1));
            }
            else {
                pm->setParam(ParamName::color1, mat.at<cv::Vec3b>(r, cursor));
            }        
        }
        //*/
            
        pm->setParam(ParamName::color2, mat.at<cv::Vec3b>(r, cursor));
        evaluator->evaluate(*po, *pm, *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            /*
             * @20251011
             * When we compare (r, cursor) with (r, cursor-1), result could be c.
             * It will never happen when policy is r_desc.
             */
            if (cursor == c) {
                return cursor;
            }
            return cursor==mbounds->left() ? mbounds->left():cursor-1;
        }
    }
    return mbounds->right();
}

void region_explore::get_row_span(const cv::Mat& mat, int r, int c) {
    //cout << "get_row_span: row: " << r << " col: " << c << endl;
    int left = get_left(mat, r, c);
    assert(left != INVALID);
    int right = get_right(mat, r, c);
    assert(right != INVALID);
    logger->debug("left: ", left);
    logger->debug("right: ", right);
    // we can assert
    assert(left<=c && right>=c);
    rows->push_back(helper->createSpanNode(ROW, r, left, right));
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
            if (! helper->contains( *search->second, col_sp.offset)) {
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
            if (! helper->contains( *search->second, row_sp.offset)) {
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

    int firstRowOnMap = rows_map->begin()->first; 

    int left = 0; 
    int right = 0;
    for (auto it=rows_map->begin(); it!=rows_map->end(); it++) {
        for (int i=0; i<it->second->size(); i++) {
            left = it->second->at(i)[0];
            right = it->second->at(i)[1];
            //cout << "Processing: row: " << it->first << " left: " << left << " right: " << right << endl;
            if (it->first == firstRowOnMap) {
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

void region_explore::checkDiagnal(const cv::Mat& mat, int r, int c) {
    //logger->fdebug("snsn", "Check diagonal pixel. Row: ", r, " Col: ", c);
    pm->setParam(ParamName::color2, mat.at<cv::Vec3b>(r, c));
    evaluator->evaluate(*po, *pm, *sta); 
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
        
void region_explore::setRegionPrint(region_print* p){
    this->rpt = p;
}

void region_explore::setEvalPolicy(eval_policy* po) {
    this->po = po;
}

void region_explore::setStartPixelRegionDesc(RegionDesc d) {
    this->start = d;
}

void region_explore::setExploreHelper(explore_helper* helper) {
    this->helper = helper;
}




