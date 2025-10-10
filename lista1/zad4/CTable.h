//
// Created by S1iwa on 10.10.2025.
//

#ifndef TECHNIKIEFEKTYWNEGOPROGRAMOWANIASEM3_CTABLE_H
#define TECHNIKIEFEKTYWNEGOPROGRAMOWANIASEM3_CTABLE_H
#include <string>

class CTable {
  private:
  std::string s_name;
  int size;
  int *table;

  public:
  CTable();
  CTable(std::string sName, int iTableLen);
  CTable(CTable &pcOther);
  ~CTable();

  void vSetName(std::string sName);
  bool bSetNewSize(int iTableLen);

  CTable* pcClone();
  void copyFrom(const CTable& pcOther);
};


#endif //TECHNIKIEFEKTYWNEGOPROGRAMOWANIASEM3_CTABLE_H