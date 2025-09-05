#include <cassert>
#include <iostream>
#include <iterator>

#include "imagecolordesc.h"

using namespace std;

imagecolordesc::imagecolordesc() {
    logger = new iapcv_log(typeid(this).name());
    init();
    /*
     * @20250826
     * Preserve color_type and hsv_dim when image color desc is reused.
     */
    color_type = 0;
    hsv_dim = hsvtree::HUE; /// TODO two variables not changed
}

imagecolordesc::~imagecolordesc() {
    logger->setLevel(iapcv_log::ERROR);
    t->setLogLevel(this->logger->getLevel());
    ht->setLogLevel(this->logger->getLevel());

    logger->debug("Destructing imagecolordesc. ");
    clear();

    printer = nullptr;
    calc = nullptr;
    convert = nullptr;

    rg = nullptr;
    delete logger;
}

void imagecolordesc::init() {
    color_map = new unordered_map<int, std::vector<int*>*>();
    t = new colorvaluetree();
    ht = new hsvtree();

    for (int i=0; i< 256; i++) {
        BH[i] = 0;
        GS[i] = 0;
        RV[i] = 0;
    }
}

void imagecolordesc::clear() {
    if (color_map==nullptr) {
        logger->info("Map is null.");
        assert(t == nullptr);
        assert(ht == nullptr);
        return;
    }
    // This is not a normal scenario as color_map size=0 only occurs when instance just created.
    if (color_map->size()==0) {
        logger->info("Map is clear.");
        delete color_map;
        color_map = nullptr;
        if (t != nullptr) {
            logger->warn("Color value tree size: ", t->size());            
            t->deleteTree();
            t = nullptr;
        }
        if (ht != nullptr) {
            logger->warn("HSV tree size: ", ht->size());
            ht->deleteTree();
            ht = nullptr;
        }
        return;
    }
    
    vector<int*>* v;
    logger->debug("To destruct map size: ", color_map->size());
    
    for (auto it=(*color_map).begin(); it!=(*color_map).end();) {
        v = it->second;
        clearSTDVector(v);
        it = color_map->erase(it);
        delete v;
    }

    *color_map = unordered_map<int, std::vector<int*>*>();
    delete color_map;
    color_map = nullptr;
    t->deleteTree();
    delete t;
    t = nullptr;
    ht->deleteTree();
    delete ht;
    ht = nullptr;
}

void imagecolordesc::clearSTDVector(vector<int*>* v) {
    logger->debug("clearSTDVector: vector size: ", v->size());
    
    int s = v->size();
    for (int i=0; i < s; i++) {
        delete v->at(i);
    }
    *v = vector<int*>();
    logger->debug("clearSTDVector: vector elements deleted.");
}

/**
 * Given a b value, return all bgr entries e where e.b = b.
 */
vector<uchar*>* imagecolordesc::findB(uchar b) {
    cout << "Find b value: " << static_cast<unsigned>(b) << endl; 
    int min = convert->getInt(b, rg->getLower()[1], rg->getLower()[2]);
    int max = convert->getInt(b, rg->getUpper()[2], rg->getUpper()[2]);

    vector<uchar*>* v = new vector<uchar*>();
    //uchar* bgr;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        if (it->first >= min && it->first <= max) {
            auto bgr = new uchar[3]();
            convert->setUChar3(it->first, bgr);
            v->push_back(bgr);
        }
    }
    return v;
}

vector<uchar*>* imagecolordesc::findPixelColors(uchar hue) {
    assert(color_type==imagecolorvalues::HSV);
    return ht->findValues(hue);
}

vector<int*>* imagecolordesc::containsBGR(uchar b, uchar g, uchar r) {
    int key = convert->getInt(b, g, r);
    // https://en.cppreference.com/w/cpp/container/unordered_map/find.html
    if (auto search = color_map->find(key); search != color_map->end())
        return search->second;
    else
        return nullptr;
}

string imagecolordesc::writeContents() {
    if (color_map==nullptr) {
        return nullptr;
    }
    string s = "W=";
    s.append(to_string(W));
    s.append(" H=");
    s.append(to_string(H));

    s.append("\nBH_MIN=");
    s.append(to_string(rg->getLower()[0]));
    s.append(" GS_MIN=");
    s.append(to_string(rg->getLower()[1]));
    s.append(" RV_MIN=");
    s.append(to_string(rg->getLower()[2]));
    s.append("\nBH_MAX=");
    s.append(to_string(rg->getUpper()[0]));
    s.append(" GS_MAX=");
    s.append(to_string(rg->getUpper()[1]));
    s.append(" RV_MAX=");
    s.append(to_string(rg->getUpper()[2]));

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

/*
 * Function setDescData() can be reused to set other matrix data without creating a new imagecolordesc instance.
 * 
 * Constructor: init() to create new instances.
 * Destructor: clear() to delete all resources.
 *
 * Function clear():
 * We invalidate color_map so it can not be accessed without calling init() to create a new instance.
 *
 * When setDesc() is called, it first checks color_map null since clear() can invalidate it.
 * If color_map is null, we call init().
 * Otherwise, we check size = 0.
 * If size = 0, instance just created.
 * If size > 0, we clear color_map and invalidate it.
 */
void imagecolordesc::setDescData(cv::Mat& mat) {
    assert(mat.rows>0 && mat.cols>0);
    if (color_map == nullptr ) { 
        init();
    }
    else if (color_map->size() == 0) {
        // Just constructed.
        assert(t!=nullptr && t->size()==0);
        assert(ht!=nullptr && ht->size()==0);
    }
    else {
        logger->info("Clear image color desc.");
        clear();
        rg->clear();
        init();
    }

    assert(color_type==imagecolorvalues::BGR || color_type==imagecolorvalues::HSV);
    
    W = mat.cols;
    H = mat.rows;
    std::vector<int*>* v;
    cv::Vec<unsigned char, 3> entry;
    int key = 0;
    for (int i=0; i<mat.rows; i++) {
        for (int j=0; j<mat.cols; j++) {
            entry = mat.at<cv::Vec3b>(i,j);
            
            BH[static_cast<unsigned>(entry[0])]++;
            GS[static_cast<unsigned>(entry[1])]++; 
            RV[static_cast<unsigned>(entry[2])]++;

            key = convert->getInt(entry[0], entry[1], entry[2]);
            if (auto search=color_map->find(key); search==color_map->end()) {
                v = new vector<int*>();
                color_map->insert(make_pair(key, v));
            }
            v->push_back(new int[]{i, j});
        }
    } 
    logger->debug("To set trees");
    
    t->setLogLevel(this->logger->getLevel());
    ht->setLogLevel(this->logger->getLevel());
    setColorValueTree();
    setHsvTree(); 
    setMinMax();          
}

void imagecolordesc::setColorValueTree() {
    assert(color_map->size()>0);
    logger->debug("Set color value tree.");
    
    t->setPrint(printer);
    int key = 0;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        key = it->first;
        std::vector<int*> value = *(it->second);
        t->add(value.size(), key);
    }
}

void imagecolordesc::setHsvTree() {
    logger->debug("Set hsv tree.");
    ht->setPrint(printer);
    ht->setHsvDim(hsv_dim);
    uchar arr[imagecolorvalues::channel] = {0}; 
    int key = 0;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        key = it->first;
        auto hsv = new uchar[imagecolorvalues::channel]{0};
        convert->setUChar3(key, arr);
        if (color_type == imagecolorvalues::BGR) {
            calc->toHsvCV(imagecolorvalues::channel, hsv, arr[0], arr[1], arr[2]);
        }
        else {
            hsv[0] = arr[0]; hsv[1] = arr[1]; hsv[2] = arr[2];
        }
        
        //printer->printPixelColor(hsv);
        ht->add(hsv);
    }
}

/// TODO: test with all black and all white images
void imagecolordesc::setMinMax() {
    uchar bh_max=0; uchar bh_min=255;
    uchar gs_max=0; uchar gs_min=255;
    uchar rv_max=0; uchar rv_min=255;

    uchar c;
    
    for (int i=0; i<256; i++) {
        c = convert->getUChar(i);
        c = c=='\0' ? 255 : c ; 
        if (bh_min==255 && BH[i] > 0) {
            bh_min = c;
        }
        if (gs_min==255 && GS[i] > 0) {
            gs_min = c;
        }
        if (rv_min==255 && RV[i] > 0) {
            rv_min = c;
        }
        if (bh_min < 255 && gs_min < 255 && rv_min < 255) {
            break;
        }
    }

    if (color_type==imagecolorvalues::BGR) {
        rg->setColorType(imagecolorvalues::BGR);
        rg->setBGRMin(bh_min, gs_min, rv_min);
    }
    else if (color_type==imagecolorvalues::HSV) {
        rg->setColorType(imagecolorvalues::HSV);
        rg->setHSVMin(bh_min, gs_min, rv_min);
    }

    for (int i=255; i>=0; i--) {
        c = convert->getUChar(i);
        c = c=='\0' ? 0 : c ;
        if (bh_max == 0 && BH[i] > 0) {
            bh_max = c;
        }
        if (gs_max == 0 && GS[i] > 0) {
            gs_max = c;
        }
        if (rv_max == 0 && RV[i] > 0) {
            rv_max = c;
        }
        if (bh_max > 0 && gs_max > 0 && rv_max > 0) {
            break;
        }
    }

    if (color_type==imagecolorvalues::BGR) {
        rg->setColorType(imagecolorvalues::BGR);
        rg->setBGRMax(bh_max, gs_max, rv_max);
    }
    else if (color_type==imagecolorvalues::HSV) {
        rg->setColorType(imagecolorvalues::HSV);
        rg->setHSVMax(bh_max, gs_max, rv_max);
    }
}

void imagecolordesc::printMinMax() {
    cout << "color type: " << imagecolorvalues::getColorTypeVal(color_type) << endl;
    cout << "max: { " << static_cast<unsigned>(rg->getUpper()[0]) << " , " << static_cast<unsigned>(rg->getUpper()[1]) << " , " << static_cast<unsigned>(rg->getUpper()[2]) << " }" << endl;
    cout << "min: { " << static_cast<unsigned>(rg->getLower()[0]) << " , " << static_cast<unsigned>(rg->getLower()[1]) << " , " << static_cast<unsigned>(rg->getLower()[2]) << " }" << endl;   
}

void imagecolordesc::printMap() {
    int num = 0; 
    string s;
    uchar p[] = {0, 0, 0};
    cout << "printMap: " << endl;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        convert->setUChar3(it->first, p);
        
        std::vector<int*> value = *(it->second);
        if (value.size() < 10) {
            s = "   " + to_string(value.size());
        }
        else if (value.size() < 100) {
            s = "  " + to_string(value.size());
        }
        else if (value.size() < 1000) {
            s = " " + to_string(value.size());
        }
        else {
            s = to_string(value.size());
        }

        cout << "Num of pixels: " << s << " ";
        cout << "Color: ";
        printer->printPixelColor(imagecolorvalues::channel, p);
        num+=value.size();
    }
    cout << "Number of pixels: " << num << endl;
}

void imagecolordesc::printColorValueTree() {
    t->printTree();
}

void imagecolordesc::printHsvTree() {
    ht->printTree();
}

void imagecolordesc::setPrint(iap_print* p) {
    printer = p;
}

void imagecolordesc::setConvertHSV(convert_bgrhsv* c) {
    calc = c;
}

void imagecolordesc::setConvertNum(convertnumber* c) {
    convert = c;
}

void imagecolordesc::setColorType(int ct) {
    assert(ct==imagecolorvalues::BGR || ct==imagecolorvalues::HSV);
    color_type = ct;
}

void imagecolordesc::setHsvDim(int hd) {
    assert(hd==hsvtree::HUE || hd==hsvtree::SAT || hsvtree::VAL);
    hsv_dim = hd;
}

void imagecolordesc::setRange(range* rg) {
    this->rg = rg;
}

/**
 * Return: Min value of h, s, and v from all the image pixels.
 */
uchar* imagecolordesc::getLowerBoundHSV() {
    assert(color_type==imagecolorvalues::HSV);
    return rg->getLower();
}

/**
 * Return: Max value of h, s, and v from all the image pixels.
 */
uchar* imagecolordesc::getUpperBoundHSV() {
    assert(color_type==imagecolorvalues::HSV);
    return rg->getUpper();
}

void imagecolordesc::getAllHue(std::vector<int>* vh) {
    if (vh == nullptr || ht == nullptr ) {
        logger->info("Cannot get hue.");
        return;
    }
    ht->getTreeData(vh);
}

int imagecolordesc::getImageSize() {
    return W*H;
}

void imagecolordesc::setLogLevel(int level) {
    logger->setLevel(level);
}

