//
// Created by micha on 10/26/2025.
//

#include "Number.h"
#include <iostream>
#include <string>

/* KONSTRUKTORY */

Number::Number(int value) {
  length = calcLength(value);
  table = new int[length];

  if (value < 0) {
    value = -value;
    isNegative = true;
  } else {
    isNegative = false;
  }

  if (value == 0) {
    table[0] = 0;
    return;
  }

  for (int i = length - 1; i >= 0; --i) {
    table[i] = value % 10;
    value /= 10;
  }
}

Number::Number(const int* table, int length, bool isNegative) {
  copyData(table, length, isNegative);
}

/* REGUŁA TRZECH */

Number::~Number() {
  delete[] table;
}

Number& Number::operator=(const Number &other) {
  if (this != &other) {
    delete[] table;
    copyData(other.table, other.length, other.isNegative);
  }
  return *this;
}

Number& Number::operator=(int value) {
  delete [] table;
  *this = Number(value);
  return *this;
}

Number::Number(const Number &other) {
  copyData(other.table, other.length, other.isNegative);
}

/* OPERATORY STRUMIENIOWE */

std::ostream& operator<<(std::ostream &os, const Number &number) {
  if (number.isNegative)
    os << '-';
  else
    os << '+';
  for (int i = 0; i < number.length; ++i)
    os << number.table[i];
  return os;
}

std::string Number::toString() const {
  std::string result;
  if (isNegative)
    result += '-';
  for (int i = 0; i < length; ++i)
    result += static_cast<char>(table[i]);
  return result;
}

/* OPERATORY MATEMATYCZNE */

Number Number::add(const Number &other) const {
  int maxLength = (length > other.length) ? length : other.length;

  int carry = 0;
  int i = length - 1;
  int j = other.length - 1;
  int *tempTable = new int[maxLength + 1];

  int index = 0;
  while (i >= 0 || j >= 0 || carry > 0) {
    int sum = carry;

    if (i >= 0)
      sum += table[i--];
    if (j >= 0)
      sum += other.table[j--];

    tempTable[index++] = sum % 10;
    carry = sum / 10;
  }

  reverseTable(tempTable, index);

  Number result(tempTable, index, false);
  delete[] tempTable;
  return result;
}

Number Number::subtract(const Number &other) const {
  int borrow = 0;
  bool willBeNegative = true;

  Number bigger = other;
  Number smaller = *this;
  if (this->isGreater(other)) {
    willBeNegative = false;
    bigger = *this;
    smaller = other;
  }

  int i = bigger.length - 1;
  int j = smaller.length - 1;
  int *tempTable = new int[bigger.length];

  int index = 0;
  while (i >= 0) {
    int digit1 = bigger.table[i];
    int digit2 = (j >= 0) ? smaller.table[j] : 0;

    digit1 -= borrow;
    if (digit1 < digit2) {
      digit1 += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    tempTable[index++] = digit1 - digit2;
    i--;
    j--;
  }

  reverseTable(tempTable, index);

  int zeros = 0;
  while (zeros < index - 1 && tempTable[zeros] == 0)
    zeros++;

  Number result(tempTable, index - zeros, willBeNegative);
  delete[] tempTable;
  return result;
}

Number Number::multiply(const Number &other) const {
  return Number(0);
}

Number Number::devide(const Number &other) const {
  return Number(0);
}

/* OPERATORY ARYTMETYCZNE */

Number Number::operator+(const Number &other) const {
  // A + B
  if (!this->isNegative && !other.isNegative)
    return this->add(other);

  // A + (-B) = A - B
  if (!this->isNegative && other.isNegative)
    return this->subtract(other);

  // (-A) + B = B - A
  if (this->isNegative && !other.isNegative)
    return other.subtract(*this);

  // (-A) + (-B) = -(A + B)
  Number result = this->add(other);
  result.isNegative = true;
  return result;
}

Number Number::operator-(const Number &other) const {
  // A - (-B) = A + B
  if (!this->isNegative && other.isNegative)
    return this->add(other);

  // A - B
  if (!this->isNegative && !other.isNegative)
    return this->subtract(other);

  // (-A) - (-B) = B - A
  if (this->isNegative && other.isNegative)
    return other.subtract(*this);

  // (-A) - B = -(A + B)
  Number result = this->add(other);
  result.isNegative = true;
  return result;
}

Number Number::operator*(const Number &other) const {

}

Number Number::operator/(const Number &other) const {

}

/* OPERATORY ARYTMETYCZNE Z INT */

Number Number::operator+(int value) const {
  return *this + Number(value);
}

Number Number::operator-(int value) const {
  return *this - Number(value);
}

Number Number::operator*(int value) const {
  return *this * Number(value);
}

Number Number::operator/(int value) const {
  return *this / Number(value);
}

/* POMOCNICZE */

int Number::calcLength(int value) {
  if (value == 0)
    return 1;

  int counter = 0;
  while (value != 0) {
    value /= 10;
    counter++;
  }
  return counter;
}

void Number::reverseTable(int *tempTable, int size) {
  for (int i = 0; i < size / 2; ++i) {
    int temp = tempTable[i];
    tempTable[i] = tempTable[size - i - 1];
    tempTable[size - i - 1] = temp;
  }
}

bool Number::isGreater(const Number &other) const {
  if (this->isNegative && !other.isNegative)
    return false;
  if (!this->isNegative && other.isNegative)
    return true;

  if (this->length > other.length)
    return !this->isNegative;

  if (this->length < other.length)
    return this->isNegative;

  for (int i = 0; i < this->length; ++i) {
    if (this->table[i] > other.table[i])
      return !this->isNegative;
    if (this->table[i] < other.table[i])
      return this->isNegative;
  }

  return false;
}

void Number::copyData(const int *newTable, int newLength, bool newIsNegative) {
  this->length = newLength;
  this->isNegative = newIsNegative;
  this->table = new int[newLength];
  for (int i = 0; i < newLength; ++i)
    table[i] = newTable[i];
}