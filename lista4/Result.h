//
// Created by micha on 10.12.2025.
//

#ifndef TEPSEM3_RESULT_H
#define TEPSEM3_RESULT_H

#include <vector>
#include "Error.h"

template<typename T, typename E>
class Result {
public:
  Result(const T& value);
  Result(E* error);
  Result(std::vector<E*> errors);
  Result(const Result<T, E>& other);
  ~Result();

  static Result<T, E> Ok(const T& value);
  static Result<T, E> Fail(E* error);
  static Result<T, E> Fail(std::vector<E*> errors);

  Result<T, E>& operator=(const Result<T, E>& other);

  bool isOk() const;
  T getValue() const;
  std::vector<E*> getErrors() const;

  Result<double, Error> divide(double dividend, double divisor);

private:
  T* value;
  std::vector<E*> errors;
};

template <typename T, typename E>
Result<T, E>::Result(const T& value) {

}

template <typename T, typename E>
Result<T, E>::Result(E* error) {

}

template <typename T, typename E>
Result<T, E>::Result(std::vector<E*> errors) {

}

template <typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other) {
  if (other.isOk())
    value = new T(*other.value);
  else
    for (E* error : other.errors)
      errors.push_back(new E(*error));
}

template <typename T, typename E>
Result<T, E>::~Result() {
  delete value;
  for (E* error : errors)
    delete error;
}

template <typename T, typename E>
Result<double, Error> Result<T, E>::divide(double dividend, double divisor) {
  if (divisor == 0)
    return new Error("Division by zero error");
  return dividend / divisor;
}

#endif  // TEPSEM3_RESULT_H
