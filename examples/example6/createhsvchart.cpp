#include <ctime>
#include <iostream>

#include "createhsvchart.h"

using namespace std;

createhsvchart::~createhsvchart() {
    convert = nullptr;
}

void createhsvchart::createChart(double h) {
    this->H = h;
    
    uchar* bgr = new uchar[convert_bgrhsv::channel]{0};
    cv::Mat input = cv::imread(fname);
    
    for(int r=0; r<input.rows; r=r+4) {
      for(int c=0; c<input.cols; c=c+4) {
        
        // S increases from 0 to 100 as loop going on c.
        convert->toBgr(convert_bgrhsv::channel, bgr, 217, c/4, 100-r/4);
        cv::Vec3b & color = input.at<cv::Vec3b>(c, r);

        color[0] = bgr[0];
        color[1] = bgr[1];
        color[2] = bgr[2];
        
        for (int k=0; k<4; k++) {
            for (int m=0; m<4; m++) {
                input.at<cv::Vec3b>(cv::Point(c+k, r+m)) = color;
            }
        }
    }
  }
  cv::imshow("input", input);
  cv::waitKey(0);

  string fn = "H" + to_string((int)round(H));
  fn = createFileName(fn);
  //cout << "Write file: " << fn << endl;
  //cv::imwrite(fn, input);
  input.release();
  delete bgr;
}

string createhsvchart::createFileName(string prefix) {
    std::time_t t = std::time(0); 
    std::tm* now = std::localtime(&t);
    string month;
    if (now->tm_mon + 1 < 10) {
        month = "0" + to_string(now->tm_mon+1);
    }
    else {
        month = to_string(now->tm_mon+1);
    }
    
    string fn = prefix;
    fn+="-";
    fn+= to_string((now->tm_year + 1900));
    fn+="-";
    fn+= month;
    fn+="-";
    fn+=to_string(now->tm_mday);
    fn+="-";
    fn+=to_string(now->tm_hour);
    fn+="-";
    fn+=to_string(now->tm_min);
    fn+="-";
    fn+=to_string(now->tm_sec);
    fn+=".JPG";
    return fn;
}

void createhsvchart::createChart(uchar b, uchar g, uchar r) {
    cv::Mat input = cv::imread(fname);
    
    for(int row=0; row<input.rows; row++) {
      for(int c=0; c<input.cols; c++) {
        cv::Vec3b & color = input.at<cv::Vec3b>(c, row);

        color[0] = b;
        color[1] = g;
        color[2] = r;
        input.at<cv::Vec3b>(cv::Point(c, row)) = color;
    }
  }

  cv::imshow("input", input);
  cv::waitKey(0);
  string fn = createFileName("BGR");
  cout << "Write file: " << fn << endl;
  cv::imwrite(fn, input);
  input.release();
}

void createhsvchart::setConvertHSV(convert_bgrhsv* convert) {
    this->convert = convert;
}

void createhsvchart::setFileName(string fname) {
    this->fname = fname;
}