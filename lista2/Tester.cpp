//
// Created by S1iwa on 10/26/2025.
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

  Number n1000000(1000000);
  Number n2000000(2000000);
  Number n3000000(3000000);
  Number n4000000(4000000);
  Number n5000000(5000000);

  std::cout << (n5 - n4) << std::endl;
  std::cout << (n1 - n3 - n5) << std::endl;
  std::cout << (n5 - n5 - n5 + n5) << std::endl;
  std::cout << (n500 - n5) << std::endl;
  std::cout << (n500 + n500) << std::endl;
  std::cout << (n500 - n500) << std::endl;
  std::cout << (n2 * n5) << std::endl;
  std::cout << (n500 * (-n1)) << std::endl;
  std::cout << (-n500) << std::endl;
  std::cout << (-n500 * -n3) << std::endl;
  std::cout << (n5000000 * n5000000 * n5000000 * n5000000 * n5000000) << std::endl;
  std::cout << (n5000000 / n5) << std::endl;
  std::cout << (n5000000 / n3) << std::endl;
  std::cout << (n5000000 / n1) << std::endl;

  std::cout << (n3 / n3) << std::endl;
  std::cout << (n3 / n3 * n2) << std::endl;
  std::cout << (n100 - n3 / n3 * n2) << std::endl;
  std::cout << (n100 - 2) << std::endl;

  std::cout << (n100 > n200) << std::endl;
  std::cout << (n100 < n200) << std::endl;
  std::cout << (n100 <= n200) << std::endl;
  std::cout << (n100 >= n200) << std::endl;
  std::cout << (n200 >= n200) << std::endl;
  std::cout << (n100 >= n100) << std::endl;

  std::cout << (--n100) << std::endl;
  std::cout << (n100++) << std::endl;
  std::cout << (n100++) << std::endl;
  std::cout << (n100--) << std::endl;
  std::cout << (n100--) << std::endl;
  std::cout << (--n100) << std::endl;

  try {
    std::cout << (n100 / (Number(5) - 5)) << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
  }
}
