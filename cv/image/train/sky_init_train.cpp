//https://stackoverflow.com/questions/25642532/opencv-pointx-y-represent-column-row-or-row-column

#include <cassert>
#include <iostream>

#include <opencv2/imgcodecs.hpp>  // cv::imread
#include <opencv2/imgproc.hpp>  // cv::cvtColor() 

#include "sky_init_train.h"

using namespace std;
sky_init_train::sky_init_train(string basePath, string imageName) {
    //assert(basePath != nullptr && basePath.length()>0 && imageName != nullptr && imageName.length()>0);
    this->basePath = basePath;
    this->imageName = imageName;

    setup();
    printer = new iap_print();
}

sky_init_train::~sky_init_train() {
    delete printer;
    printer = nullptr;
}

void sky_init_train::init(cv::Mat& mat) {
            for (int r=0; r<32; r++) {
                for (int c=0; c<32; c++) {
                    cv::Vec3b & color = mat.at<cv::Vec3b>(r, c);
                    color[OF_SKY]=1; color[OF_CLD]=0; color[OF_WCL]=0;
                    mat.at<cv::Vec3b>(cv::Point(c, r)) = color;
                }
            }
}

void sky_init_train::setupCloud(cv::Mat& mat, int row, int col_start, int col_end) {
            if (col_start == col_end) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(row, col_start);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=0;
                mat.at<cv::Vec3b>(cv::Point(col_start, row)) = color;
                return;
            }

            for (int i=col_start; i<=col_end; i++) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(row, i);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=0;
                mat.at<cv::Vec3b>(cv::Point(i, row)) = color;
            }
}

void sky_init_train::setupWeakCloud(cv::Mat& mat, int row, int col_start, int col_end) {
            if (col_start == col_end) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(row, col_start);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=1;
                mat.at<cv::Vec3b>(cv::Point(col_start, row)) = color;
                return;
            }

            for (int i=col_start; i<=col_end; i++) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(row, i);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=1;
                mat.at<cv::Vec3b>(cv::Point(i, row)) = color;
            }
}

void sky_init_train::setup() {
    string fname = basePath + "/" + imageName;
    cout << "Use file: " << fname << endl;
    input = cv::imread(fname);
    cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
            
    train = input.clone();

    init(train);

    // Row 0, Row 1: all sky
            
    // Row 2, Row 3, Row 4
            for (int r=2; r<5; r++) {
                setupWeakCloud(train, r, 17, 19);
            }

    // Row 5, Row 6: all sky

    // Row 7
            setupWeakCloud(train, 7, 16, 18);

    // Row 8
            setupCloud(train, 8, 3, 12);
            setupCloud(train, 8, 16, 22);
            
    // Row 9
            setupCloud(train, 9, 0, 6);
            setupCloud(train, 9, 17, 22);

    // Row 10
            setupCloud(train, 10, 0, 7);
            setupCloud(train, 10, 11, 18);
            setupWeakCloud(train, 10, 20, 22);

    // Row 11
            setupCloud(train, 11, 0, 14);
            setupCloud(train, 11, 16, 18);
            setupWeakCloud(train, 11, 20, 20);
            setupCloud(train, 11, 21, 22);

    // Row 12
            setupWeakCloud(train, 12, 0, 6);
            setupCloud(train, 12, 7, 7);
            setupWeakCloud(train, 12, 8, 10);
            setupCloud(train, 12, 11, 12);
            setupWeakCloud(train, 12, 13, 14);
            setupWeakCloud(train, 12, 17, 17);
            setupCloud(train, 12, 18, 23);

    // Row 13
            setupWeakCloud(train, 13, 0, 2);
            setupCloud(train, 13, 3, 5);
            setupWeakCloud(train, 13, 6, 10);
            setupCloud(train, 13, 11, 13);
            setupWeakCloud(train, 13, 14, 14);
            setupCloud(train, 13, 16, 22);

    // Row 14
            setupCloud(train, 14, 0, 6);
            setupWeakCloud(train, 14, 8, 8);
            setupCloud(train, 14, 11, 13);
            setupCloud(train, 14, 17, 23);
            setupWeakCloud(train, 14, 24, 25);

    // Row 15
            setupCloud(train, 15, 0, 6);
            setupWeakCloud(train, 15, 7, 7);
            setupWeakCloud(train, 15, 12, 13);
            setupCloud(train, 15, 17, 23);
            setupWeakCloud(train, 15, 24, 25);

    // Row 16
            setupCloud(train, 16, 0, 6);
            setupWeakCloud(train, 16, 7, 8);
            setupWeakCloud(train, 16, 12, 17);
            setupCloud(train, 16, 18, 25);
            setupWeakCloud(train, 16, 26, 28);

    // Row 17
            setupCloud(train, 17, 0, 6);
            setupWeakCloud(train, 17, 7, 8);
            setupWeakCloud(train, 17, 12, 18);
            setupCloud(train, 17, 21, 25);
            setupWeakCloud(train, 17, 26, 28);

    // Row 18
            setupCloud(train, 18, 0, 6);
            setupWeakCloud(train, 18, 7, 8);
            setupWeakCloud(train, 18, 12, 18);
            setupCloud(train, 18, 21, 25);
            setupWeakCloud(train, 18, 26, 28);

    // Row 19
            setupCloud(train, 19, 0, 6);
            setupCloud(train, 19, 10, 16);
            setupCloud(train, 19, 22, 26);           
            setupWeakCloud(train, 19, 27, 28);

    // Row 20
            setupCloud(train, 20, 0, 7);
            setupCloud(train, 20, 10, 16);
            setupWeakCloud(train, 20, 18, 22);
            setupCloud(train, 20, 23, 26);
            setupWeakCloud(train, 20, 27, 30);

    // Row 21
            setupCloud(train, 21, 0, 7);
            setupWeakCloud(train, 21, 10, 16);
            setupWeakCloud(train, 21, 19, 21);
            setupWeakCloud(train, 21, 23, 24);
            setupCloud(train, 21, 25, 27);
            setupWeakCloud(train, 21, 28, 31);

    // Row 22
            setupCloud(train, 22, 0, 9);
            setupWeakCloud(train, 22, 10, 16);
            setupCloud(train, 22, 19, 21);
            setupCloud(train, 22, 24, 28);

    // Row 23
            setupCloud(train, 23, 0, 0);
            setupWeakCloud(train, 23, 2, 2);
            setupCloud(train, 23, 5, 6);
            setupWeakCloud(train, 23, 7, 7);
            setupWeakCloud(train, 23, 9, 15);
            setupWeakCloud(train, 23, 19, 19);
            setupWeakCloud(train, 23, 25, 28);

    // Row 24
            setupCloud(train, 24, 0, 1);
            setupWeakCloud(train, 24, 2, 4);
            setupWeakCloud(train, 24, 6, 8);
            setupWeakCloud(train, 24, 22, 23);
            setupCloud(train, 24, 24, 27);
            setupWeakCloud(train, 24, 28, 28);

    // Row 25
            setupCloud(train, 25, 0, 1);
            setupWeakCloud(train, 25, 2, 2);
            setupWeakCloud(train, 25, 6, 7);
            setupWeakCloud(train, 25, 22, 23);
            setupWeakCloud(train, 25, 28, 29);

    // Row 26
            setupWeakCloud(train, 26, 0, 2);
            setupWeakCloud(train, 26, 22, 25);

    // Row 27
            setupWeakCloud(train, 27, 0, 5);
            setupWeakCloud(train, 27, 10, 14);
            setupWeakCloud(train, 27, 23, 25);
            setupCloud(train, 27, 30, 31);

    // Row 28
            setupWeakCloud(train, 28, 0, 5);
            setupWeakCloud(train, 28, 8, 8);
            setupCloud(train, 28, 10, 11);
            setupCloud(train, 28, 12, 14);
            setupCloud(train, 28, 23, 25);
            setupCloud(train, 28, 30, 31);

    // Row 29
            setupWeakCloud(train, 29, 0, 8);
            setupCloud(train, 29, 10, 11);
            setupCloud(train, 29, 14, 15);
            setupCloud(train, 29, 24, 27);

    // Row 30
            setupCloud(train, 30, 0, 4);
            setupCloud(train, 30, 10, 11);
            setupCloud(train, 30, 14, 15);
            setupCloud(train, 30, 25, 29);

    // Row 31
            setupCloud(train, 31, 0, 4);
            setupCloud(train, 31, 5, 8);
            setupCloud(train, 31, 9, 10);

    verifyTrainMax(train);        
}

void sky_init_train::verifyTrainMax(const cv::Mat& mat) {
    for (int r=0; r<train.rows; r++) {
        for (int c=0; c<train.cols; c++ ) {
            cv::Vec3b & color = train.at<cv::Vec3b>(c, r);
            int bgr = getInt(color[0], color[1], color[2]);
            assert(bgr==65536 || bgr==256 || bgr==257);
        }
    }
}

int sky_init_train::getInt(uchar b, uchar g, uchar r){
    return (b<<16) + (g<<8) + r;
}

void sky_init_train::test_dist() {
    uchar s_min_sky = 255; uchar s_max_cloud = 0;

    uchar min_sky[3] = {0}; int min_sky_idx[2] = {0};
    uchar max_cloud[3] = {0}; int max_cloud_idx[2] = {0};

    for (int c=0; c<hsvImage.cols; c++) {
        for (int r=0; r<hsvImage.rows; r++) {
            cv::Vec<unsigned char, 3> entry = hsvImage.at<cv::Vec3b>(c, r);
            //if (entry[0] == 108) { 
                cv::Vec<unsigned char, 3> entry_2 = train.at<cv::Vec3b>(c, r);
                if (entry_2[0] == 1) {
                    if (entry[1] < s_min_sky) {
                        s_min_sky = entry[1];
                        min_sky[0] = entry[0]; min_sky[1] = entry[1]; min_sky[2] = entry[2];
                        min_sky_idx[0] = c; min_sky_idx[1] = r;
                    }
                }
                else {
                    if (entry_2[2]==0 && entry[1] > s_max_cloud) {
                        s_max_cloud = entry[1];
                        max_cloud[0] = entry[0]; max_cloud[1] = entry[1]; max_cloud[2] = entry[2];
                        max_cloud_idx[0] = c; max_cloud_idx[1] = r;
                    }
                }
            //}
        }
    }

    /*
     * Modify code to test: H=108, H does not get involved, Use weak cloud or not.
     */
    cout << "s_min_sky: " << static_cast<unsigned>(s_min_sky) 
         << " s_max_cloud: " << static_cast<unsigned>(s_max_cloud) << endl;

    cout << "min_sky at: ";
    printer->printPixelIndex(2, min_sky_idx);
    cout << "min_sky color: ";
    printer->printPixelColor(3, min_sky);

    cout << "max_cloud at: ";
    printer->printPixelIndex(2, max_cloud_idx);
    cout << "max_cloud color: ";
    printer->printPixelColor(3, max_cloud);
}

void sky_init_train::printTrainR() {
    for (int r=0; r<train.rows; r++) {
        cout << "row: " << r;
        cout << train.row(r) << endl;
    }
}

// We can mask the image 

// We print cloud pixels and sky pixels

// Is it related to abs values or positions/region?

// It seems the existing methods are masking the pre-defined areas.
// which means we need to find the range.

// Probably we define color based on objects.

// Can we use _00 to define the minimum difference between cloud and sky?
// 2024-05/9938 is another example.

// On that html color chart, as long as s=0 and v=100, color is always white no matter hue.

cv::Mat* sky_init_train::getMatrixTrain() {
    return &train;
}

cv::Mat* sky_init_train::getInputImage() {
    return &input;
}

cv::Mat* sky_init_train::getHsvImage() {
    return &hsvImage;
}