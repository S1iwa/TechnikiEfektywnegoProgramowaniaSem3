//
// Created by S1iwa on 09.10.2025.
//

#include <iostream>
#include "zad1.h"

using std::cout;
using std::endl;

int main() {
  v_alloc_table_fill_34(3);
  return 0;
}

void v_alloc_table_fill_34(int iSize) {
  if (iSize <= 0) {
    cout << "Rozmiar tablicy musi byc wiekszy od 0." << endl;
    return;
  }

  int* table = NULL;
        table = new int[iSize];

  for (int i = 0; i < iSize; i++) {
    table[i] = value;
    cout << table[i] << endl;
  }

  delete[] table;
}

void wyswietlElementyTablicy(int *table, int iSize) {
  for (int i = 0; i < iSize; i++)
    cout << table[i] << " ";
  cout << endl;
}