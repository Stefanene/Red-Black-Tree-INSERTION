#ifndef NODE_H
#define NODE_H

using namespace std;

class Node {
 public:
  //constructor & deleter
  Node();
  ~Node();
  //setters
  void setData(int);
  void setRight(Node*);
  void setLeft(Node*);
  void setColor(int);
  //getters
  int getData();
  Node* getRight();
  Node* getLeft();
  int getColor();
 private:
  int data;
  Node* right;
  Node* left;
  int color;  //0 = black, 1 = red
};
#endif
