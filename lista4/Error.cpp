//
// Created by micha on 9.12.2025.
//

#include "Error.h"

Error::Error(std::string message) {
  this->message = message;
}

const std::string* Error::what() const {
  return &message;
}
