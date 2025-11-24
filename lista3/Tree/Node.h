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

  bool operator==(const Node& other) const;

 private:
  std::string value;
  std::vector<Node*> children;

  int getRequiredArguments() const;
  static double toDouble(const std::string& str) ;
};

#endif  // TEPSEM3_NODE_H
