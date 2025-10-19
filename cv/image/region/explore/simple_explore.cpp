#include <chrono>
#include <iostream>

#include "simple_explore.h"

using namespace std;

simple_explore::simple_explore() {
    sta = new bool_status(status::NORMAL, false);
}

simple_explore::~simple_explore() {
    mbounds = nullptr;
    evaluator = nullptr;
    rpt = nullptr;
    
    delete sta;
}

void simple_explore::explore(cv::Mat& mat, int row, int col, std::deque<span_node*>& rs, std::deque<span_node*>& cs, map<int, vector<int*>*>& rs_map, map<int, vector<int*>*>& cs_map) {
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
    
    int count_op = 0; 
    int count_exp_col = 0;
    int count_exp_row = 0;
    while (cols->size()>0 || rows->size()>0) { 
      logger->trace("Deque cols size: ", cols->size());
      logger->trace("Deque rows size: ", rows->size());
      count_op++;
      assert(count_op<2048);

      while (cols->size() > 0) {
        count_exp_col++;
        logger->trace("Explore col span: ");
        //rpt->printQueue("cols", *cols);
        span_node* first = cols->front();  
        explore_vert(mat, *first);
        cols->pop_front();  

        logger->trace("Explore vert completed.");
        //rpt->printQueue("rows", *rows);
        //rpt->printMap("rows", *rows_map);
      }
    
      while (rows->size() > 0) {
        count_exp_row++;
        logger->trace("explore row span: ");
        //rpt->printQueue("rows", *rows);

        span_node* first = rows->front();  
        explore_hort(mat, *first);
        rows->pop_front();
        logger->trace("Explore hort completed.");
        //rpt->printQueue("cols", *cols);
        //rpt->printMap("cols", *cols_map);
    }
  }
    logger->fdebug("snsnsn", "count: ", count_op, " count col: ", count_exp_col, " count row: ", count_exp_row);
}

int simple_explore::get_top(const cv::Mat& mat, int r, int c) {
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

int simple_explore::get_bottom(const cv::Mat& mat, int r, int c) { 
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

int simple_explore::get_left(const cv::Mat& mat, int r, int c) {
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

int simple_explore::get_right(const cv::Mat& mat, int r, int c) {
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

void simple_explore::setMatrixBounds(matrix_bounds* mb) {
    this->mbounds = mb;
}

void simple_explore::setRegionEvaluator(region_evaluator* eval) {
    this->evaluator = eval;
}
        
void simple_explore::setRegionDesc(RegionDesc desc){
    this->desc = desc;
}
        
void simple_explore::setRegionPrint(region_print* p){
    this->rpt = p;
}




