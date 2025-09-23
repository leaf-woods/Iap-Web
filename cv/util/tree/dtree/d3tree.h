#ifndef D3TREE_H
#define D3TREE_H

#include <vector>

#include "dimensions.h"
#include "ibstree.h"

class D3Node : public ITreeNode{   
  public: 
      D3Node* left;
      D3Node* right;

      std::vector<unsigned char*>* vec;
};

class d3tree : public abstree{
    private:
      D3Node* root;

      int dim = dimensions::D_X;
      DimType type = DimType::XYZ;

    public:
      /*
       * each unsigned char array length stored in vec.
       */
      const static int V_LEN = 3;

    private:
      vector<unsigned char*> copyVecFast(const vector<unsigned char*>& original);
      D3Node* createNode(unsigned char* v3);
      void deleteTree(D3Node* n);
      D3Node* insertNode(D3Node* root, unsigned char* v3);
      void printTree(D3Node* n);

    public:
      d3tree();
      ~d3tree();

      void add(size_t s, unsigned char* v3);
      virtual void deleteTree();
      std::vector<unsigned char*> findValues(int data);
      int getDim();
      DimType getDimensionType();
      virtual int getMaxValue();
      void getTreeData(std::vector<int>* vh);  
      virtual void printTree();
      void setDim(DimType type, int d);
};

#endif
