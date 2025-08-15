// https://stackoverflow.com/questions/71883343/how-to-write-to-file-in-c
#include <fstream>
#include <iostream>
#include <sys/stat.h>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "../example1/imagecolordesc.h"

using namespace std;

inline bool exists(const string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

int main(int argc, char* argv[]) {

    string fname = "IMG_5003_S_CR_R1.JPG";
    cv::Mat input = cv::imread(fname);
 
    imagecolordesc desc;

    desc.setDescData(input);
    //desc.printMap();
    //desc.printColorValueTree();
    desc.setMinMax();
    //desc.printMinMax();
    
    string mcs = desc.getContents();
    cout << "Map contents: " << endl;
    cout << mcs << endl;
    cout << "Tree contents: " << endl;
    string tcs = desc.getColorValueTreeContents(); 
    cout << tcs << endl;
    cout << endl;

    std::size_t found = fname.find(".");
    if (found==std::string::npos) {
        cout << "Can not save data. Invalid file name: " << fname << endl;
        return 1;
    }
    
    string fn = fname.substr(0, found+1);
    fn = fn.append("dat");
    cout << "Writing to file: " << fn << endl;

    if (exists(fname)) {
        cout << "File: " << fn << " already exists. Abort." << endl;
        return 1;
    }
    ofstream f;
    f.open (fn);
    f << mcs << tcs;
    f.close();
    
    return 0;
}
