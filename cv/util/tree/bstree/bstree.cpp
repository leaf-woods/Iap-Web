//https://www.geeksforgeeks.org/cpp/cpp-binary-search-tree/

#include <cassert>
#include <iostream>
#include "bstree.h"

using namespace std;

bstree::bstree() {
    //DEBUG_H = "Debug - ";
    count = 0;
    //https://stackoverflow.com/questions/35827086/best-way-to-check-if-pointer-is-initialized
    root = nullptr;
}

bstree::~bstree() {
    if (DEBUG) {
        cout << endl;
        cout << DEBUG_H << "Destructing root at: " << root << endl;
    }
    if (count > 0) {
        
        deleteTree(root);
    }
    if (DEBUG) {
        cout << DEBUG_H << "Root at: " << root << endl;
        assert(!root);
    }
}

/*
int bstree::size() {
    return count;
}
*/

ITreeNode* bstree::createNode(int data)
{
    ITreeNode* newNode = new ITreeNode();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    count++;
    if (DEBUG) {
        cout << DEBUG_H << "Created Node of: " << data << " at: " << newNode << endl;
    }
    return newNode;
}

ITreeNode* bstree::insertNode(ITreeNode* n, int data)
{
    if (count == 0) {
        root = createNode(data);
        if (DEBUG) {
            cout << DEBUG_H << "Root created of data: " << data << " at: " << root << endl;
        }
        return root;
    }

    if (n == nullptr) {
        n = createNode(data);
        return n;
    }

    if (data < n->data) {
        n->left = insertNode(n->left, data);
    }
    else if (data > n->data) { 
        n->right = insertNode(n->right, data);
    }
    else {
        cout << "Node already exists for data: " << data << endl;
    }

    // return the (unchanged) ITreeNode pointer
    return n;
}

void bstree::add(int data) {
    if (DEBUG) {
        cout << DEBUG_H << "Add Node: " << data << endl;
    }
    insertNode(root, data);
}

void bstree::printTree() {
    cout << "Print tree: size: " << count << endl;
    if (count == 0) {
        cout << "Empty tree." << endl;
        return;
    }

    if (root == nullptr) {
        cout << "Cannot print tree. Error occurred. Abort." << endl;
        return;
    }

    printTree(root);
    cout << "Print tree completed." << endl;
    cout << endl;
}

void bstree::printTree(ITreeNode* n) {
    if (n == nullptr) {
        return;
    }
    cout << "Node:" << n->data << endl;
    printTree(n->left);
    printTree(n->right);
}


int bstree::getMaxValue() {
    return abstree::getMaxValue(root);
}


/* 
 * If deleteTree(root) is called, root is deleted. 
 * Then calling add(int) will generate a new tree, i.e. a new root is created.
 */
void bstree::deleteTree(ITreeNode* n) {
    if (n == nullptr) {
        return;
    }

    if (DEBUG) {
        cout << DEBUG_H << "Delete left child of Node: " << n->data << endl;
    }
    deleteTree(n->left);
    
    if (DEBUG) {
        cout << DEBUG_H << "Delete right child of Node: " << n->data << endl;
    }
    deleteTree(n->right);

    if (DEBUG) {
        cout << DEBUG_H << "Delete Node: " << n->data << endl;
    }

    //cout << "deleting address: " << n << endl;
    
    /*
     * @20250814
     * Calling delete(root) means root and n are two variables. 
     * Inside function delete(ITreeNode*), stack variable n is a copy of instance variable root.
     *
     * Calling delete(root) passes a copy of *root (eg. 0x56046fda3a10 on Chromebook Debian 12) to
     * function delete(ITreeNode* n) 's parameter n. Which means inside function delete(ITreeNode*) 's stack, 
     * n == root where both n and root holds value  0x56046fda3a10.
     *
     * This means we need to ensure: 1) Memory holding by both root and n: 0x56046fda3a10 has to be freed (delete()).
     * Then both root and n will be reset to nullptr.
     */
    if (n == root) {
        //root->data = 0;
        //root->left = nullptr;
        //root->right = nullptr;
        
        //delete root;  // This causes: free(): double free detected in tcache 2
        root = nullptr;
    }
    n->data = 0;
    n->left = nullptr;
    n->right = nullptr;
    delete n; // free memory 0x56046fda3a10
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

void bstree::deleteTree() {
    if (count == 0) {
        cout << "Empty tree." << endl;
        assert(!root);
        return;
    }

    cout << "Deleting tree. Root: " << root << endl;    
    deleteTree(root);
    cout << "Tree deleted. Root: " << root << endl;
}