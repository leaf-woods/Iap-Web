#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "imagecolorvalues.h"
#include "hsvtree.h" 

using namespace std;

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
    logger->Debug("Created Node of: ", newNode->data, " at: ", newNode);
    return newNode;
}

HNode* hsvtree::insertNode(HNode* n, uchar* hsv)
{
    if (count == 0) {
        root = createNode(hsv);
        logger->Debug("Root created of data: ", root->data, " at: ", root);
        return root;
    }

    if (n == nullptr) {
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
    assert(hsv_dim==HUE || hsv_dim==SAT || hsv_dim==VAL);
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
        for (int i=0; i<n->vecHsv->size(); i++) {
            n->vecHsv->at(i)[0] = 0;
            n->vecHsv->at(i)[1] = 0;
            n->vecHsv->at(i)[2] = 0;
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

void hsvtree::printTree(HNode* n) {
    if (n == nullptr) {
        return;
    }
    cout << "HNode:" << n->data << " ";
    printer->printVector(n->vecHsv);

    printTree(n->left);
    printTree(n->right);
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
    cout << "Print hsvtree. Use hsv dimention: " << dim << " Size: " << count << endl;
    if (count == 0) {
        cout << "Empty tree." << endl;
        return;
    }

    if (root == nullptr) {
        cout << "Error occurred. Abort." << endl;
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

vector<uchar*>* hsvtree::findValues(int data) {
    if (root == nullptr) {
        logger->Info("Cannot find values for data: ", data);
    }
    HNode* n = abstree::findNode(root, data);
    if (n==nullptr) {
        return nullptr;
    }
    return n->vecHsv;
}

void hsvtree::getTreeData(vector<int>* vh) {
    if (vh==nullptr || root==nullptr) {
        logger->Info("Cannot get tree data.");
        return;
    }
    abstree::traverseData(root, vh);
}


