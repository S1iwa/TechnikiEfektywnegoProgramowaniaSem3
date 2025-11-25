//
// Created by micha on 23.11.2025.
//

#include "Interface.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

Interface::Interface() {
  command_map["exit"] = &Interface::command_exit;
  command_map["help"] = &Interface::command_help;
  command_map["enter"] = &Interface::command_enter;
  command_map["vars"] = &Interface::command_vars;
  command_map["print"] = &Interface::command_print;
  command_map["comp"] = &Interface::command_comp;
  command_map["join"] = &Interface::command_join;
}

void Interface::run() {
  std::string line;
  while (true) {
    std::cout << "Type command > ";
    std::getline(std::cin, line);

    std::vector<std::string> args;
    while (!line.empty()) {
      size_t pos = line.find(' ');
      if (pos == std::string::npos) {
        args.push_back(line);
        break;
      } else {
        args.push_back(line.substr(0, pos));
        line = line.substr(pos + 1);
      }
    }
    if (args.empty()) continue;

    std::string command = args[0];
    args.erase(args.begin());

    std::map<std::string, CommandFunction>::iterator it = command_map.find(command);
    if (it != command_map.end()) {
      CommandFunction func = it->second;
      (this->*func)(args);
    } else {
      std::cout << "Unknown command: " << command << std::endl;
    }
  }
}

void Interface::command_exit(std::vector<std::string>& args) {
  std::cout << "Exiting program." << std::endl;
  exit(0);
}

void Interface::command_enter(std::vector<std::string>& args) {
  if (args.empty()) {
    std::cout << "No expression provided." << std::endl;
    return;
  }

  tree = Tree();
  if(tree.build(args))
    std::cout << "Expression built successfully." << std::endl;
  else {
    std::cout << "Expression had to be modified to be valid." << std::endl;
    tree.print();
  }
}

void Interface::command_help(std::vector<std::string>& args) {
  std::cout << "Available commands:" << std::endl;
  std::cout << "  help - Show this help message" << std::endl;
  std::cout << "  enter <expression> - Enter a new expression" << std::endl;
  std::cout << "  vars - Show variables in the expression" << std::endl;
  std::cout << "  print - Print the current expression" << std::endl;
  std::cout << "  comp - Compute the value of the expression" << std::endl;
  std::cout << "  join <expression> - Join with another expression" << std::endl;
  std::cout << "  exit - Exit the program" << std::endl;
}

void Interface::command_vars(std::vector<std::string>& args) {
  std::cout << "Variables in the expression: ";
  std::vector<std::string>* vars = tree.getNodesWithVariables();
  for (int i = 0; i < vars->size(); ++i)
    std::cout << vars->at(i) << " ";
  std::cout << std::endl;
  delete vars;
}

void Interface::command_print(std::vector<std::string>& args) {
  tree.print();
}

void Interface::command_comp(std::vector<std::string>& args) {
  std::vector<std::string>* vars = tree.getNodesWithVariables();
  if (args.size() < vars->size())
    std::cout << "Not enough arguments provided to compute the expression." << std::endl;
  else if (args.size() > vars->size())
    std::cout << "More arguments provided than needed. Extra arguments will be ignored." << std::endl;

  std::map<std::string, double> values;
  for (int i = 0; i < vars->size(); ++i)
    if (i < args.size())
      values[vars->at(i)] = toDouble(args[i]);
    else
      values[vars->at(i)] = 1.0;

  delete vars;
  std::cout << "Result: " << tree.evaluate(values) << std::endl;
}

void Interface::command_join(std::vector<std::string>& args) {
  if (args.empty()) {
    std::cout << "No expression provided to join." << std::endl;
    return;
  }

  Tree other_tree;
  other_tree.build(args);
  tree = tree + other_tree;
  std::cout << "Expressions joined." << std::endl;
}

double Interface::toDouble(const std::string& str) {
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