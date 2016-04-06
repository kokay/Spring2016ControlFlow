#ifndef GADGET_H_
#define GADGET_H_

#include <string>
#include <vector>
#include <udis86.h>
#include "Operation.h"
#include "FileInputOutput.h"

using namespace std;

class Gadget {
public:
  Gadget(const Operation& startOperation, const Operation& endOperation, const vector<Operation>& operations, const string& fileName);
  void Print();
  void PrintOnFile(FileInfo* input);
  static vector<Gadget> FirstPassGadgetsRead(FileInfo& input);
  static vector<Gadget> SecondPassGadgetsRead(FileInfo& input);
  static vector<Gadget> GetGadgetsEndWith(const string& checkType, const vector<Gadget>& gadgets);
  static vector<Gadget> GetCallEndGadgetsWithSingleAddOrSub(const vector<Gadget>& gadgets, const int operationMaxLength);


private:
  friend ostream& operator<<(ostream& output, const Gadget& gadget);
  static bool isStartOfGadget(ud_t* id_obj);
  static bool isLP(ud_t* id_obj);
  static bool isEndOfGadget(ud_t* id_obj);
  static bool hasSingleAddOrSub(const Gadget& gadget);
  static uint64_t getAddress(ud_t* ud_obj);
  static vector<uint8_t> getOpcode(ud_t* ud_obj);
  static string getAsmblyCode(ud_t* ud_obj);

  Operation _startOperation;
  Operation _endOperation;
  vector<Operation> _operations;
  string _fileName;
};

#endif  // GADGET_H_
