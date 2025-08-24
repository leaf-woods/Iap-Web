#ifndef HSVTREE_H
#define HSVTREE_H

#include <vector>

#include <opencv2/core.hpp>

#include "ibstree.h"

class HNode : public ITreeNode{   
  public: 
      HNode* left;
      HNode* right;

      std::vector<uchar*>* vecHsv;
};

class hsvtree : public abstree{
    private:
      //const std::string WARN_H;

      HNode* root;

    private:
      HNode* createNode(uchar* hsv);
      void deleteTree(HNode* n);
      HNode* insertNode(HNode* root, uchar* hsv);
      void printTree(HNode* n);

    public:
      hsvtree();
      ~hsvtree();

      void add(uchar* hsv);
      virtual void deleteTree(); 
      virtual int getMaxValue();  
      virtual void printTree();

};
#endif
