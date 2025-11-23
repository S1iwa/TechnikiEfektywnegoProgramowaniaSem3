//
// Created by micha on 23.11.2025.
//

#ifndef TEPSEM3_TREE_H
#define TEPSEM3_TREE_H

#include <string>
#include <vector>

#include "Node.h"

class Tree {
public:
  void build(std::vector<std::string>& args) const;
  void print() const;
  Tree();
  ~Tree();
  Node* root;
};

#endif  // TEPSEM3_TREE_H
