//
// Created by micha on 23.11.2025.
//

#ifndef TEPSEM3_NODE_H
#define TEPSEM3_NODE_H

#include <string>
#include <vector>

class Node {
public:
  Node() : parent(NULL) {};
  ~Node();

  void setValue(const std::string& val);
  std::string getValue() const;

  void build(std::vector<std::string>& args);
  void print() const;

private:
  std::string value;
  std::vector<Node*> children;
  Node* parent;

  int getRequiredArguments() const;
};

#endif  // TEPSEM3_NODE_H
