//
// Created by micha on 9.12.2025.
//

#ifndef TEPSEM3_ERROR_H
#define TEPSEM3_ERROR_H

#include <string>

class Error {
public:
    explicit Error(std::string message);
    const std::string* what() const;
private:
    std::string message;
};

#endif  // TEPSEM3_ERROR_H
