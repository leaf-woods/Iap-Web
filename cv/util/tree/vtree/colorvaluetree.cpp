//https://www.geeksforgeeks.org/cpp/cpp-binary-search-tree/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include "colorvaluetree.h"

using namespace std;

colorvaluetree::colorvaluetree() : WARN_H("Warn - ") {
    count = 0;
    //https://stackoverflow.com/questions/35827086/best-way-to-check-if-pointer-is-initialized
    root = nullptr;
}

colorvaluetree::~colorvaluetree() {
    if (DEBUG) {
        cout << endl;
        cout << DEBUG_H << "Destructing colorvaluetree: root at: " << root << endl;
    }
    if (count > 0) {
        deleteTree(root);
    }
    if (DEBUG) {
        cout << DEBUG_H << "Root at: " << root << endl;
        assert(!root);
    }
    printer = nullptr;
}

Node* colorvaluetree::createNode(int data, int key)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    newNode->keys = new std::vector<int>();
    newNode->keys->push_back(key);

    count++;
    if (DEBUG) {
        cout << DEBUG_H << "Created node of: " << data << " at: " << newNode << endl;
    }
    return newNode;
}

Node* colorvaluetree::insertNode(Node* n, int data, int key)
{
    if (count == 0) {
        root = createNode(data, key);
        if (DEBUG) {
            cout << DEBUG_H << "Root created of data: " << data << " at: " << root << endl;
        }
        return root;
    }

    if (n == nullptr) {
        n = createNode(data, key);
        return n;
    }

    if (data < n->data) {
        n->left = insertNode(n->left, data, key);
    }
    else if (data > n->data) { 
        n->right = insertNode(n->right, data, key);
    }
    else {
        // Data exists. 
        n->keys->push_back(key);
    }

    // return the (unchanged) node pointer
    return n;
}

void colorvaluetree::add(int data, int key) {
    if (data <=0 ) {
        cout << "Can not add data. Invalid data entry: { " << data << ", " << key << " }" << endl;
        return;
    }
    insertNode(root, data, key);
}

void colorvaluetree::printTree() {
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

void colorvaluetree::getNodeContents(Node* n, string* s) {
    if (n == nullptr) {
        return;
    }
    s->append("N=");
    s->append(to_string(n->data));
    s->append(" V=[ ");
    for (int i=0; i<n->keys->size(); i++) {
        s->append(to_string(n->keys->at(i)));
        s->append(" ");
    }
    s->append("]\n");
    getNodeContents(n->left, s);
    getNodeContents(n->right, s);
}

std::string colorvaluetree::getContents() {
    string s = "t size=";
    s.append(to_string(count));
    s.append("\n");
    getNodeContents(root, &s);
    return s;
}

void colorvaluetree::printTree(Node* n) {
    if (n == nullptr) {
        return;
    }
    cout << "Node:" << n->data << " ";
    printer->printVector(n->keys);

    printTree(n->left);
    printTree(n->right);
}

int colorvaluetree::getMaxValue() {
    return abstree::getMaxValue(root);
}

void colorvaluetree::deleteTree(Node* n) {
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
        //root->data = 0;
        //root->left = nullptr;
        //root->right = nullptr;
        root = nullptr;
    }
    
    n->data = 0;
    if (n->keys != nullptr) {
        for (int i=0; i<n->keys->size(); i++) {
            n->keys->at(i) = 0;
        }
        *n->keys = vector<int>();
        delete n->keys;
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

void colorvaluetree::deleteTree() {
    if (count == 0) {
        cout << "Empty tree." << endl;
        assert(!root);
        return;
    }

    cout << "Deleting colorvaluetree." << endl;    
    deleteTree(root);
    cout << "Tree deleted. Root: " << root << endl;
}

