//
// Created by micha on 14/01/2026.
//

#include <iostream>

#include "../lista3/Tree/Tree.h"
#include "../lista4/TreeAdapter.h"
#include "SmartPointer.h"

Tree createTree() {
  std::vector<std::string> args = {"+", "3", "*", "x", "2"};
  auto result = TreeAdapter::buildTree(args);
  return result.getValue();
}

int main() {
  std::cout << "--- Test 1: MySmartPointer ---" << std::endl;
  auto val = new int(10);
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
  std::cout << "Smart Pointer test finished.\n" << std::endl;


  

  // --- TEST 2: Move Semantics dla Tree ---
  std::cout << "--- Test 2: Tree Move Semantics ---" << std::endl;

  std::vector<std::string> args = {"+", "a", "b"};
  Result<Tree, Error> res = TreeAdapter::buildTree(args);
  Tree tree1 = res.getValue();

  std::cout << "1. Copying tree (Normal Copy):" << std::endl;
  Tree tree2 = tree1; // Uruchomi się zwykły konstruktor kopiujący (Deep Copy)

  std::cout << "\n2. Moving tree (std::move):" << std::endl;
  // Tu powinien zadziałać Twój nowy konstruktor przenoszący!
  // tree1 zostanie "ograbione" z danych, tree3 przejmie wskaźnik.
  Tree tree3 = std::move(tree1);

  std::cout << "\n3. Move Assignment:" << std::endl;
  Tree tree4;
  // Operator przypisania przenoszącego
  tree4 = std::move(tree2);

  std::cout << "\nChecking structure:" << std::endl;
  std::cout << "Tree3 (moved from Tree1): " << tree3.toString() << std::endl;
  std::cout << "Tree1 (after move): " << tree1.toString() << " (Should be empty)" << std::endl;

  return 0;
}