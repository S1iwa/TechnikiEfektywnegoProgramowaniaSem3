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
  void join(const Tree& other) const;
  bool operator==(const Tree& other) const;
  Tree& operator=(const Tree& other);
  Tree operator+(const Tree& other);
  double evaluate(std::vector<std::string>& args) const;
  std::vector<std::string>* getNodesWithVariables() const;
  Tree();
  ~Tree();
  Tree(const Tree& other);
  Node* root;
};

#endif  // TEPSEM3_TREE_H
