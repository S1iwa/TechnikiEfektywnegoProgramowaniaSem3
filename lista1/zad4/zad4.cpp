//
// Created by S1iwa on 10.10.2025.
//

#include "CTable.h"
#include "zad4.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
  // CTable c_tab1;
  // CTable c_tab2("tab2", 5);
  // CTable c_tab3(c_tab2);
  // CTable *pc_tab4 = c_tab3.pcClone();
  // delete pc_tab4;
  // cout << endl << endl;
  //
  // CTable cTable3("trojka", 3);
  // CTable cTable4("czworka", 4);
  //
  // v_mod_tab(&cTable3, 30);
  // v_mod_tab(cTable4, 40);

  CTable table("tablica testowa", 3);
  table.setTableValue(0, 1);
  table.setTableValue(1, 2);
  table.setTableValue(2, 3);
  table.print();

  CTable wstawiana("wstawiana", 4);
  wstawiana.setTableValue(0, 7);
  wstawiana.setTableValue(1, 8);
  wstawiana.setTableValue(2, 9);
  wstawiana.setTableValue(3, 10);
  wstawiana.print();

  table.insertHere(0, wstawiana);
  table.print();
  return 0;
}

void v_mod_tab(CTable *pcTab, int iNewSize) {
  pcTab -> bSetNewSize(iNewSize);
  cout << "Nowy rozmiar " << pcTab -> getName() << " to: " << pcTab -> getSize()  << endl;
}

void v_mod_tab(CTable cTab, int iNewSize) {
  cTab.bSetNewSize(iNewSize);
  cout << "Nowy rozmiar " << cTab.getName() << " to: " << cTab.getSize()  << endl;
}