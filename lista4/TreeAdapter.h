//
// Created by micha on 11.12.2025.
//

#ifndef TEPSEM3_TREEADAPTER_H
#define TEPSEM3_TREEADAPTER_H

#include "../Lista3/Tree/Tree.h"
#include "Result.h"
#include "Error.h"

class TreeAdapter {
public:
  static Result<Tree, Error> buildTree(std::vector<std::string> args);

private:
  static bool isArgValid(const std::string& arg);
};

#endif  // TEPSEM3_TREEADAPTER_H
