//
// Created by micha on 23.11.2025.
//

#include "Node.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <math.h>

Node::Node() {}

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
  } else {
    std::cout << "No more arguments available, setting default value '1'" << std::endl;
    setValue("1");
  }

  int required_args = getRequiredArguments();
    for (int i = 0; i < required_args; ++i) {
      Node* child = new Node();
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

void Node::evaluate(double *result, std::vector<std::string>& args) const {
  if (isVariable()) {
    if (!args.empty()) {
      *result += args.begin()->empty() ? 1.0 : toDouble(args[0]);
      args.erase(args.begin());
    } else {
      std::cout << "No more arguments available for variable, using default value 1.0" << std::endl;
      *result += 1.0;
    }
  } else {
  std::vector<double> child_results;
  for (int i = 0; i < children.size(); ++i) {
    double child_result = 0.0;
    children[i]->evaluate(&child_result, args);
    child_results.push_back(child_result);
  }

  if (value == "+")
    *result += child_results[0] + child_results[1];
  else if (value == "-")
    *result += child_results[0] - child_results[1];
  else if (value == "*")
    *result += child_results[0] * child_results[1];
  else if (value == "/")
    *result += child_results[0] / child_results[1];
  else if (value == "sin") {
    std::cout << "Calculating sin of " << child_results[0] << std::endl;
    *result += sin(child_results[0]);
  } else if (value == "cos")
    *result += cos(child_results[0]);
  else
    *result += toDouble(value);
  }
}

void Node::getVariables(std::vector<std::string>* vars) {
  if (isVariable())
    if (std::find(vars->begin(), vars->end(), value) == vars->end())
      vars->push_back(value);
  for (int i = 0; i < children.size(); ++i)
    children[i]->getVariables(vars);
}

bool Node::isVariable() const {
  return (getRequiredArguments() == 0
            && !(value == "sin" || value == "cos")
            && !(value[0] >= '0' && value[0] <= '9'));
}

bool Node::operator==(const Node& other) const {
  return this->value == other.value;
}

double Node::toDouble(const std::string& str) {
  try {
    for (int i = 0; i < str.size(); ++i)
      if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
        throw std::invalid_argument("Not a number");
  } catch (std::invalid_argument& e) {
    std::cout << "Error converting string to double: " << e.what() << std::endl;
    return 0.0;
  }

  std::stringstream ss(str);
  double result;
  if (ss >> result)
    return result;
  else {
    std::cout << "Error converting string to double." << std::endl;
    return 0.0;
  }
}