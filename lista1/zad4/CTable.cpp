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

CTable::CTable() {
  vSetName("default");
  cout << "bezp: '" << s_name << "'" << endl;
  size = 10;
  table = new int[size];
}

CTable::CTable(string sName, int iTableLen) {
  if (iTableLen <= 0)
    cout << "Niepoprawny rozmiar tablicy! Wartosci musza byc dodatnie." << endl;

  if (sName.empty())
    vSetName("default");
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
    s_name = "default";
  s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen) {
  if (iTableLen <= 0)
    return false;

  int *newTable = new int[iTableLen];
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
  for (int i = 0; i < size; i++)
    table[i] = pcOther.table[i];

  cout << "kopiuj: '" << s_name << "'" << endl;
}

string CTable::getName() const {
  return s_name;
}

int CTable::getSize() const {
  return size;
}