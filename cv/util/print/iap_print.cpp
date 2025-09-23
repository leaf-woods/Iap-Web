#include <iostream>

#include "iap_print.h" 

using namespace std;

void iap_print::printVector(const vector<uchar*>& v) {
    cout << " Vector: { ";
    for (int i=0; i < (int)v.size(); i++) {
        cout << "[" << static_cast<unsigned>(v.at(i)[0]) << ", " 
             << static_cast<unsigned>(v.at(i)[1]) << ", " 
             << static_cast<unsigned>(v.at(i)[2]) << "] ";
    }
    cout << " }" << endl;
}

void iap_print::printVector(const vector<int>& v) {  
    cout << " Vector: { ";
    for (int i=0; i < (int)v.size(); i++) {
       cout << v.at(i) << " "; 
    }
    cout << " }" << endl;
}

void iap_print::printVector(const vector<unsigned char*>& v, bool fixed_len) {
    if (fixed_len) {
        printVector(v);
        return;
    }

    int count = 0;
    cout << " Vector: { ";
    for (int i=0; i < (int)v.size(); i++) {
       count = check_size(v.at(i));
       cout << "unsigned char array length: [" << count << "] ";
       for (int j=0; j<count; j++) {
           cout <<  static_cast<unsigned>(v.at(i)[j]) << ", ";
       }
       cout << " ; ";
    }
    cout << " }" << endl;
}

// https://stackoverflow.com/questions/4180818/finding-the-length-of-a-character-array-in-c
int iap_print::check_size(unsigned char *ptr)
{
    int offset = 0;
    //int count = 0;

    while (*(ptr + offset) != '\0')
    {
        //++count;
        ++offset;
    }
    return offset;
}

void iap_print::printPixelColor(size_t channel, uchar* array) {
    cout << "Color [" << static_cast<unsigned>(array[0]) << ", " << static_cast<unsigned>(array[1]) << ", " << static_cast<unsigned>(array[2]) << "]" << endl;
}

void iap_print::printPixelColor(cv::Vec<unsigned char, 3> entry, string type) {
    cout << type << " [" << static_cast<unsigned>(entry[0]) << ", " << static_cast<unsigned>(entry[1]) << ", " << static_cast<unsigned>(entry[2]) << "]" << endl;
}

void iap_print::printKV(int key, int value) {
    cout << "{ " << key << ", " << value << " }" << endl;
}

void iap_print::printPixelIndex(size_t dim, int* array) {
    cout << "[" << array[0] << ", " << array[1] << "]" << endl;
}

string iap_print::formattedNumToStr(int num) {
    ostringstream ostrm;
    if (num < 10) {
        string p = "       ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    if (num < 100) {
        string p = "      ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    if (num < 1000) {
        string p = "     ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    if (num < 10000) {
        string p = "    ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    if (num < 100000) {
        string p = "   ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    if (num < 1000000) {
        string p = "  ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    if (num < 10000000) {
        string p = " ";
        ostrm << string(p) << num;
        return ostrm.str();
    }
    return to_string(num);
    
}
