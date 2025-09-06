#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "sky_init_train.h"

sky_init_train::sky_init_train() {
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
                    cv::Vec3b & color = mat.at<cv::Vec3b>(c, r);
                    color[OF_SKY]=1; color[OF_CLD]=0; color[OF_WCL]=0;
                    mat.at<cv::Vec3b>(cv::Point(c, r)) = color;
                }
            }
}

void sky_init_train::setupCloud(cv::Mat& mat, int row, int col_start, int col_end) {
            if (col_start == col_end) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(col_start, row);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=0;
                mat.at<cv::Vec3b>(cv::Point(col_start, row)) = color;
                return;
            }

            for (int i=col_start; i<=col_end; i++) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(i, row);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=0;
                mat.at<cv::Vec3b>(cv::Point(i, row)) = color;
            }
        }

void sky_init_train::setupWeakCloud(cv::Mat& mat, int row, int col_start, int col_end) {
            if (col_start == col_end) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(col_start, row);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=1;
                mat.at<cv::Vec3b>(cv::Point(col_start, row)) = color;
                return;
            }

            for (int i=col_start; i<=col_end; i++) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(i, row);
                color[OF_SKY]=0; color[OF_CLD]=1; color[OF_WCL]=1;
                mat.at<cv::Vec3b>(cv::Point(i, row)) = color;
            }
        }

void sky_init_train::setupSky(cv::Mat& mat, int row, int col_start, int col_end) {
            if (col_start == col_end) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(col_start, row);
                color[OF_SKY]=1; color[OF_CLD]=0; color[OF_WCL]=0;
                mat.at<cv::Vec3b>(cv::Point(col_start, row)) = color;
                return;
            }

            for (int i=col_start; i<=col_end; i++) {
                cv::Vec3b & color = mat.at<cv::Vec3b>(i, row);
                color[OF_SKY]=1; color[OF_CLD]=0; color[OF_WCL]=0;
                mat.at<cv::Vec3b>(cv::Point(i, row)) = color;
            }
        }

void sky_init_train::setup() {
            input = cv::imread(fname);
            cv::cvtColor(input, hsvImage, cv::COLOR_BGR2HSV);
            
            mat = input.clone();

            init(mat);

            // Row 0, Row 1: all sky
            
            // Row 2, Row 3, Row 4
            for (int r=2; r<5; r++) {
                setupWeakCloud(mat, r, 17, 19);
            }

            // Row 5, Row 6: all sky

            // Row 7
            setupWeakCloud(mat, 7, 16, 18);

            // Row 8
            setupCloud(mat, 8, 3, 14);
            setupCloud(mat, 8, 16, 22);

            // Row 9
            setupCloud(mat, 9, 0, 6);
            setupCloud(mat, 9, 17, 22);

            // Row 10
            setupCloud(mat, 10, 0, 7);
            setupCloud(mat, 10, 11, 18);
            setupCloud(mat, 10, 20, 22);

            // Row 11
            setupCloud(mat, 11, 0, 14);
            setupCloud(mat, 11, 16, 22);

            // Row 12
            setupWeakCloud(mat, 12, 0, 6);
            setupCloud(mat, 12, 7, 7);
            setupWeakCloud(mat, 12, 8, 10);
            setupCloud(mat, 12, 11, 12);
            setupWeakCloud(mat, 12, 13, 14);
            setupWeakCloud(mat, 12, 17, 17);
            setupCloud(mat, 12, 18, 23);

            // Row 13
            setupWeakCloud(mat, 13, 0, 2);
            setupCloud(mat, 13, 3, 5);
            setupWeakCloud(mat, 13, 6, 10);
            setupCloud(mat, 13, 11, 13);
            setupWeakCloud(mat, 13, 14, 14);
            setupCloud(mat, 13, 16, 22);

            // Row 14
            setupCloud(mat, 14, 0, 6);
            setupWeakCloud(mat, 14, 8, 8);
            setupCloud(mat, 14, 11, 13);
            setupCloud(mat, 14, 17, 23);
            setupWeakCloud(mat, 14, 24, 25);

            // Row 15
            setupCloud(mat, 15, 0, 6);
            setupWeakCloud(mat, 15, 7, 7);
            setupWeakCloud(mat, 15, 12, 13);
            setupCloud(mat, 15, 17, 23);
            setupWeakCloud(mat, 15, 24, 25);

            // Row 16
            setupCloud(mat, 16, 0, 6);
            setupWeakCloud(mat, 16, 7, 8);
            setupWeakCloud(mat, 16, 12, 17);
            setupCloud(mat, 16, 18, 25);
            setupWeakCloud(mat, 16, 26, 28);

            // Row 17
            setupCloud(mat, 17, 0, 6);
            setupWeakCloud(mat, 17, 7, 8);
            setupWeakCloud(mat, 17, 12, 18);
            setupCloud(mat, 17, 21, 25);
            setupWeakCloud(mat, 17, 26, 28);

            // Row 18
            setupCloud(mat, 18, 0, 6);
            setupWeakCloud(mat, 18, 7, 8);
            setupWeakCloud(mat, 18, 12, 18);
            setupCloud(mat, 18, 21, 25);
            setupWeakCloud(mat, 18, 26, 28);

            // Row 19
            setupCloud(mat, 19, 0, 6);
            setupCloud(mat, 19, 10, 16);
            setupCloud(mat, 19, 22, 26);           
            setupWeakCloud(mat, 19, 27, 28);

            // Row 20
            setupCloud(mat, 20, 0, 7);
            setupCloud(mat, 20, 10, 16);
            setupWeakCloud(mat, 20, 18, 22);
            setupCloud(mat, 20, 23, 26);
            setupWeakCloud(mat, 20, 27, 30);

            // Row 21
            setupCloud(mat, 21, 0, 7);
            setupWeakCloud(mat, 21, 10, 16);
            setupWeakCloud(mat, 21, 19, 21);
            setupWeakCloud(mat, 21, 23, 24);
            setupCloud(mat, 21, 25, 27);
            setupWeakCloud(mat, 21, 28, 31);

            // Row 22
            setupCloud(mat, 22, 0, 9);
            setupWeakCloud(mat, 22, 10, 16);
            setupCloud(mat, 22, 19, 21);
            setupCloud(mat, 22, 24, 28);

            // Row 23
            setupCloud(mat, 23, 0, 0);
            setupWeakCloud(mat, 23, 2, 2);
            setupCloud(mat, 23, 5, 6);
            setupWeakCloud(mat, 23, 7, 7);
            setupWeakCloud(mat, 23, 9, 15);
            setupWeakCloud(mat, 23, 19, 19);
            setupWeakCloud(mat, 23, 25, 28);

            // Row 24
            setupCloud(mat, 24, 0, 1);
            setupWeakCloud(mat, 24, 2, 4);
            setupWeakCloud(mat, 24, 6, 8);
            setupWeakCloud(mat, 24, 22, 23);
            setupCloud(mat, 24, 24, 27);
            setupWeakCloud(mat, 24, 28, 28);

            // Row 25
            setupCloud(mat, 25, 0, 1);
            setupWeakCloud(mat, 25, 2, 2);
            setupWeakCloud(mat, 25, 6, 7);
            setupWeakCloud(mat, 25, 22, 23);
            setupWeakCloud(mat, 25, 28, 29);

            // Row 26
            setupWeakCloud(mat, 26, 0, 2);
            setupWeakCloud(mat, 26, 22, 25);

            // Row 27
            setupWeakCloud(mat, 27, 0, 5);
            setupWeakCloud(mat, 27, 10, 14);
            setupWeakCloud(mat, 27, 23, 25);
            setupCloud(mat, 27, 30, 31);

            // Row 28
            setupWeakCloud(mat, 28, 0, 5);
            setupWeakCloud(mat, 28, 8, 8);
            setupCloud(mat, 28, 10, 11);
            setupCloud(mat, 28, 12, 14);
            setupCloud(mat, 28, 23, 25);
            setupCloud(mat, 28, 30, 31);

            // Row 29
            setupWeakCloud(mat, 29, 0, 8);
            setupCloud(mat, 29, 10, 11);
            setupCloud(mat, 29, 14, 15);
            setupCloud(mat, 29, 24, 27);

            // Row 30
            setupCloud(mat, 30, 0, 4);
            setupCloud(mat, 30, 10, 11);
            setupCloud(mat, 30, 14, 15);
            setupCloud(mat, 30, 25, 29);

            // Row 31
            setupCloud(mat, 31, 0, 4);
            setupCloud(mat, 31, 5, 8);
            setupCloud(mat, 31, 9, 10);

            for (int r=0; r<mat.rows; r++) {
                for (int c=0; c<mat.cols; c++ ) {
                   cv::Vec3b & color = mat.at<cv::Vec3b>(c, r);
                    int bgr = getInt(color[0], color[1], color[2]);
                    //cout << "row: " << r << " col: " << c << " bgr: " << bgr << endl;
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
                cv::Vec<unsigned char, 3> entry_2 = mat.at<cv::Vec3b>(c, r);
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

// We can mask the image 

// We print cloud pixels and sky pixels

// Is it related to abs values or positions/region?

// It seems the existing methods are masking the pre-defined areas.
// which means we need to find the range.

// Probably we define color based on objects.

// Can we use _00 to define the minimum difference between cloud and sky?
// 2024-05/9938 is another example.

// On that html color chart, as long as s=0 and v=100, color is always white no matter hue.
