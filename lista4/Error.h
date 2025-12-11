//
// Created by micha on 9.12.2025.
//

#ifndef TEPSEM3_ERROR_H
#define TEPSEM3_ERROR_H

#include <string>

class Error {
public:
    explicit Error(std::string message) : message(std::move(message)) {};
    virtual ~Error() = default;
    std::string getMessage() const { return message; }
private:
    std::string message;
};

#endif  // TEPSEM3_ERROR_H
