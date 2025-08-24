//https://stackoverflow.com/questions/228684/how-to-declare-a-structure-in-a-header-that-is-to-be-used-by-multiple-files-in-c
//https://www.geeksforgeeks.org/cpp/cpp-binary-search-tree/

#ifndef COLORVALUETREE_H
#define COLORVALUETREE_H

#include <vector>

#include "ibstree.h"

class Node : public ITreeNode
{   public:
    Node* left;
    Node* right;

    std::vector<int>* keys;
};

class colorvaluetree : public abstree {
    private:
      const std::string WARN_H;

      Node* root;
      
    private:
      Node* createNode(int data, int key);
      void deleteTree(Node* n);
      int getMaxValue(Node* n); 
      void getNodeContents(Node* n, std::string* s);
      Node* insertNode(Node* root, int data, int key);
      void printTree(Node* n);
   
    public:
      colorvaluetree();
      ~colorvaluetree();

      void add(int data, int key);
      virtual void deleteTree(); 
      virtual int getMaxValue();
      std::string getContents();  
      virtual void printTree();
};

#endif
