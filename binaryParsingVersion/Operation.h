#ifndef OPERATION_H_
#define OPERATION_H_

#include <vector>
#include <stdio.h>

using namespace std;

class Operation {
public:
  Operation(const int64_t& address, const vector<uint8_t>& instractionSet, const string& asmblyInstraction);
  void Print();
  void PrintOnFile(FILE* outputFile);
  static void RemoveDuplicate(const Operation& startOperation, vector<Operation>* operations);

private:
  friend ostream& operator<<(ostream& output, const Operation& gadget);

  int64_t _address;
  vector<uint8_t> _instractionSet;
  string _asmblyInstraction;
};



#endif // OPERATION_H_
