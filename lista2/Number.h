//
// Created by micha on 10/26/2025.
//

#ifndef TEPSEM3_NUMBER_H
#define TEPSEM3_NUMBER_H
#include <iosfwd>

class Number {
public:
  explicit Number(int value);
  Number(const Number &other);
  ~Number();

  Number& operator=(const Number &other);
  Number& operator=(int value);

  friend std::ostream& operator<<(std::ostream &os, const Number &number);
  std::string toString() const;

  Number add(const Number &other) const;
  Number subtract(const Number &other) const;
  Number multiply(const Number &other) const;
  Number devide(const Number &other) const;

  Number operator+(const Number &other) const;
  Number operator-(const Number &other) const;
  Number operator*(const Number &other) const;
  Number operator/(const Number &other) const;

  Number operator+(int value) const;
  Number operator-(int value) const;
  Number operator*(int value) const;
  Number operator/(int value) const;

private:
  int *table;
  int length;
  bool isNegative;

  Number(const int* table, int length, bool isNegative);

  static int calcLength(int value);
  static void reverseTable(int *tempTable, int size);
  bool isGreater(const Number &other) const;
  void copyData(const int *newTable, int newLength, bool newIsNegative);
};

#endif  // TEPSEM3_NUMBER_H
