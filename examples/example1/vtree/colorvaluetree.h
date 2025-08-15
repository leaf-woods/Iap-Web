//https://stackoverflow.com/questions/228684/how-to-declare-a-structure-in-a-header-that-is-to-be-used-by-multiple-files-in-c
//https://www.geeksforgeeks.org/cpp/cpp-binary-search-tree/

#ifndef COLORVALUETREE_H
#define COLORVALUETREE_H

#include <vector>

struct Node
{
    int data;
    Node* left;
    Node* right;

    std::vector<int>* keys;
};
// C++ standard then implicitly adds the following line
typedef Node Node;

class colorvaluetree {
    private:
      const std::string DEBUG_H;
      const std::string WARN_H;

      int count;
      Node* root;
      std::vector<int>* keys;

    public:
      const static int DEBUG = 0;
      
    private:
      Node* createNode(int data, int key);
      void deleteTree(Node* n);
      void getNodeContents(Node* n, std::string* s);
      Node* insertNode(Node* root, int data, int key);
      void printTree(Node* n);
      void printVector(std::vector<int>* v);
   
    public:
      colorvaluetree();
      ~colorvaluetree();

      void add(int data, int key);
      void deleteTree(); 
      int getMaxValue();
      std::string getContents();  
      int size();
      void printTree();
};

#endif

#endif
