//
// Created by micha on 23.11.2025.
//

#include "Node.h"
#include "../Interface.h"

#include <cmath>
#include <algorithm>
#include <iostream>

Node::Node() {}

Node::~Node() {
  for (int i = 0; i < children.size(); ++i)
    delete children[i];
  children.clear();
}

bool Node::operator==(const Node& other) const {
  if (this->value != other.value)
    return false;

  if (this->children.size() != other.children.size())
    return false;

  for (size_t i = 0; i < this->children.size(); ++i)
    if (!(*this->children[i] == *other.children[i]))
      return false;

  return true;
}

Node& Node::operator=(const Node& other) {
  if (this != &other) {
    this->value = other.value;

    for (int i = 0; i < this->children.size(); ++i)
      delete this->children[i];
    this->children.clear();

    for (int i = 0; i < other.children.size(); ++i) {
      Node* newChild = new Node();
      *newChild = *other.children[i];
      this->children.push_back(newChild);
    }
  }
  return *this;
}

Node::Node(const Node& other) {
  *this = other;
}

bool Node::build(std::vector<std::string>& args) {
  bool flag = true;
  if (!args.empty()) {
    setValue(args[0]);
    args.erase(args.begin());
  } else {
    flag = false;
    //std::cout << "No more arguments available, setting default value 1.0" << std::endl;
    setValue("1");
  }

  int required_args = getRequiredArguments();
    for (int i = 0; i < required_args; ++i) {
      Node* child = new Node();
      if(!child->build(args))
        flag = false;
      children.push_back(child);
    }
  return flag;
}

void Node::print() const {
  std::cout << value << " ";
  for (int i = 0; i < children.size(); ++i)
    children[i]->print();
}

double Node::evaluate(std::map<std::string, double>& values) const {
  if (isVariable()) {
    if (values.find(value) != values.end())
      return values[value];
    //std::cout << "No more arguments available for variable, using default value 1.0" << std::endl;
    return 1.0;
  }

  if (getRequiredArguments() == 0)
    return Interface::toDouble(value);

  std::vector<double> child_results;
  child_results.reserve(children.size());
  for (int i = 0; i < children.size(); ++i)
    child_results.push_back(children[i]->evaluate(values));

  if (value == "+")
    return child_results[0] + child_results[1];
  if (value == "-")
    return child_results[0] - child_results[1];
  if (value == "*")
    return child_results[0] * child_results[1];
  if (value == "/") {
    if (child_results[1] == 0) {
      std::cout << "Division by zero encountered. Dividing variable by 1.0" << std::endl;
      return child_results[0];
    }
    return child_results[0] / child_results[1];
  }
  if (value == "sin") return sin(child_results[0]);
  if (value == "cos") return cos(child_results[0]);
  return 0.0;
}

// nie moze byc const bo ja modyfikuje te zmienneeeeee
void Node::getVariables(std::vector<std::string>* vars) {
  if (isVariable())
    if (std::find(vars->begin(), vars->end(), value) == vars->end())
      vars->push_back(value);
  for (int i = 0; i < children.size(); ++i)
    children[i]->getVariables(vars);
}

bool Node::isVariable() const {
  if (value.empty() || getRequiredArguments() != 0)
    return false;

  if (value == "sin" || value == "cos")
    return false;

  for (size_t i = 0; i < value.size(); ++i) {
    char c = value[i];
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
      return true;
  }

  return false;
}

void Node::setValue(const std::string& val) {
  value = val;
}

std::string Node::getValue() const {
  return value;
}

std::vector<Node*> Node::getChildren() const {
  return children;
}

int Node::getRequiredArguments() const {
  if (value == "+" || value == "-" || value == "*" || value == "/")
    return 2;
  if (value == "sin" || value == "cos")
    return 1;
  return 0;
}
