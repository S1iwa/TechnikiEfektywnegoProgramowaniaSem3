//
// Created by micha on 23.11.2025.
//

#ifndef TEPSEM3_NODE_H
#define TEPSEM3_NODE_H

#include <string>
#include <vector>

class Node {
public:
  Node();
  ~Node();

  void setValue(const std::string& val);
  std::string getValue() const;

  void build(std::vector<std::string>& args);
  void print() const;
  bool isVariable() const;
  void evaluate(double *result, std::vector<std::string>& args) const;

  void getVariables(std::vector<std::string>* vars);
  int getRequiredArguments() const;
  std::vector<Node*> getChildren() const;

  bool operator==(const Node& other) const;
  Node& operator=(const Node& other);
  Node(const Node& other);

 private:
  std::string value;
  std::vector<Node*> children;

  static double toDouble(const std::string& str) ;
};

#endif  // TEPSEM3_NODE_H
