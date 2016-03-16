#ifndef GADGET_H_ 
#define GADGET_H_

#include <string>
#include <vector>
#include <udis86.h>

using namespace std;

class Operation {
public:
  Operation(const int64_t& address, const vector<uint8_t>& instractionSet, const string& asmblyInstraction);
  void Print();
private:
  int64_t _address;
  vector<uint8_t> _instractionSet;
  string _asmblyInstraction;
};


class Gadget {
public:
  Gadget(const Operation& startOperation, const Operation& endOperation, const vector<Operation>& operations);
  void Print();
  static vector<Gadget> ReadGadgetsFromBinary(FILE* inputFile);
private:
  static bool isStartOfGadget(ud_t* id_obj);
  static bool isEndOfGadget(ud_t* id_obj);
  static uint64_t getAddress(ud_t* ud_obj);
  static vector<uint8_t> getInstractionSet(ud_t* ud_obj);
  static string getAsmblyInstraction(ud_t* ud_obj);
  Operation _startOperation;
  Operation _endOperation;
  vector<Operation> _operations;
};

#endif  // GADGET_H_ 
