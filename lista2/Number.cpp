//
// Created by S1iwa on 10/26/2025.
//

#include "Number.h"
#include <iostream>
#include <string>

/* KONSTRUKTORY */

Number::Number(int value) {
  length = calcLength(value);
  table = new int[length];

  if (value < 0) {
    isNegative = true;
  } else {
    isNegative = false;
  }

  if (value == 0) {
    table[0] = 0;
    return;
  }

  for (int i = length - 1; i >= 0; --i) {
    int digit = value % 10;
    table[i] = (digit < 0) ? -digit : digit;
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
  // Number1 = number2 już usuwa tabelę, więc nie muszę tutaj, żeby dwa razy nie zwalniać
  *this = Number(value);
  return *this;
}

Number Number::operator-() const {
  Number copy = *this;
  if (!isZero())
    copy.isNegative = !copy.isNegative;
  return copy;
}

Number::Number(const Number &other) {
  copyData(other.table, other.length, other.isNegative);
}

/* OPERATORY STRUMIENIOWE */

std::ostream& operator<<(std::ostream &os, const Number &number) {
  os << number.toString();
  return os;
}

std::string Number::toString() const {
  if (isZero())
    return "0";
  std::string result;
  if (isNegative)
    result += '-';
  for (int i = 0; i < length; ++i)
    result += static_cast<char>(table[i] + '0');
  return result;
}

/* HELPERY MATEMATYCZNE */

Number Number::addHelper(const Number &other) const {
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

Number Number::subtractHelper(const Number &other) const {
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

  Number result(tempTable + zeros, index - zeros, willBeNegative);
  delete[] tempTable;
  return result;
}

/* OPERATORY MATEMATYCZNE */

Number Number::add(const Number &other) const {
  // A + B
  if (!this->isNegative && !other.isNegative)
    return this->addHelper(other);

  // A + (-B) = A - B
  if (!this->isNegative && other.isNegative)
    return this->subtractHelper(other);

  // (-A) + B = B - A
  if (this->isNegative && !other.isNegative)
    return other.subtractHelper(*this);

  // (-A) + (-B) = -(A + B)
  Number result = this->addHelper(other);
  result.isNegative = true;
  return result;
}

Number Number::subtract(const Number &other) const {
  // A - (-B) = A + B
  if (!this->isNegative && other.isNegative)
    return this->addHelper(other);

  // A - B
  if (!this->isNegative && !other.isNegative)
    return this->subtractHelper(other);

  // (-A) - (-B) = B - A
  if (this->isNegative && other.isNegative)
    return other.subtractHelper(*this);

  // (-A) - B = -(A + B)
  Number result = this->addHelper(other);
  result.isNegative = true;
  return result;

}

Number Number::multiply(const Number &other) const {
  if (isZero() || other.isZero())
    return Number(0);

  bool resultIsNegative = this->isNegative ^ other.isNegative;
  int m = this->length;
  int n = other.length;
  int resultSize = m + n;
  int *resultTable = new int[resultSize]();

  for (int i = m - 1; i >= 0; i--)
    for (int j = n - 1; j >= 0; j--) {
      int product = this->table[i] * other.table[j];
      int pos = (m - 1 - i) + (n - 1 - j);
      resultTable[pos] += product;
    }

  int carry = 0;
  for (int i = 0; i < resultSize; i++) {
    int sum = resultTable[i] + carry;
    resultTable[i] = sum % 10;
    carry = sum / 10;
  }

  int actualSize = resultSize;
  while (actualSize > 1 && resultTable[actualSize - 1] == 0)
    actualSize--;

  reverseTable(resultTable, actualSize);

  Number result(resultTable, actualSize, resultIsNegative);
  delete[] resultTable;
  return result;
}

Number Number::divide(const Number &other) const {
  if (other.isZero())
    throw std::invalid_argument("Division by zero is not allowed.");

  if (isZero())
    return Number(0);

  if (!isGreaterOrEqualD(other))
    return Number(0);

  bool resultIsNegative = this->isNegative ^ other.isNegative;

  Number reminder(0);
  Number absOther = other;
  absOther.isNegative = false;

  int *resultTable = new int[this->length];
  int index = 0;

  for (int i = 0; i < this->length; ++i) {
    reminder.internalAppend(table[i]);
    int count = 0;

    while (reminder.isGreaterOrEqualD(absOther)) {
      reminder.internalSubtract(absOther);
      count++;
    }

    resultTable[index++] = count;
  }

  int zeros = 0;
  while (zeros < index - 1 && resultTable[zeros] == 0)
    zeros++;
  int finalLength = index - zeros;

  Number result(resultTable + zeros, finalLength, resultIsNegative);
  delete[] resultTable;
  return result;
}

/* OPERATORY MATEMATYCZNE Z INT */

Number Number::add(int value) const {
  return this->add(Number(value));
}

Number Number::subtract(int value) const {
  return this->subtract(Number(value));
}

Number Number::multiply(int value) const {
  return this->multiply(Number(value));
}

Number Number::divide(int value) const {
  return this->divide(Number(value));
}

/* OPERATORY ARYTMETYCZNE */

Number Number::operator+(const Number& other) const {
  return this->add(other);
}

Number Number::operator-(const Number &other) const {
  return this->subtract(other);
}

Number Number::operator*(const Number &other) const {
  return this->multiply(other);
}

Number Number::operator/(const Number &other) const {
  return this->divide(other);
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

/* OPERATORY PORÓWNANIA */

bool Number::operator>(Number &other) const {
  if (this->isGreater(other))
    return true;
  return false;
}

bool Number::operator>=(Number &other) const {
  if (this->isGreater(other) || (*this == other))
    return true;
  return false;
}

bool Number::operator<(Number &other) const {
  if (this->isGreater(other))
    return false;
  return true;
}

bool Number::operator<=(Number &other) const {
  if (this->isGreater(other) || (*this == other))
    return false;
  return true;
}

bool Number::operator==(Number &other) const {
  if (this->isNegative != other.isNegative)
    return false;
  if (this->length != other.length)
    return false;
  for (int i = 0; i < this->length; ++i)
    if (this->table[i] != other.table[i])
      return false;
  return true;
}

/* OPERATORY INKREMENTACJI/DEKREMENTACJI */

Number& Number::operator++() {
  *this = this->add(Number(1));
  return *this;
}

Number Number::operator++(int) {
  Number temp = *this;
  ++(*this);
  return temp;
}

Number& Number::operator--() {
  *this = this->subtract(Number(1));
  return *this;
}

Number Number::operator--(int) {
  Number temp = *this;
  --(*this);
  return temp;
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

bool Number::isGreaterOrEqualD(const Number &other) const {
  if (this->length > other.length)
    return true;
  if (this->length < other.length)
    return false;

  for (int i = 0; i < this->length; ++i) {
    if (this->table[i] > other.table[i])
      return true;
    if (this->table[i] < other.table[i])
      return false;
  }

  return true;
}

bool Number::isZero() const {
  return (this->length == 1 && this->table[0] == 0);
}

void Number::internalAppend(int digit) {
  if (isZero()) {
    this->table[0] = digit;
    return;
  }

  int *newTable = new int[this->length + 1];
  for (int i = 0; i < this->length; ++i)
    newTable[i] = this->table[i];
  newTable[this->length] = digit;

  delete[] this->table;
  this->table = newTable;
  this->length++;
}

void Number::internalSubtract(const Number &other) {
  int borrow = 0;
  int i = this->length - 1;
  int j = other.length - 1;

  while (i >= 0) {
    int digit1 = this->table[i];
    int digit2 = (j >= 0) ? other.table[j] : 0;

    digit1 -= borrow;
    if (digit1 < digit2) {
      digit1 += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    this->table[i] = digit1 - digit2;
    i--;
    j--;
  }

  int zeros = 0;
  while (zeros < this->length - 1 && this->table[zeros] == 0)
    zeros++;

  if (zeros > 0) {
    int newLength = this->length - zeros;
    int *newTable = new int[newLength];
    for (int k = 0; k < newLength; ++k)
      newTable[k] = this->table[k + zeros];
    delete[] this->table;
    this->table = newTable;
    this->length = newLength;
  }
}

void Number::copyData(const int *newTable, int newLength, bool newIsNegative) {
  this->length = newLength;
  this->isNegative = newIsNegative;
  this->table = new int[newLength];
  for (int i = 0; i < newLength; ++i)
    table[i] = newTable[i];
}