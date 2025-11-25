//
// Created by micha on 23.11.2025.
//

#ifndef TEPSEM3_NODE_H
#define TEPSEM3_NODE_H

#include <string>
#include <vector>
#include <map>

class Node {
public:
  Node();
  ~Node();

  bool operator==(const Node& other) const;
  Node& operator=(const Node& other);
  Node(const Node& other);

  void setValue(const std::string& val);
  std::string getValue() const;

  bool build(std::vector<std::string>& args);
  void print() const;
  double evaluate(std::map<std::string, double>& values) const;

  void getVariables(std::vector<std::string>* vars);
  int getRequiredArguments() const;
  std::vector<Node*> getChildren() const;

 private:
  std::string value;
  std::vector<Node*> children;

  bool isVariable() const;
};

#endif  // TEPSEM3_NODE_H
