#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "gadget.h"

#define CLP      0xaa401f0f
#define JLP      0xbb401f0f
#define RLP      0xcc401f0f
#define LP_NEW_A 0x00841f0f
#define LP_NEW_B 0x00881f0f
#define LP_NEW_C 0x00441f0f

using namespace std;

Gadget::Gadget(const Operation& startOperation, const Operation& endOperation, const vector<Operation>& operations, const string& fileName)
  : _startOperation(startOperation)
  , _endOperation(endOperation)
  , _operations(operations)
  , _fileName(fileName)
  {}


// This can be delted. Operation can be printed out like -> cout << gadget << endl;
void Gadget::Print() {
  cout << _fileName << "\t";
  _startOperation.Print();
  for(unsigned i=0;i<_operations.size();++i) {
    _operations[i].Print();
  }
  _endOperation.Print();
}

void Gadget::PrintOnFile(FileInfo* output) {
  fprintf(output->file, "%s\n", _fileName.c_str());
  _startOperation.PrintOnFile(output->file);
  fprintf(output->file, "\n");
  for(unsigned i=0;i<_operations.size();++i) {
    _operations[i].PrintOnFile(output->file);
    fprintf(output->file, "\n");
  }
  _endOperation.PrintOnFile(output->file);
  fprintf(output->file, "\n\n");
}

vector<Gadget> Gadget::FirstPassGadgetsRead(FileInfo& input) {

  ud_t ud_obj;
  ud_init(&ud_obj);
  ud_set_input_file(&ud_obj, input.file);
  ud_set_mode(&ud_obj, 64);
  ud_set_syntax(&ud_obj, UD_SYN_INTEL);

  vector<Gadget> gadgets;
  while (ud_disassemble(&ud_obj)) {
    if(!isStartOfGadget(&ud_obj)) continue;

    Operation startOperation( getAddress(&ud_obj),
      getOpcode(&ud_obj), getAsmblyCode(&ud_obj));

    vector<Operation> operations;
    while (ud_disassemble(&ud_obj)) {
      if(isEndOfGadget(&ud_obj)) {
        Operation endOperation(getAddress(&ud_obj),
          getOpcode(&ud_obj), getAsmblyCode(&ud_obj));

        gadgets.push_back(Gadget(startOperation, endOperation, operations, input.fileName));
        break;
      }

      Operation operation( getAddress(&ud_obj),
        getOpcode(&ud_obj), getAsmblyCode(&ud_obj));

      operations.push_back(operation);

      if(operations.size() == input.depth - 1){
        break;
      }
    }
  }

  input.ResetFile();
  return gadgets;
}

vector<Gadget> Gadget::SecondPassGadgetsRead(FileInfo& input) {

  ud_t ud_obj;
  ud_init(&ud_obj);
  ud_set_input_file(&ud_obj, input.file);
  ud_set_mode(&ud_obj, 64);
  ud_set_syntax(&ud_obj, UD_SYN_INTEL);

  vector<Gadget> gadgets;
  while (ud_disassemble(&ud_obj)) {
    if(!isLP(&ud_obj)) continue;

    Operation startOperation( getAddress(&ud_obj),
      getOpcode(&ud_obj), getAsmblyCode(&ud_obj));

    vector<Operation> operations;
    while (ud_disassemble(&ud_obj)) {
      if(isEndOfGadget(&ud_obj)) {
        Operation endOperation(getAddress(&ud_obj),
          getOpcode(&ud_obj), getAsmblyCode(&ud_obj));

        Operation::RemoveDuplicate(startOperation, &operations);
        gadgets.push_back(Gadget(startOperation, endOperation, operations, input.fileName));
        break;
      }

      Operation operation( getAddress(&ud_obj),
        getOpcode(&ud_obj), getAsmblyCode(&ud_obj));

      operations.push_back(operation);

      if(operations.size() == input.depth - 1){
        break;
      }
    }
  }


  input.ResetFile();
  return gadgets;
}

vector<Gadget> Gadget::GetGadgetsEndWith(const string& checkType, const vector<Gadget>& gadgets) {
  vector<Gadget> theGadgets;
  for(auto& gadget : gadgets) {
    if(gadget._endOperation.equals(checkType))
      theGadgets.push_back(gadget);
  }
  return theGadgets;
}

ostream& operator<<(ostream& output, const Gadget& gadget) {
  output << gadget._startOperation << endl;
  for(unsigned i=0;i<gadget._operations.size();++i) {
    output << gadget._operations[i] << endl;
  }
  output << gadget._endOperation << endl;
  return output;
}

bool Gadget::isStartOfGadget(ud_t* ud_obj) {
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

vector<Gadget> Gadget::GetCallEndGadgetsWithSingleAddOrSub(const vector<Gadget>& gadgets, const int operationMaxLength) {
  vector<Gadget> theGadgets;
  for(const Gadget& gadget : gadgets){
    if(gadget._operations.size() <= operationMaxLength &&
       gadget._endOperation._operation == "call" && gadget._endOperation._regster1[0] != '0' &&
       gadget._endOperation._regster1[0] != 'x' && hasSingleAddOrSub(gadget))

      theGadgets.push_back(gadget);
  }
  return theGadgets;
}

bool Gadget::isLP(ud_t* ud_obj) {
  const uint8_t *instractionBuffer = ud_insn_ptr(ud_obj);
  int instraction = *(int*)instractionBuffer;
  switch(instraction) {
    case LP_NEW_A:
      return true;
    case LP_NEW_B:
      return true;
    case LP_NEW_C:
      return true;
    default:
      return false;
  }
}

bool Gadget::isEndOfGadget(ud_t* ud_obj) {
  static vector<string> retCallJmp{ "ret", "call", "jmp" };

  string asmblyInstraction = getAsmblyCode(ud_obj);
  for (string& endType : retCallJmp) {
    if (asmblyInstraction.rfind(endType) != string::npos)
      return true;
  }
  return false;
}

uint64_t Gadget::getAddress(ud_t* ud_obj) {
  return ud_insn_off(ud_obj);
}

vector<uint8_t> Gadget::getOpcode(ud_t* ud_obj) {
  vector<uint8_t> instractionSet;
  for(unsigned i=0;i<ud_insn_len(ud_obj);++i){
    instractionSet.push_back(ud_insn_ptr(ud_obj)[i]);
  }
  return instractionSet;
}

bool Gadget::hasSingleAddOrSub(const Gadget& gadget) {
  int count = 0;
  for(const Operation& operation:gadget._operations){
    if(operation._operation == "add" && gadget._endOperation._regster1 == operation._regster1 ||
       operation._operation == "sub" && gadget._endOperation._regster1 == operation._regster1 )
      ++count;

    if(count >= 2)
      return false;
  }
  if(count == 1) return true;
  else		return false;
}

string Gadget::getAsmblyCode(ud_t* ud_obj) {
  const uint8_t *instractionBuffer = ud_insn_ptr(ud_obj);
  int instraction = *(int*)instractionBuffer;
  switch(instraction) {
    case CLP:
      return "CLP";
    case JLP:
      return "JLP";
    case RLP:
      return "RLP";
    case LP_NEW_A:
      return "LP_NEW_A";
    case LP_NEW_B:
      return "LP_NEW_B";
    case LP_NEW_C:
      return "LP_NEW_C";
    default:
      return ud_insn_asm(ud_obj);
  }
}
