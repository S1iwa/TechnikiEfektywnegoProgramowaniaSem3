//
// Created by S1iwa on 10.10.2025.
//

#include "CTable.h"

using namespace std;

int main() {
  CTable c_tab1;
  CTable c_tab2("tab2", 5);
  CTable c_tab3(c_tab2);
  CTable *pc_tab4 = c_tab3.pcClone();
  delete pc_tab4;
  return 0;
}

void v_mod_tab(CTable *pcTab, int iNewSize) {
  pcTab -> bSetNewSize(iNewSize);
}

void v_mod_tab(CTable cTab, int iNewSize) {
  cTab.bSetNewSize(iNewSize);
}