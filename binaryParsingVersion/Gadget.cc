#include <string>
#include <vector>
#include "Gadget.h"
#include <iostream>


using namespace std;

Operation::Operation(const int64_t& address, const vector<uint8_t>& instractionSet, const string& asmblyInstraction)
  : _address(address) 
  , _instractionSet(instractionSet)
  , _asmblyInstraction(asmblyInstraction)
  {}

void Operation::Print() {
  printf( "%llx :\t", (unsigned long long)_address);
  for(int i=0;i<_instractionSet.size();++i) {
    printf("%02x ", _instractionSet[i]); 
  }
  
  int spaceSize = 0;
  if(_instractionSet.size() <= 10) spaceSize = 32 - _instractionSet.size() * 3;
  else                             spaceSize = 47 - _instractionSet.size() * 3;

  for(int i=0;i<spaceSize;++i) printf(" ");
  cout << _asmblyInstraction << endl;
}

Gadget::Gadget(const Operation& startOperation, const Operation& endOperation, const vector<Operation>& operations)
  : _startOperation(startOperation)
  , _endOperation(endOperation)
  , _operations(operations)
  {}

void Gadget::Print() {
  _startOperation.Print();
  for(int i=0;i<_operations.size();++i) {
    cout << "  ";
    _operations[i].Print();
  }
  _endOperation.Print();
}

vector<Gadget> Gadget::ReadGadgetsFromBinary(FILE* inputFile) {
 
  ud_t ud_obj;
  ud_init(&ud_obj);
  ud_set_input_file(&ud_obj, inputFile);
  ud_set_mode(&ud_obj, 64);
  ud_set_syntax(&ud_obj, UD_SYN_INTEL);

  vector<Gadget> gadgets;
  while (ud_disassemble(&ud_obj)) {
    if(!isStartOfGadget(&ud_obj)) continue;

    Operation startOperation(
      getAddress(&ud_obj),
      getInstractionSet(&ud_obj),
      getAsmblyInstraction(&ud_obj));
      
    vector<Operation> operations;
    while (ud_disassemble(&ud_obj)) {
      if(isEndOfGadget(&ud_obj)) break;

      operations.push_back(Operation(
        getAddress(&ud_obj),
        getInstractionSet(&ud_obj), 
        getAsmblyInstraction(&ud_obj))); 
    }
   
    Operation endOperation(
      getAddress(&ud_obj),
      getInstractionSet(&ud_obj),
      getAsmblyInstraction(&ud_obj));
      
    gadgets.push_back(Gadget(startOperation, endOperation, operations));
  }
  return gadgets; 
}

bool Gadget::isStartOfGadget(ud_t* ud_obj) {
  static const unsigned long long CLP = 0xaa401f0f;
  static const unsigned long long JLP = 0xbb401f0f;
  static const unsigned long long RLP = 0xcc401f0f;
  
  const uint8_t *instractionBuffer = ud_insn_ptr(ud_obj); 
  int instraction = *(int*)instractionBuffer;
  switch(instraction) {
    case CLP:
      return true;
    case JLP:
      return true;
    case RLP:
      return true;
    default:
      return false;
  }
}

bool Gadget::isEndOfGadget(ud_t* ud_obj) {
  static vector<string> retCallJmp{ "ret", "call", "jmp" };
  
  string asmblyInstraction = getAsmblyInstraction(ud_obj);
  for (string& endType : retCallJmp) {
    if (asmblyInstraction.rfind(endType) != string::npos) 
      return true;
  }
  return false;
}

uint64_t Gadget::getAddress(ud_t* ud_obj) {
  return ud_insn_off(ud_obj);	
}

vector<uint8_t> Gadget::getInstractionSet(ud_t* ud_obj) {
  vector<uint8_t> instractionSet;
  for(int i=0;i<ud_insn_len(ud_obj);++i){
    instractionSet.push_back(ud_insn_ptr(ud_obj)[i]);
  }
  return instractionSet;
}

string Gadget::getAsmblyInstraction(ud_t* ud_obj) {
  static const unsigned long long CLP = 0xaa401f0f;
  static const unsigned long long JLP = 0xbb401f0f;
  static const unsigned long long RLP = 0xcc401f0f;
  
  const uint8_t *instractionBuffer = ud_insn_ptr(ud_obj); 
  int instraction = *(int*)instractionBuffer;
  switch(instraction) {
    case CLP:
      return "CLP";
    case JLP:
      return "JLP";
    case RLP:
      return "RLP";
    default:
      return ud_insn_asm(ud_obj);
  }
}
