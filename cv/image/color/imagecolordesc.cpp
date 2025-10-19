#include <cassert>
#include <iostream>
#include <iterator>

#include "imagecolordesc.h"

using namespace std;

/// TODO Ready to a full test
/*
 * @20250914
 * setDescData() will build color_map, compact_color_map.
 * color value tree and hsv tree will be generated on demand by customer classes.
 */
 /*
  * @20250917
  * imagecolordesc: setDescData() is to store image matrix data in a color_map for 
  * future analysis.
  *
  * instance variable color_type is used to record the color type on the matrix, i.e.,
  * BGR, HSV or Masked matrix. Therefore each time setDescData() is called, we need
  * to tell setDescData() the color type and store it in color_type.
  *
  * color_type is set to NOT_AVAILABE in header file. Each setDescData() call will change
  * color_type accordingly. Neither init() or clear() will change color_type.
  */
  /*
   * @20250921
   * At this moment, we do not have any request to remove created tree without changing color_map,
   * i.e., calling of setDescData().
   */
imagecolordesc::imagecolordesc() {
    logger = new iapcv_log(typeid(this).name());
    init();
}

imagecolordesc::~imagecolordesc() {
    logger->setLevel(iapcv_log::ERROR);
    if (t != nullptr) {
        t->setLogLevel(iapcv_log::ERROR);
    }
    if (d3t != nullptr) {
        d3t->setLogLevel(iapcv_log::ERROR);
    }

    logger->debug("Destructing imagecolordesc. ");
    clear();

    printer = nullptr;
    calc = nullptr;
    convert = nullptr;

    rg = nullptr;
    delete logger;
}

void imagecolordesc::init() {
    color_map = new unordered_map<int, vector<int*>*>();
    //compact_map = new unordered_map<int, vector<int*>*>();
    
    /*
     * @20250914
     * Ready to use by customer classes.
     */
    t = new colorvaluetree();
    d3t = new d3tree();

    for (int i=0; i< 256; i++) {
        BH[i] = 0;
        GS[i] = 0;
        RV[i] = 0;
    }
}

void imagecolordesc::clear() {
    if (rg != nullptr) {
        rg->clear();
    }
    for (int i=0; i< 256; i++) {
        BH[i] = 0;
        GS[i] = 0;
        RV[i] = 0;
    }

    // Just cleared
    if (color_map==nullptr) {
        logger->info("Color Map is null.");
        assert(t == nullptr && d3t == nullptr);
        return;
    }
    // Just created.
    if (color_map->size()==0) {
        logger->info("Map is clear.");
        delete color_map;
        color_map = nullptr;
        
        if (t->size() > 0) {
            logger->error("Color value tree size: ", t->size());
            t->deleteTree();
        }
        delete t;
        t = nullptr;
        
        if (d3t->size() > 0) {
            logger->error("D3Tree size: ", d3t->size());
            d3t->deleteTree();
        }
        delete d3t;
        d3t = nullptr;
        
        return;
    }

    // Just used
    logger->debug("To destruct color map: size: ", color_map->size());
    
    /*
    for (auto it=(*color_map).begin(); it!=(*color_map).end();) {
        v = it->second;
        clearSTDVector(v);
        it = color_map->erase(it);
        delete v;
    }*/
    clearMap(*color_map);
    *color_map = unordered_map<int, std::vector<int*>*>();
    delete color_map;
    color_map = nullptr;

    /*
    if (compact_map->size() > 0) {
        clearMap(*compact_map);
        *compact_map = unordered_map<int, std::vector<int*>*>();
        delete compact_map;
        compact_map = nullptr;
    }*/
    
    if (t->size()>0) {
        t->deleteTree();
    }
    delete t;
    t = nullptr;
    if (d3t->size()>0) {
        d3t->deleteTree();
    }
    delete d3t;
    d3t = nullptr;
}

void imagecolordesc::clearMap(unordered_map<int, vector<int*>*>& m) {
    if (m.size()>0) {
        vector<int*>* v;
        for (auto it=m.begin(); it!=m.end();) {
            v = it->second;
            clearSTDVector(it->second);
            it = m.erase(it);
            delete v;
        }
    }
}

void imagecolordesc::clearSTDVector(vector<int*>* v) {
    logger->trace("Clear vector: vector size: ", v->size());
    
    int s = v->size();
    for (int i=0; i < s; i++) {
        delete v->at(i);
    }
    *v = vector<int*>();
    logger->trace("Clear vector: vector elements deleted.");
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

/**
 * Customer classes are responsible to release memory of newVec, example use auto.
 */
vector<uchar*> imagecolordesc::findPixelColors(uchar hue) {
    assert(color_type==ColorType::HSV);
    assert(d3t!=nullptr && d3t->getDimensionType()==DimType::HSV);
    return d3t->findValues(hue);
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
 * When setDescData() is called, it first checks color_map null since clear() can invalidate it.
 * If color_map is null, we call init().
 * Otherwise, we check size = 0.
 * If size = 0, instance just created.
 * If size > 0, we clear color_map and invalidate it.
 */
void imagecolordesc::setDescData(const cv::Mat& mat, ColorType type) {
    assert(mat.rows>0 && mat.cols>0);
    assert(type==ColorType::BGR || type==ColorType::HSV);
    color_type = type;

    // Just cleared
    if (color_map == nullptr) {
        logger->info("color_map is null.");
        init();
    }
    // color_map->size() == 0: Just constructed
    // Just used
    else if (color_map->size() > 0) { 
        logger->info("Clear image color desc.");
        clear();
        rg->clear();
        init();
    }
    
    W = mat.cols;
    H = mat.rows;
    std::vector<int*>* v = nullptr;
    cv::Vec<unsigned char, 3> entry;
    int key = 0;
    for (int i=0; i<mat.rows; i++) {
        for (int j=0; j<mat.cols; j++) {
            entry = mat.at<cv::Vec3b>(i,j);
            
            BH[static_cast<unsigned>(entry[0])]++;
            GS[static_cast<unsigned>(entry[1])]++; 
            RV[static_cast<unsigned>(entry[2])]++;

            key = convert->getInt(entry[0], entry[1], entry[2]);
            auto search = color_map->find(key);
            if (search == color_map->end()) {
                v = new vector<int*>();
                color_map->insert(make_pair(key, v));
                v->push_back(new int[]{i, j});
            }
            else {
                search->second->push_back(new int[]{i, j});
            }
        }
    } 
    
    setMinMax();          
}

void imagecolordesc::setColorValueTree() {
    // Just cleared
    if (color_map == nullptr) {
        logger->info("Data cleared. Can not set color value tree.");
        return;
    }
    // Just created
    if (color_map->size()==0) {
        logger->info("No data to set color value tree.");
        return;
    } 
    t->setLogLevel(this->logger->getLevel());
    logger->debug("Set color value tree.");
    
    t->setPrint(printer);
    int key = 0;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        key = it->first;
        std::vector<int*> value = *it->second;
        t->add(value.size(), key);
    }
}

void imagecolordesc::setD3Tree(DimType type, int dim) {
    if (ColorType::HSV == color_type && DimType::BGR == type) {
        logger->error("Unsupported operation.");
        return;
    }
    // Just cleared
    if (color_map == nullptr) {
        logger->info("Data cleared. Can not set d3tree.");
        return;
    }
    // Just created
    if (color_map->size()==0) {
        logger->info("No data to set d3tree.");
        return;
    } 
    logger->debug("Set d3tree.");
    if (d3t->size()>0) {
        d3t->deleteTree();
    }
    d3t->setLogLevel(this->logger->getLevel());
    d3t->setPrint(printer);
    d3t->setDim(type, dim);
    uchar arr[imagecolorvalues::channel] = {0}; 
    int key = 0;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        key = it->first;
        auto v3 = new uchar[imagecolorvalues::channel]{0};
        convert->setUChar3(key, arr);
        if (color_type == ColorType::BGR && type == DimType::HSV) {
            calc->toHsvCV(imagecolorvalues::channel, v3, arr[0], arr[1], arr[2]);
        }
        /*  Unsupported operation
        else if (color_type == ColorType::HSV && type == DimType::BGR) {            
        }
        */
        else {
            v3[0] = arr[0]; v3[1] = arr[1]; v3[2] = arr[2];
        }
        
        //printer->printPixelColor(imagecolorvalues::channel, hsv);
        d3t->add(imagecolorvalues::channel, v3);
    }
    logger->debug("D3Tree set up.");
}

/// TODO: test with all black and all white images
void imagecolordesc::setMinMax() {
    logger->debug("Set Min Max.");
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

    if (color_type==ColorType::BGR) {
        rg->setColorType(ColorType::BGR);
        rg->setBGRMin(bh_min, gs_min, rv_min);
    }
    else if (color_type==ColorType::HSV) {
        rg->setColorType(ColorType::HSV);
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

    if (color_type==ColorType::BGR) {
        rg->setColorType(ColorType::BGR);
        rg->setBGRMax(bh_max, gs_max, rv_max);
    }
    else if (color_type==ColorType::HSV) {
        rg->setColorType(ColorType::HSV);
        rg->setHSVMax(bh_max, gs_max, rv_max);
    }
}

/// TODO
/*
void imagecolordesc::setCompactMap() {
    if (color_map->size() == 0) {
        logger->info("Empty color map.");
        return;
    }

}
*/

void imagecolordesc::printMinMax() {
    cout << "color type: " << imagecolorvalues::getColorTypeVal(color_type) << endl;
    cout << "max: { " << static_cast<unsigned>(rg->getUpper()[0]) << " , " << static_cast<unsigned>(rg->getUpper()[1]) << " , " << static_cast<unsigned>(rg->getUpper()[2]) << " }" << endl;
    cout << "min: { " << static_cast<unsigned>(rg->getLower()[0]) << " , " << static_cast<unsigned>(rg->getLower()[1]) << " , " << static_cast<unsigned>(rg->getLower()[2]) << " }" << endl;   
}

void imagecolordesc::printMap() {
    int num = 0; 
    uchar p[] = {0, 0, 0};
    cout << "printMap: size: " << color_map->size() << " Color type: " << imagecolorvalues::getColorTypeVal(color_type) << endl;
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        convert->setUChar3(it->first, p);
        
        std::vector<int*> value = *it->second;

        cout << "Num of pixels: " << printer->formattedNumToStr(value.size()) << " " << " Key: " << printer->formattedNumToStr(it->first) << " ";
        cout << "Color: ";
        printer->printPixelColor(imagecolorvalues::channel, p);
        num+=value.size();
    }
    cout << "Number of pixels: " << num << endl;
}

void imagecolordesc::printColorValueTree() {
    t->printTree();
}

void imagecolordesc::printD3Tree() {
    d3t->printTree();
}

void imagecolordesc::printState() {
    cout << "Print imagecolordesc state." << endl;
    if (color_map == nullptr) {
        cout << "color_map: null" << endl;
    }
    else {
        cout << "Size of color_map: " << color_map->size() << endl;
    }
    if (t == nullptr) {
        cout << "color value tree: null" << endl;
    }
    else {
        cout << "Size of color value tree: " << t->size() << endl;
    }
    if (d3t == nullptr) {
        cout << "d3tree: null" << endl;
    } 
    else {
        cout << "Size of d3tree: " << d3t->size() << endl;
    }
    printMinMax();
}

bool imagecolordesc::verifyState(const color_desc_state& cst) {
    bool verified = true;
    if (cst.s_color_type != color_type ) {
        logger->error("color type: expected: ", imagecolorvalues::getColorTypeVal(cst.s_color_type));
        verified = false;
    }
    if (cst.s_color_map == ClearableState::just_cleared) {
        if (color_map != nullptr) {
            logger->error("color map state: expected: ", static_cast<int>(cst.s_color_map));
            verified = false;
        }
    } 
    else if (cst.s_color_map == ClearableState::just_created) {
        if (color_map == nullptr || color_map->size()>0) {
            logger->error("color map state: expected: ", static_cast<int>(cst.s_color_map));
            verified = false;
        }
    }
    else if (cst.s_color_map == ClearableState::just_used) {
        if (color_map == nullptr || color_map->size()==0) {
            logger->error("color map state: expected: ", static_cast<int>(cst.s_color_map));
            verified = false;
        }
    } 
    
    if (cst.s_tree_cvt == ClearableState::just_cleared) {
        if (t != nullptr) {
            logger->error("color value tree state: expected: ", static_cast<int>(cst.s_tree_cvt));
            verified = false;
        }
    } 
    else if (cst.s_tree_cvt == ClearableState::just_created) {
        if (t == nullptr || t->size()>0) {
            logger->error("color value tree state: expected: ", static_cast<int>(cst.s_tree_cvt));
            verified = false;
        }
    }
    else if (cst.s_tree_cvt == ClearableState::just_used) {
        if (t == nullptr || t->size()==0) {
            logger->error("color value tree state: expected: ", static_cast<int>(cst.s_tree_cvt));
            verified = false;
        }
    } 
    
    if (cst.s_tree_d3t == ClearableState::just_cleared) {
        if (d3t != nullptr) {
            logger->error("color value tree state: expected: ", static_cast<int>(cst.s_tree_d3t));
            verified = false;
        }
    } 
    else if (cst.s_tree_d3t == ClearableState::just_created) {
        if (d3t == nullptr || d3t->size()>0) {
            logger->error("color value tree state: expected: ", static_cast<int>(cst.s_tree_d3t));
            verified = false;
        }
    }
    else if (cst.s_tree_d3t == ClearableState::just_used) {
        if (d3t == nullptr || d3t->size()==0) {
            logger->error("color value tree state: expected: ", static_cast<int>(cst.s_tree_d3t));
            verified = false;
        }
    }  
    
    return verified;
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

void imagecolordesc::setRange(range* rg) {
    this->rg = rg;
}

/**
 * Return: Min value of h, s, and v from all the image pixels.
 */
uchar* imagecolordesc::getLowerBoundHSV() {
    assert(color_type==ColorType::HSV);
    return rg->getLower();
}

/**
 * Return: Max value of h, s, and v from all the image pixels.
 */
uchar* imagecolordesc::getUpperBoundHSV() {
    assert(color_type==ColorType::HSV);
    return rg->getUpper();
}

void imagecolordesc::getAllHue(std::vector<int>* vh) {
    if (vh == nullptr || d3t == nullptr ) {
        logger->info("Cannot get hue.");
        return;
    }
    d3t->getTreeData(vh);
}

int imagecolordesc::getImageSize() {
    return W*H;
}

void imagecolordesc::setLogLevel(int level) {
    logger->setLevel(level);
}

int imagecolordesc::countColor(int color) {
    assert(color_type==ColorType::BGR);
    if (color != imagecolorvalues::BLACK) {
        logger->info("Unsupported operation. Color: ", imagecolorvalues::getColorVal(color));
        return -1;
    }
    int count = 0;
    uchar bgr[imagecolorvalues::channel] = {0};
    for (auto it=color_map->begin(); it!=color_map->end(); it++) {
        convert->setUChar3(it->first, bgr);
        if (bgr[0]<=20 && bgr[1]<=20 && bgr[2] <=20) { /// TODO
            count+=it->second->size();
        }
    }
    logger->debug("Count of " + imagecolorvalues::getColorVal(color), count);
    return count;
}

ColorType imagecolordesc::getColorType() {
    return color_type;
}
