#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node::Node() { //Constructor
  data = 0;
  left = NULL;
  right = NULL;
}

Node::~Node() { //Destructor
  left = NULL;
  right = NULL;
}

//Getters
Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

int Node::getData() {
  return data;
}

//Setters
void Node::setLeft(Node* newLeft) {
  left = newLeft;
}

void Node::setRight(Node* newRight) {
  right = newRight;
}

void Node::setData(int newData) {
  data = newData;
}
