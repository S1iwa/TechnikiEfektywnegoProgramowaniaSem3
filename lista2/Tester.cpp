//
// Created by micha on 10/26/2025.
//

#include "Tester.h"
#include "Number.h"

#include <iostream>
#include <ostream>

int main() {
  Number number(900);
  Number number2(300);
  Number number3(3000);
  number3 = number + number2;

  std::cout << (number3 + number2) << std::endl;
}
