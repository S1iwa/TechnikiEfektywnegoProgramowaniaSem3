//
// Created by micha on 23.11.2025.
//

#ifndef TEPSEM3_INTERFACE_H
#define TEPSEM3_INTERFACE_H

#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "Tree/Tree.h"

class Interface {
public:
  Interface();
  void run();
  Tree tree;

  static double toDouble(const std::string& str) throw (std::invalid_argument);
private:
  typedef void (Interface::*CommandFunction)(std::vector<std::string>&);
  std::map<std::string, CommandFunction> commandMap;

  void command_exit(std::vector<std::string>& args);
  void command_help(std::vector<std::string>& args);
  void command_enter(std::vector<std::string>& args);
  void command_vars(std::vector<std::string>& args);
  void command_print(std::vector<std::string>& args);
  void command_comp(std::vector<std::string>& args);
  void command_join(std::vector<std::string>& args);

  static bool isArgValid(const std::string& arg);
};

#endif  // TEPSEM3_INTERFACE_H
