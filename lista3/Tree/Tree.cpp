//
// Created by micha on 23.11.2025.
//

#include "Tree.h"
#include "Node.h"

#include <iostream>

void Tree::build(std::vector<std::string>& args) const {
  std::cout << "Building tree with args:";
  for (int i = 0; i < args.size(); ++i)
    std::cout << " " << args[i];
  std::cout << std::endl;
  root->build(args);
}

void Tree::print() const {
  root->print();
  std::cout << std::endl;
}

Tree::~Tree() {
  delete root;
}

Tree::Tree() {
  root = new Node();
}

double Tree::evaluate(std::vector<std::string>& args) const {
  double result = 0;
  root->evaluate(&result, args);
  return result;
}

  std::vector<std::string>* Tree::getNodesWithVariables() const {
  std::vector<std::string> *vars = new std::vector<std::string>();
  root->getVariables(vars);
  return vars;
}

void Tree::join(const Tree& other) const {
  if (this->root == NULL || other.root == NULL) {
    std::cout << "Cannot join trees: one of the roots is null." << std::endl;
    return;
  }

  Node* leaf = this->root;
  while (!leaf->getChildren().empty())
    leaf = leaf->getChildren().back();

  *leaf = *other.root;
}

bool Tree::operator==(const Tree& other) const {
  return (*this->root == *other.root);
}

Tree Tree::operator+(const Tree& other) {
  Tree result = *this;
  result.join(other);
  return result;
}

Tree& Tree::operator=(const Tree& other) {
  if (this != &other) {
    delete this->root;
    this->root = new Node();
    *this->root = *other.root;
  }
  return *this;
}

Tree::Tree(const Tree& other) {
  root = new Node();
  *root = *other.root;
}
