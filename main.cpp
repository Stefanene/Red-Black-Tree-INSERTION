/*
  This is a Red-Black Tree Insertion algorithm by Stefan Ene
    Using most of the base code from my Binary Search Tree algorithm
    Colored output from https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
    Balancing Tree references from https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
*/

#include <iostream>
#include <cstring>
#include <fstream>
//colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"

#include "node.h"

using namespace std;

//struct Trunk for print method
struct Trunk {
  Trunk *prev;
  char* str;

  Trunk(Trunk *prev, char* str) {
    this -> prev = prev;
    this -> str = str;
  }
};

void showTrunks(Trunk *p) {//helper method for printing
  if (p == NULL)
    return;

  showTrunks(p -> prev);

  cout << p -> str;
}

//functions
void ADD(Node* &head, Node* &curr, Node*& prev, int val, int &height);
void READ(Node* &head, int &height);
void PRINT(Node* root, Trunk *prev, bool isLeft);
void parse(char* in, int* modif, int &count);
//functions for balancing/fixing tree
void balance(Node* &head, Node* &curr);
void rotateLeft(Node* &head, Node* &curr);
void rotateRight(Node* &head, Node* &curr);

//MAIN function
int main() {
  //variables
  char input[10]; //user input
  char read[10000];  //file input
  int modif[100]; //parsed input for insertion
  Node* head = NULL;
  int height = 0; //keep trach of tree height in terms of balck nodes
  //program
  cout << "=========================" << endl;
  cout << "Welcome to my Red-Black Tree INSERTION." << endl;
  bool run = true;
  while (run) {
    //cout << RED << "hello world" << RESET << endl;
    //cout << BLUE << "YO" << RESET << endl;
    cout << endl << "You can: add, read, print, and quit." << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(input, "add") == 0) {
      int val;
      cout << ">Add value: ";
      cin >> val;
      cin.clear();
      cin.ignore(10000, '\n');
      Node* curr = NULL;
      Node* prev = NULL;
      curr = head;
      ADD(head, curr, prev, val, height);
      balance(head, curr);
      cout << endl << val << " has been added:" << endl;
    }
    else if (strcmp(input, "read") == 0) {
      //make sure arrays are clear
      READ(head, height);
    }
    else if (strcmp(input, "print") == 0) {
      cout << "=========================" << endl;
      PRINT(head, NULL, false);
      cout << "=========================" << endl;
    }
    else if (strcmp(input, "quit") == 0) {
      cout << endl << "Thanks for using my program!" << endl;
      cout << "=========================" << endl;
      run = false;
    }
    else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  return 0;
}

//balance method to keep Red-Black properties of tree
//https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
void balance(Node* &head, Node* &curr) {
  Node* parent_pt = NULL;
  Node* grandparent_pt = NULL;
  
}

void rotateLeft(Node* &head, Node* &curr) {
  Node* rightPtr = curr->getRight(); 
  //begin rotation
  curr->setRight(rightPtr->getLeft()); 
  if (curr->getRight() != NULL) {
    (curr->getRight())->setParent(curr); 
  }
  rightPtr->setParent(curr->getParent());
  //if working with head
  if (curr->getParent() == NULL) {
    head = rightPtr; 
  } else if (curr == (curr->getParent())->getLeft()) {
    (curr->getParent())->setLeft(rightPtr); 
  } else {
    (curr->getParent())->setRight(rightPtr); 
  }  
  rightPtr->setLeft(curr); 
  curr->setParent(rightPtr);
}

void rotateRight(Node* &head, Node* & curr) {
  Node *leftPtr = curr->getLeft(); 
  //being rotation
  curr->setLeft(leftPtr->getRight()); 
  if (curr->getLeft() != NULL) {
    (curr->getLeft())->setParent(curr); 
  }  
  leftPtr->setParent(curr->getParent());
  //if working with head
  if (curr->getParent() == NULL) {
    head = leftPtr; 
  } else if (curr == (curr->getParent())->getLeft()) {
    (curr->getParent())->setLeft(leftPtr); 
  } else {
    (curr->getParent())->setRight(leftPtr);
  }
  leftPtr->setRight(curr); 
  curr->setParent(leftPtr);
}

//ADD method from my previous BTS project
void ADD(Node* &head, Node* &curr, Node*& prev, int val, int &height) {
  if (head == NULL) {
    head = new Node();
    head->setData(val);
    head->setColor(0);  //head is always black
    height = 1; //height of one black node
    return;
  } else {
    if (val < curr->getData()) {  //lower goes left
      prev = curr;
      curr = curr->getLeft();
      if (curr == NULL) {  //if empty then insert
	curr = new Node();
	curr->setData(val);
	prev->setLeft(curr);
	curr->setParent(prev);
	balance(head, curr);  //balance tree
	return;
      } else {  //if !empty then keep going
	ADD(head, curr, prev, val, height);
      }
    } else {
      prev = curr;
      curr = curr->getRight();  //higher goes right
      if (curr == NULL) {  //if empty then inset
	curr = new Node();
	curr->setData(val);
	prev->setRight(curr);
	curr->setParent(prev);
	balance(head, curr);  //balance tree
	return;
      } else {  //if !empty then keep going
	ADD(head, curr, prev, val, height);
      }
    }
  }
}

//READ function from file
void READ(Node* &head, int &height) {
  char in[10000];
  char fileName[100];
  int modif[100];
  int siz = 0;
  int count = 0;
  memset(in, 0, 10000);
  memset(fileName, 0, 100);
  memset(modif, 0, 100);
  //read in file name
  //Credit Omar Nassar's Heap project for file input code
  cout << endl << "What is the name of the file?" << endl << ">> ";
  cin.get(fileName, 30);
  cin.clear();
  cin.ignore(100000, '\n');
  streampos size;
  ifstream file(fileName, ios::in | ios::binary | ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    file.seekg(0, ios::beg);
    file.read(in, size);
    file.close();
    parse(in, modif, count);  //parse input to modif array
    cout << "IN: ";
    for (int i = 0; i < 100; i++) {
      if (modif[i] != 0) {
	cout << modif[i] << " ";
	siz++;
      }
    }
    cout << endl << "Size: " << siz << endl;;
    //add to tree
    Node* curr = NULL;
    Node* prev = NULL;
    for (int i = 0; i < siz; i++) {
      if(modif[i] == 0) break;
      curr = head;
      ADD(head, curr, prev, modif[i], height);
      balance(head, curr);
    }
  } 
}

//print functions from my previous BTS project
void PRINT(Node* root, Trunk *prev, bool isLeft) {
  if (root == NULL) {
    return;
  }
  char* prev_str = (char*)("    ");
  Trunk *trunk = new Trunk(prev, prev_str);
  PRINT(root->getLeft(), trunk, true);
  if (!prev) {
    trunk -> str = (char*)("---");
  }
  else if (isLeft) {
    trunk -> str = (char*)(".---");
    prev_str = (char*)("   |");
  }
  else {
    trunk -> str = (char*)("`---");
    prev -> str = prev_str;
  }
  showTrunks(trunk);
  if (root->getColor() == 0) {  //balck
    cout << BLUE << root->getData() << RESET << endl;
  } else {  //red
    cout << RED << root->getData() << RESET << endl;
  }
  if (prev) {
    prev -> str = prev_str;
  }
  trunk -> str = (char*)("   |");
  PRINT(root->getRight(), trunk, false);
}

//parse method from my previous BTS project
void parse(char* in, int* modif, int &count) {
  int l = 0;  //keeps track of # of chars before space
  for (int i = 0; i < strlen(in); i++) {
    if (in[i] == ' ') {
      if (l == 1) {
	int temp = 0;
	temp = in[i-1] - '0';
	modif[count] = temp;
	count++;
	l = 0;
      } else {
	int temp = 0;
	for (int a = 0; a < l; a++) {
	  temp = 10 * temp + (in[i-l+a] - '0');
	}
	modif[count] = temp;
	count++;
	l = 0;
      }
    } else {
      int temp = 0;
      l++;
      if (i == strlen(in) - 1) {  //last possible pair of chars
	for (int a = 0; a < l; a++) {
	  temp = 10 * temp + (in[i+a+1-l] - '0');
	}
	modif[count] = temp;
	count++;
      }
    }
  } 
}
