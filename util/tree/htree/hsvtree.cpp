#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "hsvtree.h" 

using namespace std;

hsvtree::hsvtree() {
    count = 0;
    root = nullptr;
}

hsvtree::~hsvtree() {
    if (DEBUG) {
        cout << endl;
        cout << DEBUG_H << "Destructing hsvtree: root at: " << root << endl;
    }
    if (count > 0) {
        deleteTree(root);
    }
    if (DEBUG) {
        cout << DEBUG_H << "Root at: " << root << endl;
        assert(!root);
    }

    /*
     * @20250821
     * Variable printer is injected using a setter. Therefore we don't release it here.
     */
    printer = nullptr;
}

HNode* hsvtree::createNode(uchar* hsv)
{
    HNode* newNode = new HNode();
    newNode->data = hsv[0];
    newNode->left = newNode->right = nullptr;
    newNode->vecHsv = new vector<uchar*>();
    newNode->vecHsv->push_back(hsv);

    count++;
    if (DEBUG) {
        cout << DEBUG_H << "Created node of: " << newNode->data << " at: " << newNode << endl;
    }
    return newNode;
}

HNode* hsvtree::insertNode(HNode* n, uchar* hsv)
{
    if (count == 0) {
        root = createNode(hsv);
        if (DEBUG) {
            cout << DEBUG_H << "Root created of data: " << root->data << " at: " << root << endl;
        }
        return root;
    }

    if (n == nullptr) {
        n = createNode(hsv);
        return n;
    }

    if (hsv[0] < n->data) {
        n->left = insertNode(n->left, hsv);
    }
    else if (hsv[0] > n->data) { 
        n->right = insertNode(n->right, hsv);
    }
    else {
        // No new node is created. We add an entry in node n->vecHsv
        if (DEBUG) {
            cout << DEBUG_H << "Data exists. Add hsv to existing vector. ";
            printer->printPixelColor(hsv);
        }
        n->vecHsv->push_back(hsv);
    }

    return n;
}

void hsvtree::add(uchar* hsv) {
    if (hsv[0] < 0 ) {
        cout << "Can not add data. Invalid data: " << static_cast<unsigned>(hsv[0])  << endl;
        return;
    }
    insertNode(root, hsv);
}

void hsvtree::deleteTree(HNode* n) {
    if (n == nullptr) {
        return;
    }

    if (DEBUG) {
        cout << DEBUG_H << "Delete left child of node: " << n->data << endl;
    }
    deleteTree(n->left);
    
    if (DEBUG) {
        cout << DEBUG_H << "Delete right child of node: " << n->data << endl;
    }
    deleteTree(n->right);

    if (DEBUG) {
        cout << DEBUG_H << "Delete node: " << n->data << endl;
    }

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
    if (DEBUG) {
        cout << DEBUG_H << "Current size: " << count << endl;
        if (count == 0) {
            cout << "Root deleted at addr:" << root << endl;
            assert(!root);
        }
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
        cout << "Empty tree." << endl;
        assert(!root);
        return;
    }

    cout << "Deleting hsvtree." << endl;    
    deleteTree(root);
    cout << "Tree deleted. Root: " << root << endl;
}

void hsvtree::printTree() {
    cout << "Print tree: size: " << count << endl;
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


