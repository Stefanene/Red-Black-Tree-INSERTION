/*
  This is a Red-Black Tree Insertion algorithm by Stefan Ene
    Using most of the base code from my Binary Search Tree algorithm
    Colored output from https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
*/

#include <iostream>
#include <cstring>
#include <fstream>
//colors
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
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
void ADD(Node* &head, Node* &curr, Node*& prev, int val);
void READ(Node* &head);
void PRINT(Node* root, Trunk *prev, bool isLeft);
void parse(char* in, int* modif, int &count);
void balance(Node* &head);  //function for balancing tree

//MAIN function
int main() {
  //variables
  char input[10]; //user input
  char read[10000];  //file input
  int modif[100]; //parsed input for insertion
  Node* head = NULL;
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
      ADD(head, curr, prev, val);
      balance(head);
      cout << endl << val << " has been added:" << endl;
    }
    else if (strcmp(input, "read") == 0) {
      //make sure arrays are clear
      READ(head);
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

//balance method to keep Red-Black functions of tree
void balance(Node* &head) {
  
}

//ADD method from my previous BTS project
void ADD(Node* &head, Node* &curr, Node*& prev, int val) {
  if (head == NULL) {
    head = new Node();
    head->setData(val);
    head->setColor(0);  //head is always black
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
	return;
      } else {  //if !empty then keep going
	ADD(head, curr, prev, val);
      }
    } else {
      prev = curr;
      curr = curr->getRight();  //higher goes right
      if (curr == NULL) {  //if empty then inset
	curr = new Node();
	curr->setData(val);
	prev->setRight(curr);
	curr->setParent(prev);
	return;
      } else {  //if !empty then keep going
	ADD(head, curr, prev, val);
      }
    }
  }
}

//READ function from file
void READ(Node* &head) {
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
