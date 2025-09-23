#include <cassert>
#include <iostream>

#include <opencv2/core.hpp>

#include "imagecolorvalues.h"
#include "d3tree.h" 

using namespace std;

/*
 * We ensure when count = 0, root is nullptr.
 *
 * There is no restriction on size of v3. We suppose it is 3-elelment unsigned char array.
 */
d3tree::d3tree() {
    logger = new iapcv_log(typeid(this).name());
    count = 0;
    root = nullptr;
    dim = dimensions::D_X;
}

d3tree::~d3tree() {
    logger->Debug("Destructing d3tree: root at: ", root);
    if (count > 0) {
        deleteTree(root);
    }
    logger->Debug("Root at: ", root);
    assert(!root);

    printer = nullptr;

    delete logger;
}

D3Node* d3tree::createNode(unsigned char* v3)
{
    D3Node* newNode = new D3Node();
    newNode->data = v3[dim];
    newNode->left = newNode->right = nullptr;
    newNode->vec = new vector<unsigned char*>();
    newNode->vec->push_back(v3);

    count++;
    logger->fTrace("snsp", "Created Node of: ", newNode->data, " at: ", newNode);
    return newNode;
}

D3Node* d3tree::insertNode(D3Node* n, unsigned char* v3)
{
    if (count == 0) {
        root = createNode(v3);
        logger->fTrace("snsp", "Root created of data: ", root->data, " at: ", root);
        return root;
    }

    if (n == nullptr) {
        n = createNode(v3);
        return n;
    }

    if (v3[dim] < n->data) {
        n->left = insertNode(n->left, v3);
    }
    else if (v3[dim] > n->data) { 
        n->right = insertNode(n->right, v3);
    }
    else {
        logger->Trace("Data exists. Add v3 to existing vector of Data: ", n->data);
        if (logger->getLevel()==iapcv_log::TRACE) {
            printer->printPixelColor(imagecolorvalues::channel, v3);
        }
        n->vec->push_back(v3);
    }

    return n;
}

void d3tree::add(size_t s, unsigned char* v3) {
    assert(V_LEN == s);
    insertNode(root, v3);
}

void d3tree::deleteTree(D3Node* n) {
    if (n == nullptr) {
        return;
    }

    logger->Trace("Delete left child of node: ", n->data);
    deleteTree(n->left);
    logger->Trace("Delete right child of node: ", n->data);
    deleteTree(n->right);
    logger->Trace("Delete node: ", n->data);

    if (n == root) {
        root = nullptr;
    }
    
    n->data = 0;
    if (n->vec != nullptr) {
        for (int i=0; i < (int)n->vec->size(); i++) {
            n->vec->at(i) = nullptr;
        }
        
        *n->vec = vector<unsigned char*>();
        delete n->vec;
    }
    n->left = nullptr;
    n->right = nullptr;
    delete n;
    n = nullptr;
    
    count--;
    logger->Trace("Current size: ", count);
    if (count == 0) {
        logger->Debug("Root deleted at addr:", root);
        assert(!root);
    }
}

void d3tree::deleteTree() {
    if (count == 0) {
        logger->Info("Empty tree.");
        assert(!root);
        return;
    }
    logger->Debug("Deleting d3tree.");
    deleteTree(root);
    logger->Debug("Tree deleted. Root: ", root);
}

void d3tree::printTree(D3Node* n) {
    if (n == nullptr) {
        return;
    }
    cout << "D3Node:" << n->data << " ";
    printer->printVector(*n->vec);

    printTree(n->left);
    printTree(n->right);
}

void d3tree::printTree() {
    cout << "Print d3tree. Use dimension: " << dimensions::toString(type) << " : " << dimensions::toString(type, dim) << endl;
    cout << "Size: " << count << endl;
    if (count == 0) {
        cout << "Empty tree." << endl;
        assert(!root);
        return;
    }

    printTree(root);
    cout << "Print tree completed." << endl;
    cout << endl;
}

int d3tree::getMaxValue() {
    return abstree::getMaxValue(root);
}

void d3tree::setDim(DimType type, int d) {
    if (count > 0) {
        logger->error("Tree is not empty. Cannot change dimension type or dimension.");
        return;
    }
    assert(type==DimType::XYZ || type==DimType::HSV || type==DimType::BGR);
    assert(d==dimensions::D_X || d==dimensions::D_Y || d==dimensions::D_Z);
    this->type = type;
    dim = d;
}

vector<unsigned char*> d3tree::findValues(int data) {
    if (root == nullptr) {
        throw logic_error( "Function findValues: Invalid tree state: root is null." );
    }
    D3Node* n = abstree::findNode(root, data);
    if (n==nullptr) {
        return vector<uchar*>();
    }  
    return copyVecFast(* n->vec);
}

void d3tree::getTreeData(vector<int>* vh) {
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

int d3tree::getDim() {
    return dim;
}

DimType d3tree::getDimensionType(){
    return type;
}

//https://stackoverflow.com/questions/644673/is-it-more-efficient-to-copy-a-vector-by-reserving-and-copying-or-by-creating-a
/*
 * Shallow copy i.e., create a set of pointers in newVec pointing to the same contents as orginal.
 */
 /**
  * Customer classes are responsible to release memory of newVec, example use auto.
  */
vector<unsigned char*> d3tree::copyVecFast(const vector<unsigned char*>& original)
{
  std::vector<unsigned char*> newVec;
  newVec.reserve(original.size());
  copy(original.begin(), original.end(), back_inserter(newVec));
  return newVec;
}



