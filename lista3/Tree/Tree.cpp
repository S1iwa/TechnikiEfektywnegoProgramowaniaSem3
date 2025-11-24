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
  double *result = new double();
  root->evaluate(result, args);
  double res = *result;
  delete result;
  return res;
}

  std::vector<std::string>* Tree::getNodesWithVariables() const {
  std::vector<std::string> *vars = new std::vector<std::string>();
  root->getVariables(vars);
  return vars;
}
