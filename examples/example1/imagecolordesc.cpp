#include <iostream>
#include <iterator>

#include "imagecolordesc.h"

using namespace std;

imagecolordesc::imagecolordesc() : DEBUG_H("Debug - "),WARN_H("Warn - "){
    color_map = new unordered_map<int, std::vector<int*>*>();
    convert = new convertnumber();
    t = new colorvaluetree();

    r_max=0; g_max=0; b_max=0; 
    r_min=255; g_min=255; b_min=255;

    for (int i=0; i< 256; i++) {
        B[i] = 0;
        G[i] = 0;
        R[i] = 0;
    }
}

/// TODO DEBUG
imagecolordesc::~imagecolordesc() {
    if (DEBUG) {
        cout << endl;
        cout << DEBUG_H << "Destructing imagecolordesc. " << endl;
    }
    std::vector<int*>* v;

    //cout << "To destruct map." << endl;
    //cout << "map size: " << color_map->size() << endl;
    for (auto it=(*color_map).begin(); it!=(*color_map).end();) {
        v = it->second;
        clearSTDVector(v);
        it = color_map->erase(it);
        delete v;
    }
    
    *color_map =  unordered_map<int, std::vector<int*>*>();
    delete color_map;
    delete convert;
    t->deleteTree();
    delete t;
}

void imagecolordesc::clearSTDVector(std::vector<int*>* v) {
    //cout << "clearSTDVector: vector size: " << v->size() << endl;
    int s = v->size();
    for (int i=0; i < s; i++) {
        delete v->at(i);
    }
    *v = vector<int*>();
    //cout << "clearSTDVector: vector elements deleted." << endl;
    //cout << "clearSTDVector: size: " << v->size() << endl;
}

string imagecolordesc::writeContents() {
    if (color_map==nullptr) {
        return nullptr;
    }
    string s = "W=";
    s.append(to_string(W));
    s.append(" H=");
    s.append(to_string(H));

    s.append("\nB_MIN=");
    s.append(to_string(b_min));
    s.append(" G_MIN=");
    s.append(to_string(g_min));
    s.append(" R_MIN=");
    s.append(to_string(r_min));
    s.append("\nB_MAX=");
    s.append(to_string(b_max));
    s.append(" G_MAX=");
    s.append(to_string(g_max));
    s.append(" R_MAX=");
    s.append(to_string(r_max));

    s.append("\nm size=");
    s.append(to_string(color_map->size()));
    s.append("\n");

    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        s.append("K=");
        s.append(to_string(it->first));
        s.append(" N=");
        s.append(to_string(it->second->size()));
        s.append("\n");
    }
    return s;
}

string imagecolordesc::writeColorValueTreeContents() {
    return t->getContents();
}

void imagecolordesc::setDescData(cv::Mat& mat) {
    W = mat.cols;
    H = mat.rows;
    std::vector<int*>* v;
    cv::Vec<unsigned char, 3> entry;
    for (int i=0; i<mat.rows; i++) {
        for (int j=0; j<mat.cols; j++) {
            entry = mat.at<cv::Vec3b>(i,j);
            
            B[static_cast<unsigned>(entry[0])]++;
            G[static_cast<unsigned>(entry[1])]++; 
            R[static_cast<unsigned>(entry[2])]++;

            int key = convert->getInt(entry[0], entry[1], entry[2]);
            if (auto search=color_map->find(key); search==color_map->end()) {
                v = new std::vector<int*>();
                color_map->insert(std::make_pair(key, v));
            }
            v->push_back(new int[]{i, j});
        }
    } 
    setColorValueTree(); 
    setMinMax();          
}

void imagecolordesc::setColorValueTree() {
    cout << "Set color value tree." << endl;
    int key = 0;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        key = it->first;
        std::vector<int*> value = *(it->second);
        t->add(value.size(), key);
    }
}

/// TODO: test with all black and all white images
void imagecolordesc::setMinMax() {
    uchar c;
    
    for (int i=0; i<256; i++) {
        c = convert->getUChar(i);
        c = c=='\0' ? 255 : c ; 
        if (b_min==255 && B[i] > 0) {
            b_min = c;
        }
        if (g_min==255 && G[i] > 0) {
            g_min = c;
        }
        if (r_min==255 && R[i] > 0) {
            r_min = c;
        }
        if (b_min < 255 && g_min < 255 && r_min < 255) {
            break;
        }
    }

    for (int i=255; i>=0; i--) {
        c = convert->getUChar(i);
        c = c=='\0' ? 0 : c ;
        if (b_max == 0 && B[i] > 0) {
            b_max = c;
        }
        if (g_max == 0 && G[i] > 0) {
            g_max = c;
        }
        if (r_max == 0 && R[i] > 0) {
            r_max = c;
        }
        if (b_max > 0 && g_max > 0 && r_max > 0) {
            break;
        }
    }
}

void imagecolordesc::printPixelIndex(int* array) {
    cout << "[" << array[0] << ", " << array[1] << "]" << endl;
}

void imagecolordesc::printBGR(uchar* array) {
    cout << "BGR: [" << static_cast<unsigned>(array[0]) << ", " << static_cast<unsigned>(array[1]) << ", " << static_cast<unsigned>(array[2]) << "]" << endl;
}

void imagecolordesc::printMinMax() {
    cout << "b_max: " << static_cast<unsigned>(b_max) << " g_max: " << static_cast<unsigned>(g_max) << " r_max: " << static_cast<unsigned>(r_max) << endl;
    cout << "b_min: " << static_cast<unsigned>(b_min) << " g_min: " << static_cast<unsigned>(g_min) << " r_min: " << static_cast<unsigned>(r_min) << endl;   
}

void imagecolordesc::printMap() {
    int num = 0; 
    string s;
    uchar p[] = {0, 0, 0};
    cout << "printMap: " << endl;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        convert->setBGR(it->first, p);
        
        std::vector<int*> value = *(it->second);
        if (value.size() < 10) {
            s = "   " + std::to_string(value.size());
        }
        else if (value.size() < 100) {
            s = "  " + std::to_string(value.size());
        }
        else if (value.size() < 1000) {
            s = " " + std::to_string(value.size());
        }
        else {
            s = std::to_string(value.size());
        }

        cout << "Num of pixels: " << s << " ";
        printBGR(p);
        num+=value.size();
    }
    cout << "Number of pixels: " << num << endl;
}

void imagecolordesc::printColorValueTree() {
    t->printTree();
}

