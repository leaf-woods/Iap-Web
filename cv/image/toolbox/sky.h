#ifndef SKY_H
#define SKY_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "blue_space.h"
#include "iapcv_log.h"
#include "imagecontext.h"
#include "status.h"

class sky {
    private:
        iapcv_log* logger;
        blue_space* blue;
        imagecontext* ctx;

    public:
        sky();
        ~sky();

        void setLogLevel(int level);
        void setBlueSpace(blue_space* blue);
        void setImageContext(imagecontext* ctx);
        
        b_status* isSky(std::string imageName);

};
#endif