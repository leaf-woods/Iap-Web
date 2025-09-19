#ifndef IBSTREE_H
#define IBSTREE_H

#include <iostream>
#include <vector>

#include "ITreeNode.h"
#include "iapcv_log.h"
#include "iap_print.h"

class ibstree {
    public:
      virtual void deleteTree()=0; 
      virtual int getMaxValue()=0;
      virtual int size()=0;
      virtual void printTree()=0;
};

// Every child class type of abstree has its own root.
class abstree : public ibstree {
    protected:
      int count;
      int level;
      iapcv_log* logger;
      iap_print* printer;
      
    public:
      abstree(){};
      virtual ~abstree(){};

      int size() { return count;}
      
      void setLogLevel(int level) { logger->setLevel(level); }

      void setPrint(iap_print* p) { printer = p;}

    protected:
      template<typename N>
      int getMaxValue(N* n) {
          if (n == nullptr) {
            return 0;
          } 
          if (n->right == nullptr) {
            return n->data;
          }
          int count = 0;
          int value = n->data;
          // Find right most leaf on the tree
          while (n->right != nullptr) {
            value = n->right->data; 
            n = n->right;
            count++;
          }
          return value;
      }

      template<typename N>
      N* findNode(N* n, int data) {
          if (n == nullptr) {
            return nullptr;
          } 
          if (n->data == data) {
            return n;
          }
          if (data < n->data) {
            return findNode(n->left, data);
          }
          return findNode(n->right, data);
      }

      template<typename N>
      void traverseData(N* n, std::vector<int>* vh) {
          if (n == nullptr) {
              return;
          }
          logger->debug("Node data:", n->data);
          if (logger->isDebug()) {
              printer->printVector(*n->vecHsv);
          }
          traverseData(n->left, vh);
          vh->push_back(n->data);
          traverseData(n->right, vh);
      }
};
#endif