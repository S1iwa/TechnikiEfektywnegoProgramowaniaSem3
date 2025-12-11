//
// Created by micha on 10.12.2025.
//

#ifndef TEPSEM3_TESTER_H
#define TEPSEM3_TESTER_H

#include "Result.h"
#include "Error.h"

class Tester {
public:
  Result<double, Error> safeDivide(double a, double b);
  static void test(std::vector<std::string>& args, std::string& filename);
};

#endif  // TEPSEM3_TESTER_H
