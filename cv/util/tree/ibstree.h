#ifndef IBSTREE_H
#define IBSTREE_H

#include "ITreeNode.h"
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
      const static int DEBUG = 0;
      const std::string DEBUG_H;

      int count;

      iap_print* printer;

    public:
      abstree() : DEBUG_H("Debug - ") {}
      virtual ~abstree(){};

      int size() { return count;}
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
};

#endif