//
// Created by S1iwa on 10.10.2025.
//

#include <iostream>
#include "main.h"

using std::cout;
using std::endl;

int main() {
  int iSizeX = 5;
  int iSizeY = 3;
  int **table;

  // ReSharper disable once CppDFAConstantConditions
  if (!b_alloc_table_2_dim(&table, iSizeX, iSizeY)) {
    cout << "Niepoprawny rozmiar tablicy!" << endl;
    return -1;
  }

  wyswietlElementyTablicy(table, iSizeX, iSizeY);
  b_dealoc_table_2_dim(table, iSizeX, iSizeY);
  return 0;
}

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
  if (iSizeX <= 0 || iSizeY <= 0) {
    cout << "Niepoprawny rozmiar tablicy! Wartosci musza byc dodatnie." << endl;
    return false;
  }

  *piTable = new int*[iSizeY];

  for (int i = 0; i < iSizeY; i++)
    (*piTable)[i] = new int[iSizeX];

  return true;
}

// Nie potrzebujemy iSizeX
bool b_dealoc_table_2_dim(int **piTable, int iSizeX, int iSizeY) {
  for (int i = 0; i < iSizeY; i++)
    delete[] piTable[i];
  delete[] piTable;
  return true;
}

void wyswietlElementyTablicy(int **table, int iSizeX, int iSizeY) {
  for (int i = 0; i < iSizeY; i++) {
    for (int j = 0; j < iSizeX; j++)
      cout << table[i][j] << " ";
    cout << endl;
  }
}