//
// Created by micha on 11.12.2025.
//

#include "TreeAdapter.h"
Result<Tree, Error> TreeAdapter::buildTree(std::vector<std::string> args) {
  std::vector<Error*> errors;

  if (args.empty()) {
    errors.push_back(new Error("No arguments provided to build the tree."));
    return Result<Tree, Error>::fail(errors);
  }

  for (int i = 0; i < args.size(); ++i)
    if (!isArgValid(args[i]))
      errors.push_back(new Error("Invalid argument at position " + std::to_string(i) + ": " + args[i]));
  if (!errors.empty())
    return Result<Tree, Error>::fail(errors);

  Tree tree;
  if (!tree.build(args))
    errors.push_back(new Error("Failed to build tree from the provided arguments."));

  if (!args.empty())
    errors.push_back(new Error("Not all arguments were used to build the tree."));
  if (!errors.empty())
    return Result<Tree, Error>::fail(errors);

  return Result<Tree, Error>::ok(tree);
}

bool TreeAdapter::isArgValid(const std::string& arg) {
  if (arg == "+" || arg == "-" || arg == "*" || arg == "/" ||
      arg == "sin" || arg == "cos") {
    return true;
  }

  // 2. Sprawdź liczby i zmienne (dozwolone: alfanumeryczne, kropka, minus)
  for (char c : arg)
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') || c == '.'))
      return false;
  return true;
}
