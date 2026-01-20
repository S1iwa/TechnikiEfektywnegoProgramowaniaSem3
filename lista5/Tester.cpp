//
// Created by micha on 14/01/2026.
//

#include <iostream>

#include "../lista3/Tree/Tree.h"
#include "../lista4/TreeAdapter.h"
#include "SmartPointer.h"
#include "SmartPointerFixed.h"

Tree createTree() {
  std::vector<std::string> args = {"+", "3", "*", "x", "2"};
  auto result = TreeAdapter::buildTree(args);
  return result.getValue();
}

int main() {
  int* val = new int(10);
  {
    SmartPointer<int> sp1(val);
    std::cout << "SP1 value: " << *sp1 << std::endl;
    {
      SmartPointer<int> sp2 = sp1;
      std::cout << "SP2 value: " << *sp2 << std::endl;
      *sp2 = 20;
    }
    std::cout << "SP1 value after SP2 scope: " << *sp1 << std::endl;
  }
  std::cout << "\n\n";



  Tree tree1 = createTree();

  std::cout << "1. Copying tree:" << std::endl;
  Tree tree2 = tree1;

  std::cout << "\n2. Moving tree (std::move):" << std::endl;
  Tree tree3 = std::move(tree1);

  std::cout << "\n3. Move Assignment:" << std::endl;
  Tree tree4;
  tree4 = std::move(tree2);

  std::cout << "\nTree3 (moved from Tree1): " << tree3.toString() << std::endl;
  std::cout << "Tree1 (after move): " << tree1.toString() << " (Should be empty)" << std::endl;



  std::cout << "\n\n";

  BorrowingPointer<int>* externalBorrower = nullptr;
  {
    SmartPointer<int> sp(new int(123));
    std::cout << "Sp value: " << *sp << std::endl;

    BorrowingPointer<int> borrower = sp.getBorrowingPointer();
    std::cout << "2. Borrower created. Value: " << *borrower << std::endl;

    *borrower = 999;
    std::cout << "3. Modified via borrower. Sp value: " << *sp << std::endl;

    externalBorrower = new BorrowingPointer<int>(borrower);
    std::cout << "4. Exiting owner scope..." << std::endl;
  }
  // Sp tutaj znika:
  // notifyObjectDeleted() -> externalBorrower->reset()
  // czyli usuwa pamiec inta


  std::cout << "Is bp null:" << externalBorrower->isValid() << std::endl;

  try {
    std::cout << "Value: " << **externalBorrower << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  delete externalBorrower;

  return 0;
}