//
// Created by micha on 10/26/2025.
//

#include "Tester.h"
#include "Number.h"

#include <iostream>
#include <ostream>

int main() {
  Number n1(1);
  Number n2(2);
  Number n3(3);
  Number n4(4);
  Number n5(5);

  Number n100(100);
  Number n200(200);
  Number n300(300);
  Number n400(400);
  Number n500(500);

  std::cout << (n5 - n4) << std::endl;
  std::cout << (n1 - n3 - n5) << std::endl;
  std::cout << (n5 - n5 - n5 + n5) << std::endl;
  std::cout << (n500 - n5) << std::endl;
  std::cout << (n500 + n500) << std::endl;
  std::cout << (n500 - n500) << std::endl;
  std::cout << (n2 * n5) << std::endl;
  std::cout << (n500 * (-n1)) << std::endl;
}
