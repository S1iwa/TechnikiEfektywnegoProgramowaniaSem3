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
  root->build(args);
}

void Tree::print() const {
  root->print();
}

Tree::~Tree() {
  delete root;
}

Tree::Tree() {
  root = new Node();
}
