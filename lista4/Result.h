//
// Created by micha on 10.12.2025.
//

#ifndef TEPSEM3_RESULT_H
#define TEPSEM3_RESULT_H

#include <stdexcept>
#include <vector>

#include "Error.h"

template<typename T, typename E>
class Result {
public:
  Result(const T& value) : value(new T(value)), errors() {};

  Result(E* error) : value(nullptr) {
    errors.push_back(error);
  };

  Result(std::vector<E*>& errors) : value(nullptr), errors(errors) {};

  Result(const Result<T, E>& other) {
    if (other.value)
      value = new T(*other.value);
    else
      value = nullptr;

    for (E* error : other.errors)
      errors.push_back(new E(*error));
  };

  ~Result() {;
    delete value;
    for (E* error : errors)
      delete error;
  };

  Result<T, E>& operator=(const Result<T, E>& other) {
    if (this != &other) {
      delete value;
      for (E* error : errors)
        delete error;
       errors.clear();

      if (other.value)
        value = new T(*other.value);
      else
        value = nullptr;

      for (E* error : other.errors)
        errors.push_back(new E(*error));
    }
    return *this;
  }

  static Result<T, E> ok(const T& value) {
    return Result<T, E>(value);
  }

  static Result<T, E> fail(E* error) {
    return Result<T, E>(error);
  }

  static Result<T, E> fail(std::vector<E*> errors) {
    return Result<T, E>(errors);
  }

  bool isSuccess() const {
    return value != nullptr;
  }

  T getValue() const {
    if (!value)
      throw std::runtime_error("No value present");
    return *value;
  }

  std::vector<E*>& getErrors() {
    return errors;
  }

  const std::vector<E*>& getErrors() const {
    return errors;
  }

private:
  T* value;
  std::vector<E*> errors;
};

template<typename E>
class Result<void, E> {
public:
  Result() = default;

  Result(E* error) {
    errors.push_back(error);
  };

  Result(std::vector<E*> errors) : errors(std::move(errors)) {};

  ~Result() {
    for (E* error : errors)
      delete error;
  };

  Result(const Result<void, E>& other) {
    for (E* error : other.errors)
      errors.push_back(new E(*error));
  };

  Result<void, E>& operator=(const Result<void, E>& other) {
    if (this != &other) {
      for (E* error : errors)
        delete error;
      errors.clear();
      for (E* error : other.errors)
        errors.push_back(new E(*error));
    }
    return *this;
  }

  static Result<void, E> ok() {
    return Result<void, E>();
  }

  static Result<void, E> fail(E* error) {
    return Result<void, E>(error);
  }

  static Result<void, E> fail(std::vector<E*> errors) {
    return Result<void, E>(errors);
  }

  bool isSuccess() const {
    return errors.empty();
  }

  std::vector<E*>& getErrors() {
    return errors;
  }

  const std::vector<E*>& getErrors() const {
    return errors;
  }
private:
  std::vector<E*> errors;
};

#endif  // TEPSEM3_RESULT_H
