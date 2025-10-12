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

  cout << endl;

  b_dealoc_table_2_dim(&table, iSizeY);

  wyswietlElementyTablicy(table, iSizeX, iSizeY);
  return 0;
}

bool b_alloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
  if (iSizeX <= 0 || iSizeY <= 0)
    return false;

  *piTable = new int*[iSizeY];

  for (int i = 0; i < iSizeY; i++) {
    (*piTable)[i] = new int[iSizeX];
    for (int j = 0; j < iSizeX; j++)
      (*piTable)[i][j] = j;
  }

  return true;
}

// Nie potrzebujemy iSizeX
bool b_dealoc_table_2_dim(int ***piTable, int iSizeY) {
  if (iSizeY <= 0 || *piTable == NULL)
    return false;

  for (int i = 0; i < iSizeY; i++)
    delete[] (*piTable)[i];
  delete[] *piTable;

  // Ustawiamy oryginalny wskaźnik w main na nullptr
  *piTable = NULL;

  return true;
}

void wyswietlElementyTablicy(int **table, int iSizeX, int iSizeY) {
  if (table == NULL) {
    cout << "Tablica nie istnieje!" << endl;
    return;
  }

  if (iSizeX <= 0 || iSizeY <= 0) {
    cout << "Niepoprawny rozmiar tablicy!" << endl;
    return;
  }

  for (int i = 0; i < iSizeY; i++) {
    for (int j = 0; j < iSizeX; j++)
      cout << table[i][j] << " ";
    cout << endl;
  }
}