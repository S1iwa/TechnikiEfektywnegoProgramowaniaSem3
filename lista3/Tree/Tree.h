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
  Tree();
  ~Tree();

  bool operator==(const Tree& other) const;
  Tree& operator=(const Tree& other);
  Tree(const Tree& other);

  // Zwraca false, jeżeli musiano modyfikować, aby było poprawne
  bool build(std::vector<std::string>& args);
  void print() const;
  void join(const Tree& other);
  double evaluate(std::map<std::string, double>& values) const;

  std::vector<std::string>* getNodesWithVariables() const;

  Tree operator+(const Tree& other) const;
  bool isEmpty() const;
private:
  Node* root;
};

#endif  // TEPSEM3_TREE_H
