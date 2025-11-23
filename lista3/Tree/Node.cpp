//
// Created by micha on 23.11.2025.
//

#include "Node.h"

#include <iostream>

Node::~Node() {
  for (int i = 0; i < children.size(); ++i)
    delete children[i];
  children.clear();
}

int Node::getRequiredArguments() const {
  if (value == "+" || value == "-" || value == "*" || value == "/")
    return 2;
  else if (value == "sin" || value == "cos")
    return 1;
  return 0;
}

void Node::build(std::vector<std::string>& args) {
  if (!args.empty()) {
    setValue(args[0]);
    args.erase(args.begin());
  } else
    setValue("1");

  int required_args = getRequiredArguments();
    for (int i = 0; i < required_args; ++i) {
      Node* child = new Node();
      child->parent = this;
      child->build(args);
      children.push_back(child);
    }
}

void Node::setValue(const std::string& val) {
  value = val;
}

std::string Node::getValue() const {
  return std::string();
}

void Node::print() const {
  std::cout << value << " ";
  for (int i = 0; i < children.size(); ++i)
    children[i]->print();
}
