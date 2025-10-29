//
// Created by micha on 10/26/2025.
//

#include "Number.h"
#include <iostream>

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
  *this = Number(value);
  return *this;
}

Number::Number(const Number &other) {
  copyData(other.table, other.length, other.isNegative);
}

/* OPERATORY STRUMIENIOWE */

std::ostream& operator<<(std::ostream &os, const Number &number) {
  for (int i = 0; i < number.length; ++i)
    os << number.table[i];
  return os;
}

/* OPERATORY ARYTMETYCZNE */

Number Number::operator+(const Number &other) const {
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

Number Number::operator-(const Number &other) const {
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

void Number::copyData(const int *newTable, int newLength, bool newIsNegative) {
  this->length = newLength;
  this->isNegative = newIsNegative;
  this->table = new int[newLength];
  for (int i = 0; i < newLength; ++i)
    table[i] = newTable[i];
}