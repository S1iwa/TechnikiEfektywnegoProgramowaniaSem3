//
// Created by S1iwa on 10.12.2025.
//

#include "Tester.h"

#include <iostream>

#include "../lista3/Tree/Tree.h"
#include "FileSaver.h"
#include "TreeAdapter.h"

int main() {
  std::vector<std::string> args = {"a", "b", "c", "d", "e"};
  std::string filename = "tree0.txt";
  Tester::test(args, filename);

  args = {"+", "@", "*", "2", "sin", "b"};
  filename = "tree1.txt";
  Tester::test(args, filename);

  args = {"+", "a", "*", "2", "sin", "b"};
  filename = "tree2.txt";
  Tester::test(args, filename);

  args = {"+", "2"};
  filename = "tree3.txt";
  Tester::test(args, filename);

  args = {};
  filename = "tree4.txt";
  Tester::test(args, filename);

  Result<double, Error> result = Tester::safeDivide(10, 0);

  return 0;
}

void Tester::test(std::vector<std::string>& args, std::string& filename) {
  Result<Tree, Error> result = TreeAdapter::buildTree(args);
  std::cout << "Tree with args: ";
  for (const auto& arg : args)
    std::cout << arg << " ";
  std::cout << std::endl;
  if (result.isSuccess()) {
    std::cout << "Tree built successfully." << std::endl;
  } else {
    for (const auto& error : result.getErrors())
      std::cout << "Error: " << error->getMessage() << std::endl;
  }
  FileSaver<Tree>::saveToFile(result, filename);
  std::cout << std::endl;
}

Result<double, Error> Tester::safeDivide(double a, double b) {
  if (b == 0)
    return new Error("Division by zero");
  return a / b;
}