#include "convert_bgrhsv.h"
#include "iap_print.h"

#include <iostream>
#include <opencv2/core.hpp>

using namespace std;

int main(int argc, char* argv[]) {
    convert_bgrhsv* convert = new convert_bgrhsv();
    
    /* 
     * img64/IMG_4585_S_CR_R1_S64_00.JPG
     * First we use ImageMagick visually detect (4,8) is cloud pixel.
     * We calculate the hsv of this pixel.
     * Then we use H_min, S_min, V_min, H_max, 160, V_max to run cv/test/image/test_img_data in range test. 
     */
    uchar* hsv = new uchar[3]{0};
    uchar* bgr = new uchar[3]{145, 89, 54};
    cout << "(4, 8): 145, 89, 54" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    iap_print* print = new iap_print(); // Color [108, 160, 145]
    print->printPixelColor(hsv);
    cout << endl;
    
    bgr[0]=162; bgr[1]=110; bgr[2]=80;
    cout << "(4, 16): 162, 110, 80" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    print = new iap_print(); // Color [109, 129, 162]
    print->printPixelColor(hsv);  
    cout << endl;

    /*
     * We found cloud area is over masked by using S upper bound 160.
     * We use ImageMagick visually detect (9, 16) and (15, 14) that are sky pixels but detected as cloud pixels
     *    on masked image.
     * We calculate hsv of the two pixels and decrease S upper bound to 152 to run cv/test/image/test_img_data in range test. 
     */
    bgr[0]=144; bgr[1]=89; bgr[2]=58;
    cout << "(9, 16): 144, 89, 58" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    print = new iap_print(); // Color [109, 152, 144]
    print->printPixelColor(hsv);
    cout << endl;

    bgr[0]=149; bgr[1]=92; bgr[2]=60;
    cout << "(15, 14): 149, 92, 60" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    print = new iap_print(); // Color [109, 152, 149]
    print->printPixelColor(hsv);
    cout << endl;

    /*
     * We found central and bottom left area cloud is smaller but still overmasked. But top right area cloud area is not detected.
     * We use ImageMagick visually detect (4, 26) is sky but detected as cloud.
     * We found (19,4) is cloud but detected as sky, (20,4) is sky.
     * We found (8,16) is sky but detected as cloud.
     */
    bgr[0]=151; bgr[1]=94; bgr[2]=62;
    cout << "(4, 26): 151, 94, 62" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    print = new iap_print(); // Color [109, 150, 151]
    print->printPixelColor(hsv);
    cout << endl;

    // cloud
    bgr[0]=151; bgr[1]=93; bgr[2]=58;
    cout << "(19, 4): 151, 93, 58" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    print = new iap_print(); // Color [108, 157, 151]
    print->printPixelColor(hsv);
    cout << endl;

    // sky
    bgr[0]=146; bgr[1]=88; bgr[2]=53;
    cout << "(20, 4): 146, 88, 53" << endl;
    convert->toHsvCV(hsv, bgr[0], bgr[1], bgr[2]);
    print = new iap_print();
    print->printPixelColor(hsv);  // Color [108, 162, 146]
    cout << endl;

    /*
     * At this moment, we can't decrease S upper to run more tests since (20,4) is sky with S=162 and
     * (19,4) is cloud with S=157.
     * We deduct a conclution, with the same Hue, a sky pixel is at the bottom right of a cloud pixel on 
     * html color chart as shown in example5/cv-hue-108.png
     * We will mark all pixels with H = 108 on cv-hue-108.png
     */

     /*
      * @20250829
      * Although Point (19,4) which is a cloud not in range set above (S_min, 152), it is 
      * considered significantly from Point (20,4). Both points not in range set above.
      * At this moment, we manually define they are significantly as initial train data.
      * That is, we define critical difference base on Point(19,4) and (20,4) with Delta(S)=+5 and
      * Delta(V)=-5. See Issue4 for the observation for the difference between sky and cloud.
      */
     
    delete hsv;
    delete bgr;
    delete convert;
    delete print;
    return 0;
}
