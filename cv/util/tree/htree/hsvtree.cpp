#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "imagecolorvalues.h"
#include "hsvtree.h" 

using namespace std;

/*
 * We ensure when count = 0, root is nullptr.
 */
hsvtree::hsvtree() {
    logger = new iapcv_log(typeid(this).name());
    count = 0;
    root = nullptr;
    hsv_dim = HUE;
}

hsvtree::~hsvtree() {
    logger->Debug("Destructing hsvtree: root at: ", root);
    if (count > 0) {
        deleteTree(root);
    }
    logger->Debug("Root at: ", root);
    assert(!root);

    /*
     * @20250821
     * Variable printer is injected using a setter. Therefore we don't release it here.
     */
    printer = nullptr;

    delete logger;
}

HNode* hsvtree::createNode(uchar* hsv)
{
    HNode* newNode = new HNode();
    newNode->data = hsv[hsv_dim];
    newNode->left = newNode->right = nullptr;
    newNode->vecHsv = new vector<uchar*>();
    newNode->vecHsv->push_back(hsv);

    count++;
    logger->fDebug("snsp", "Created Node of: ", newNode->data, " at: ", newNode);
    return newNode;
}

HNode* hsvtree::insertNode(HNode* n, uchar* hsv)
{
    if (count == 0) {
        root = createNode(hsv);
        logger->fDebug("snsp", "Root created of data: ", root->data, " at: ", root);
        return root;
    }

    if (n == nullptr) {  /// TODO not reachable?
        n = createNode(hsv);
        return n;
    }

    if (hsv[hsv_dim] < n->data) {
        n->left = insertNode(n->left, hsv);
    }
    else if (hsv[hsv_dim] > n->data) { 
        n->right = insertNode(n->right, hsv);
    }
    else {
        // No new node is created. We add an entry in node n->vecHsv
        logger->Debug("Data exists. Add hsv to existing vector. ");
        if (logger->isDebug()) {
            printer->printPixelColor(imagecolorvalues::channel, hsv);
        }
        n->vecHsv->push_back(hsv);
    }

    return n;
}

void hsvtree::add(uchar* hsv) {
    insertNode(root, hsv);
}

void hsvtree::deleteTree(HNode* n) {
    if (n == nullptr) {
        return;
    }

    logger->Debug("Delete left child of node: ", n->data);
    deleteTree(n->left);
    logger->Debug("Delete right child of node: ", n->data);
    deleteTree(n->right);
    logger->Debug("Delete node: ", n->data);

    if (n == root) {
        root = nullptr;
    }
    
    n->data = 0;
    if (n->vecHsv != nullptr) {
        for (int i=0; i < (int)n->vecHsv->size(); i++) {
            /* @20250821 Parameter uchar* is passed to function add(),
             * therefore it is not our responsibility to handle the 
             * memory release.
             */
            //cout << "type: " << typeid(n->vecHsv->at(i)).name() << endl;
            //delete n->vecHsv->at(i);
            n->vecHsv->at(i) = nullptr;
        }
        

        *n->vecHsv = vector<uchar*>();
        delete n->vecHsv;
    }
    n->left = nullptr;
    n->right = nullptr;
    delete n;
    n = nullptr;
    
    count--;
    logger->Debug("Current size: ", count);
    if (count == 0) {
        logger->Debug("Root deleted at addr:", root);
        assert(!root);
    }
}

void hsvtree::deleteTree() {
    if (count == 0) {
        logger->Info("Empty tree.");
        assert(!root);
        return;
    }
    logger->Debug("Deleting hsvtree.");
    deleteTree(root);
    logger->Debug("Tree deleted. Root: ", root);
}

void hsvtree::printTree(HNode* n) {
    if (n == nullptr) {
        return;
    }
    cout << "HNode:" << n->data << " ";
    printer->printVector(*n->vecHsv);

    printTree(n->left);
    printTree(n->right);
}

void hsvtree::printTree() {
    string dim;
    if (hsv_dim==HUE) {
        dim = "HUE";
    }
    else if (hsv_dim==SAT) {
        dim = "SAT";
    }
    else if (hsv_dim==VAL) {
        dim = "VAL";
    }
    cout << "Print hsvtree. Use hsv dimension: " << dim << " Size: " << count << endl;
    if (count == 0) {
        cout << "Empty tree." << endl;
        assert(!root);
        return;
    }

    printTree(root);
    cout << "Print tree completed." << endl;
    cout << endl;
}

int hsvtree::getMaxValue() {
    return abstree::getMaxValue(root);
}

void hsvtree::setHsvDim(int hd) {
    assert(hd==HUE || hd==SAT || hd==VAL);
    hsv_dim = hd;
}

vector<uchar*> hsvtree::findValues(int data) {
    if (root == nullptr) {
        throw logic_error( "Function findValues: Invalid tree state: root is null." );
    }
    HNode* n = abstree::findNode(root, data);
    if (n==nullptr) {
        return vector<uchar*>();
    }  
    return copyVecFast(* n->vecHsv);
}

void hsvtree::getTreeData(vector<int>* vh) {
    if (vh == nullptr) {
        throw invalid_argument( "Function getTreeData: Null pointer argument." );
    }
    if (vh->size() != 0) {
        throw invalid_argument( "Function getTreeData: Argument vector is not empty." );
    }
    if (root==nullptr) {
        throw logic_error( "Function getTreeData: Invalid tree state: root is null." );
    }
    abstree::traverseData(root, vh);
}

int hsvtree::getHSVDim() {
    return hsv_dim;
}

//https://stackoverflow.com/questions/644673/is-it-more-efficient-to-copy-a-vector-by-reserving-and-copying-or-by-creating-a
/*
 * Shallow copy i.e., create a set of pointers in newVec pointing to the same contents as orginal.
 */
 /**
  * Customer classes are responsible to release memory of newVec, example use auto.
  */
vector<uchar*> hsvtree::copyVecFast(const vector<uchar*>& original)
{
  std::vector<uchar*> newVec;
  newVec.reserve(original.size());
  copy(original.begin(), original.end(), back_inserter(newVec));
  return newVec;
}





