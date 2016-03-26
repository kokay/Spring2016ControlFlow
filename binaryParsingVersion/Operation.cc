#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Operation.h"

Operation::Operation(const int64_t& address, const vector<uint8_t>& opcode, const string& asmblyCode)
  : _address(address)
  , _opcode(opcode)
  , _asmblyCode(asmblyCode) {

  stringstream ss(_asmblyCode);
  ss >> _operation;
  ss >> _regster1;
  if(isCast(_regster1)) {
    string tmp;
    ss >> tmp;
    _regster1.append(tmp);
  }

  ss >> _regster2;
  if(isCast(_regster2)) {
    string tmp;
    ss >> tmp;
    _regster2.append(tmp);
  }
}

bool Operation::isCast(const string& theRegister) {
  static vector<string> castTypes {"word", "byte"};

  for(auto& castType:castTypes) {
    if(theRegister.find(castType) != string::npos)
      return true;
  }
}

// This can be delted. Operation can be printed out like -> cout << operation << endl;
void Operation::Print() {
  printf( "%llx :\t", (unsigned long long)_address);
  for(unsigned i=0;i<_opcode.size();++i) {
    printf("%02x ", _opcode[i]);
  }

  int spaceSize = 0;
  if(_opcode.size() <= 10) spaceSize = 32 - _opcode.size() * 3;
  else                             spaceSize = 47 - _opcode.size() * 3;

  for(int i=0;i<spaceSize;++i) printf(" ");
  printf("%s", _asmblyCode.c_str());
}

void Operation::PrintOnFile(FILE* outputFile) {
  fprintf(outputFile, "%llx :\t", (unsigned long long)_address);
  for(unsigned i=0;i<_opcode.size();++i) {
    fprintf(outputFile, "%02x ", _opcode[i]);
  }

  int spaceSize = 0;
  if(_opcode.size() <= 10) spaceSize = 32 - _opcode.size() * 3;
  else                             spaceSize = 47 - _opcode.size() * 3;

  for(int i=0;i<spaceSize;++i) fprintf(outputFile, " ");
  fprintf(outputFile, "%s", _asmblyCode.c_str());
}

bool Operation::equals(const string& checkType) const {
  return _operation == checkType;
}

ostream& operator<<(ostream& output, const Operation& operation) {
  output << hex << (unsigned long long)operation._address << " :\t";
  for(unsigned i=0;i<operation._opcode.size();++i) {
    output << hex << setw(2) << setfill('0') << unsigned(operation._opcode[i]) << " ";
  }

  int spaceSize = 0;
  if(operation._opcode.size() <= 10) spaceSize = 32 - operation._opcode.size() * 3;
  else                             spaceSize = 47 - operation._opcode.size() * 3;

  for(int i=0;i<spaceSize;++i) output << " ";
  output << operation._asmblyCode;
  return output;
}

void Operation::RemoveDuplicate(const Operation& startOperation, vector<Operation>* operations) {
  int i = 0;
  for(i=0;operations->size();++i){
    if(startOperation._asmblyCode != (*operations)[i]._asmblyCode)
      break;
  }

  operations->erase(operations->begin(), operations->begin() + i);
}
