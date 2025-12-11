//
// Created by micha on 11.12.2025.
//

#ifndef TEPSEM3_FILESAVER_H
#define TEPSEM3_FILESAVER_H

#include <fstream>
#include <string>

#include "../lista3/Tree/Tree.h"
#include "Result.h"

template<typename T>
class FileSaver {
public:
  static void saveToFile(const Result<T, Error>& result, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open())
      throw std::runtime_error("Could not open file for writing: " + filename);

    if (!result.isSuccess()) {
      file << "Errors occurred:\n";
      const auto& errors = result.getErrors();
      for (const auto& error : errors)
        file << error->getMessage() << "\n";
    }

    file.close();
  }
};

template<>
class FileSaver<Tree> {
public:
  static void saveToFile(const Result<Tree, Error>& result, const std::string& filename) {
    std::ofstream file(filename.c_str());
    if (!file.is_open())
      throw std::runtime_error("Could not open file for writing: " + filename);

    if (result.isSuccess()) {
      file << result.getValue().toString() << "\n";
    } else {
      file << "Errors occurred:\n";
      const auto& errors = result.getErrors();
      for (const auto& error : errors)
        file << error->getMessage() << "\n";
    }
    file.close();
  }
};

#endif  // TEPSEM3_FILESAVER_H
