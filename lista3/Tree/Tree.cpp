//
// Created by micha on 23.11.2025.
//

#include "Tree.h"
#include "Node.h"

#include <iostream>

Tree::Tree() {
  root = new Node();
}

Tree::~Tree() {
  delete root;
}

bool Tree::build(std::vector<std::string>& args) {
  return root->build(args);
}

void Tree::print() const {
  root->print();
  std::cout << std::endl;
}

void Tree::join(const Tree& other) {
  // To sie nigdy nie zdarzy w sumie
  // if (this->root == NULL || other.root == NULL) {
  //   std::cout << "Cannot join trees: one of the roots is null." << std::endl;
  //   return;
  // }

  Node* leaf = this->root;
  while (!leaf->getChildren().empty())
    leaf = leaf->getChildren().back();

  *leaf = *other.root;
}

bool Tree::operator==(const Tree& other) const {
  return (*this->root == *other.root);
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

double Tree::evaluate(std::map<std::string, double>& values) const {
  return root->evaluate(values);
}

std::vector<std::string>* Tree::getNodesWithVariables() const {
  std::vector<std::string> *vars = new std::vector<std::string>();
  root->getVariables(vars);
  return vars;
}

Tree Tree::operator+(const Tree& other) const {
  Tree result = *this;
  result.join(other);
  return result;
}
bool Tree::isEmpty() const {
  return root->getValue().empty();
}