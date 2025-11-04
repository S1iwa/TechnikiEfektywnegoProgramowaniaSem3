//
// Created by S1iwa on 10.10.2025.
//

#include "CTable.h"

#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::string;
using std::min;

string CTable::default_name = "default";
int CTable::default_size = 10;

CTable::CTable() {
  vSetName(default_name);
  cout << "bezp: '" << s_name << "'" << endl;

  size = default_size;
  table = new int[size];
}

CTable::CTable(string sName, int iTableLen) {
  if (iTableLen <= 0)
    cout << "Niepoprawny rozmiar tablicy! Wartosci musza byc dodatnie." << endl;

  if (sName.empty())
    vSetName("default");
  else
    vSetName(sName);
  cout << "parametr: '" << s_name << "'" << endl;

  if (iTableLen <= 0)
    size = 10;
  else
    size = iTableLen;
  table = new int[size];
}

CTable::CTable(CTable &pcOther) {
  copyFrom(pcOther);
}

CTable::~CTable() {
  cout << "usuwam: '" << s_name << "'" << endl;
  delete[] table;
}

void CTable::vSetName(string sName) {
  if (sName.empty())
    s_name = default_name;
  else
    s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen) {
  if (iTableLen <= 0)
    return false;

  int *newTable = new int[iTableLen];
  // if (newTable == NULL)
  //   return false;

  int minSize = min(iTableLen, size);
  for (int i = 0; i < minSize; i++)
    newTable[i] = table[i];

  delete[] table;
  table = newTable;
  size = iTableLen;
  return true;
}

CTable* CTable::pcClone() {
  return new CTable(*this);
}

void CTable::copyFrom(const CTable &pcOther) {
  vSetName(pcOther.s_name + "_copy");
  cout << s_name << endl;

  size = pcOther.size;
  table = new int[size];
  // if (table != NULL)
    for (int i = 0; i < size; i++)
      table[i] = pcOther.table[i];
  // else
  //   size = 0;

  cout << "kopiuj: '" << s_name << "'" << endl;
}

string CTable::getName() const {
  return s_name;
}

int CTable::getSize() const {
  return size;
}

// Modyfikacja
void CTable::insertHere(int iStartIndex, const CTable &pcOther) {
  if (iStartIndex < 0 || iStartIndex > size)
    return;

  int newSize = size + pcOther.size;
  int* newTable = new int[newSize];

  for (int i = 0; i < iStartIndex; i++)
    newTable[i] = table[i];

  for (int i = 0; i < pcOther.size; i++)
    newTable[iStartIndex + i] = pcOther.table[i];

  for (int i = iStartIndex; i < size; i++)
    newTable[pcOther.size + i] = table[i];

  delete[] table;
  table = newTable;
  size = newSize;
}

void CTable::setTableValue(int index, int value) const {
  if (index >= 0 && index < size) {
    table[index] = value;
  }
}

void CTable::print() const {
  cout << "Nazwa: " << s_name << ", Rozmiar: " << size << ", Elementy: ";
  for (int i = 0; i < size; i++)
    cout << table[i] << " ";
  cout << endl;
}