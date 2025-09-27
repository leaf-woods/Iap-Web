#include "region_explore.h"

using namespace std;

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
    
    auto t1 = chrono::high_resolution_clock::now();
    
    get_col_span(mat, row, col);
    vector<int*>* v = new vector<int*>(); 
    cols_map->insert(make_pair(cols->front()->offset, v));
    v->push_back(cols->front()->span);

    int count = 0; 
    int count_exp_col = 0;
    int count_exp_row = 0;
    while (cols->size()>0 || rows->size()>0) { 
      //logger.debug("Deque cols size: ", cols->size());
      //logger.debug("Deque rows size: ", rows->size());
      count++;
      assert(count<2048);

      while (cols->size() > 0) {
        count_exp_col++;
        //logger.debug("Explore col span: ");
        //rpt.printQueue("cols", *cols);
        span_node* first = cols->front();  
        explore_vert(mat, *first);
        cols->pop_front();  

        //logger.debug("Explore vert completed.");
        //absr_explore::printQueue("rows", *rows);
        //printMap("rows", *rows_map);
        
        
        //assert( count==1 && cols->size()==0 && rows->size()==9 && cols_map->size()== 1 && rows_map->size()== 0 );
         
      }
    
      while (rows->size() > 0) {
        count_exp_row++;
        //logger.debug_inline("explore row span: ");
        //printQueue("rows", *rows);

        span_node* first = rows->front();  
        explore_hort(mat, *first);
        rows->pop_front();
        //logger.debug("Explore hort completed.");
        //printQueue("cols", *cols);
        //printMap("cols", *cols_map);
    }
  }
    logger.fdebug("snsnsn", "count: ", count, " count col: ", count_exp_col, " count row: ", count_exp_row);
    rpt.printMap("cols", *cols_map);
    cout << endl;
    rpt.printMap("rows", *rows_map);
    //countRegion();
    //cout << "size: " << size() << endl;

    auto t2 = chrono::high_resolution_clock::now();
    logger.info("Total process time: ", (int)chrono::duration_cast<chrono::microseconds>(t2-t1).count());
}

int region_explore::get_top(const cv::Mat& mat, int r, int c) {
    if (r == 0) {
        return r;
    }
    
    for (int cursor=r; cursor >= 0; cursor--) { 
        evaluator.evaluate(desc, mat.at<cv::Vec3b>(cursor, c), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        } 
        if (! sta->getResult()) {
            return cursor==H-1 ? H-1:cursor+1;
        }
    }
    return 0;
}

int region_explore::get_bottom(const cv::Mat& mat, int r, int c) { 
    if (r == H-1) {
        return r;
    }

    for (int cursor=r; cursor <= H-1; cursor++) {
        evaluator.evaluate(desc, mat.at<cv::Vec3b>(cursor, c), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==0 ? 0:cursor-1;
        }
    }
    return H-1;
}

void region_explore::get_col_span(const cv::Mat& mat, int r, int c) {
    int top = get_top(mat, r, c); 
    assert(top != INVALID);
    int bottom = get_bottom(mat, r, c);
    assert(bottom != INVALID);
    //logger.debug("top: ", top);
    //logger.debug("bottom: ", bottom);
    
    // we can assert
    cols->push_back(createSpanNode(COL, c, top, bottom));
}

int region_explore::get_left(const cv::Mat& mat, int r, int c) {
    if (c == 0) {
        // No left not available, i.e. (r, c) is on border.
        return c;
    }
    
    for (int cursor=c; cursor >= 0; cursor--) {
        evaluator.evaluate(desc, mat.at<cv::Vec3b>(r, cursor), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==W-1 ? W-1:cursor+1;
        }
    }
    return 0;
}

int region_explore::get_right(const cv::Mat& mat, int r, int c) {
    if (c == W-1) {
        return c;
    }

    for (int cursor=c; cursor <= W-1; cursor++) {
        evaluator.evaluate(desc, mat.at<cv::Vec3b>(r, cursor), *sta); 
        if (! sta->isNormal()) {
            return INVALID;
        }
        if (! sta->getResult()) {
            return cursor==0 ? 0:cursor-1;
        }
    }
    return W-1;
}

void region_explore::get_row_span(const cv::Mat& mat, int r, int c) {
    int left = get_left(mat, r, c);
    assert(left != INVALID);
    int right = get_right(mat, r, c);
    assert(right != INVALID);
    //logger.debug("left: ", left);
    //logger.debug("right: ", right);
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

    //logger.debug_inline("Explore vert: ");
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
                //logger.debug("Skip col span: ");
                //printSpan(col_sp);
                return;
            } 
            if (op == bounds::ADJUSTED) {
                //logger.debug("Adjusted col span: offset: ", col_sp.offset, "bounds: [", begin, " , ", end, "]");
            }
            else {
                //logger.debug("No adjustment on col span:");
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
    //logger.debug("New entry generated: ", count_newentry, " New bounds generated: ", count_newbounds);
}

/*
 * Calculate and create a set of col spans.
 */
void region_explore::explore_hort(const cv::Mat& mat, const span_node& row_sp) {
    int begin = row_sp.span[0];
    int end = row_sp.span[1];

    //logger.debug_inline("Explore hort: ");
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
                //logger.debug("Skip row span: ");
                //printSpan(row_sp);
                return;
            } 
            if (op == bounds::ADJUSTED) {
                //logger.debug("Adjusted row span: offset: ", row_sp.offset, "bounds: [", begin, " , ", end, "]");
            }
            else {
                //logger.debug("No adjustment on row span:");
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
    //logger.debug("New entry generated: ", count_newentry, " New bounds generated: ", count_newbounds);
}

