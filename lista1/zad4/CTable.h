//
// Created by S1iwa on 10.10.2025.
//

#ifndef TECHNIKIEFEKTYWNEGOPROGRAMOWANIASEM3_CTABLE_H
#define TECHNIKIEFEKTYWNEGOPROGRAMOWANIASEM3_CTABLE_H
#include <string>

using std::string;

class CTable {
private:
  std::string s_name;
  static string default_name;

  int size;
  static int default_size;

  int *table;

public:
  CTable();
  CTable(string sName, int iTableLen);
  CTable(CTable &pcOther);
  ~CTable();

  void vSetName(string sName);
  bool bSetNewSize(int iTableLen);

  CTable* pcClone();
  void copyFrom(const CTable& pcOther);

  string getName() const;
  int getSize() const;
};


#endif //TECHNIKIEFEKTYWNEGOPROGRAMOWANIASEM3_CTABLE_H