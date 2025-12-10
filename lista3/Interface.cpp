//
// Created by micha on 23.11.2025.
//

#include "Interface.h"

#include <iostream>
#include <map>
#include <sstream>
#include <string>

Interface::Interface() {
  commandMap["exit"] = &Interface::command_exit;
  commandMap["help"] = &Interface::command_help;
  commandMap["enter"] = &Interface::command_enter;
  commandMap["vars"] = &Interface::command_vars;
  commandMap["print"] = &Interface::command_print;
  commandMap["comp"] = &Interface::command_comp;
  commandMap["join"] = &Interface::command_join;
}

void Interface::run() {
  std::string line;
  while (true) {
    std::cout << "Type command > ";
    std::getline(std::cin, line);

    std::vector<std::string> args;
    std::stringstream ss(line);

    std::string segment;
    while (ss >> segment)
      args.push_back(segment);

    if (args.empty()) continue;

    std::string command = args[0];
    args.erase(args.begin());

    std::map<std::string, CommandFunction>::iterator it = commandMap.find(command);
    if (it != commandMap.end())
      (this->*(it->second))(args);
    else
      std::cout << "Unknown command: " << command << std::endl;
  }
}

// Pewnie to ja jestem debilem a nie kompilator ale nwm
// One nie mogą być const
// Kiedy dam wszedzie const to i tak sa dalej bledy ktore nie da sie naprawic
// peak programming skills

void Interface::command_exit(std::vector<std::string>&) {
  std::cout << "Exiting program." << std::endl;
  exit(0);
}

void Interface::command_enter(std::vector<std::string>& args) {
  if (args.empty()) {
    std::cout << "No expression provided." << std::endl;
    return;
  }

  tree = Tree();

  for (int i = 0; i < args.size(); ++i)
    if (!isArgValid(args[i])) {
      std::cout << "Skipping argument: " << args[i] << std::endl;
      args.erase(args.begin() + i--);
    }

  if(tree.build(args) && args.empty())
    std::cout << "Expression built successfully." << std::endl;
  else {
    std::cout << "Expression had to be modified to be valid." << std::endl;
    tree.print();
  }
}

void Interface::command_help(std::vector<std::string>&) {
  std::cout << "Available commands:" << std::endl;
  std::cout << "  help - Show this help message" << std::endl;
  std::cout << "  enter <args> - Enter a new expression" << std::endl;
  std::cout << "  vars - Show variables in the expression" << std::endl;
  std::cout << "  print - Print the current expression" << std::endl;
  std::cout << "  comp <args> - Compute the value of the expression" << std::endl;
  std::cout << "  join <args> - Join with another expression" << std::endl;
  std::cout << "  exit - Exit the program" << std::endl;
}

void Interface::command_vars(std::vector<std::string>&) {
  std::cout << "Variables in the expression: ";
  std::vector<std::string>* vars = tree.getNodesWithVariables();
  if (vars->empty()) {
    std::cout << "None" << std::endl;
    delete vars;
    return;
  }
  for (int i = 0; i < vars->size(); ++i)
    std::cout << vars->at(i) << " ";
  std::cout << std::endl;
  delete vars;
}

void Interface::command_print(std::vector<std::string>&) {
  if (tree.isEmpty())
    std::cout << "No expression provided." << std::endl;
  tree.print();
}

void Interface::command_comp(std::vector<std::string>& args) {
  if (tree.isEmpty()) {
    std::cout << "Cannot comp empty tree." << std::endl;
    return;
  }

  std::vector<std::string>* vars = tree.getNodesWithVariables();
  if (args.size() < vars->size())
    std::cout << "Not enough arguments provided to compute the expression." << std::endl;
  else if (args.size() > vars->size())
    std::cout << "More arguments provided than needed. Extra arguments will be ignored." << std::endl;
  // else if (args.size() > 0 && vars->size() == 0)
  //   std::cout << "No variables in the expression, arguments will be ignored." << std::endl;

  std::map<std::string, double> values;

  try {
    for (int i = 0; i < vars->size(); ++i)
      if (i < args.size())
        values[vars->at(i)] = toDouble(args[i]);
      else
        values[vars->at(i)] = 1.0;
  } catch (std::invalid_argument&) {
    std::cout << "Invalid argument provided for variable value." << std::endl;
    delete vars;
    return;
  }

  delete vars;
  std::cout << "Result: " << tree.evaluate(values) << std::endl;
}

void Interface::command_join(std::vector<std::string>& args) {
  if (args.empty()) {
    std::cout << "No expression provided to join." << std::endl;
    return;
  }

  Tree other_tree;

  for (int i = 0; i < args.size(); ++i)
    if (!isArgValid(args[i])) {
      std::cout << "Skipping argument: " << args[i] << std::endl;
      args.erase(args.begin() + i--);
    }

  if(other_tree.build(args) && args.empty())
    std::cout << "Expression built successfully." << std::endl;
  else {
    std::cout << "Expression had to be modified to be valid." << std::endl;
    other_tree.print();
  }

  tree = tree + other_tree;
  std::cout << "Expressions joined." << std::endl;
}

bool Interface::isArgValid(const std::string& arg) {
  if (arg == "+" || arg == "-" || arg == "*" || arg == "/" ||
        arg == "sin" || arg == "cos")
    return true;

  for (int i = 0; i < arg.size(); ++i) {
    char c = arg[i];
    if (!isalnum(c) && c != '.')
      return false;
  }

  return true;
}

double Interface::toDouble(const std::string& str) throw (std::invalid_argument) {
  if (str.empty() || (str.size() == 1 && (str[0] < '0' || str[0] > '9')))
    throw std::invalid_argument("Not a proper number");

  for (int i = 0; i < str.size(); ++i)
    if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
      throw std::invalid_argument("Not a number");

  std::stringstream ss(str);
  double result;
  if (ss >> result)
    return result;
  throw std::invalid_argument("Conversion to double failed");
}