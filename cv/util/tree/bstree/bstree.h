//https://stackoverflow.com/questions/228684/how-to-declare-a-structure-in-a-header-that-is-to-be-used-by-multiple-files-in-c
//https://www.geeksforgeeks.org/cpp/cpp-binary-search-tree/

#ifndef BSTREE_H
#define BSTREE_H

#include <vector>

#include "ibstree.h"

class bstree : public abstree {
    
    private:
      ITreeNode* root;
       
    private:
      ITreeNode* createNode(int data);
      void deleteTree(ITreeNode* n);
      ITreeNode* insertNode(ITreeNode* n, int data);
      void printTree(ITreeNode* n);
   
    public:
      bstree();
      ~bstree();

      void add(int data);
      virtual void deleteTree(); 
      virtual int getMaxValue();
      virtual void printTree();
};

#endif