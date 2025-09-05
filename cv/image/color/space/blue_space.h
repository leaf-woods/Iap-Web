#ifndef BLUE_SPACE_H
#define BLUE_SPACE_H

#include <opencv2/core.hpp>

/*
 * https://www.google.com/search?q=html+color+picker&rlz=1CAKWCM_enCA1044&oq=html+color+picker&gs_lcrp=EgZjaHJvbWUqDggAEEUYJxg7GIAEGIoFMg4IABBFGCcYOxiABBiKBTIGCAEQRRhAMgwIAhAAGEMYgAQYigUyBggDEEUYOzIHCAQQABiABDIHCAUQABiABDIHCAYQABiABDIHCAcQABiABNIBCTYwMDlqMGoxNagCDLACAfEFV59-LRWFVdvxBVeffi0VhVXb&sourceid=chrome&ie=UTF-8
 * H: 220 S=100, V=100 means "bluest", S=0, V=100 means "white"
 * which is, H: 220, the four corners are:
 * S=0, V=100 -> white, upper left
 * S=100, V=100 -> blue upper right
 * S=0, V=0 -> black bottom left
 * S=100, V=0 -> black bottom right                        
 */
class blue_space {
    private:
      /* @20250902 We pick up the bounds by visually detection on the html color chart. */
      static const int H_MIN = 180;
      static const int H_MAX = 280;

    public:
      bool isBlue(uchar h) {
          return false;
      }
};
#endif