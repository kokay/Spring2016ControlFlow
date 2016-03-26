#ifndef OPERATION_H_
#define OPERATION_H_

#include <vector>
#include <stdio.h>

using namespace std;

class Operation {
  friend class Gadget;

public:
  Operation(const int64_t& address, const vector<uint8_t>& opcode, const string& asmblyCode);
  void Print();
  void PrintOnFile(FILE* outputFile);

private:
  friend ostream& operator<<(ostream& output, const Operation& gadget);
  bool equals(const string& checkType) const;
  static void RemoveDuplicate(const Operation& startOperation, vector<Operation>* operations);
  static bool isCast(const string& theRegister);

  int64_t _address;
  vector<uint8_t> _opcode;
  string _asmblyCode;
  string _operation;
  string _regster1;
  string _regster2;
};



#endif // OPERATION_H_
