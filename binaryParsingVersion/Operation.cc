#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Operation.h"

Operation::Operation(const int64_t& address, const vector<uint8_t>& instractionSet, const string& asmblyInstraction)
  : _address(address)
  , _instractionSet(instractionSet)
  , _asmblyInstraction(asmblyInstraction)
  {}

// This can be delted. Operation can be printed out like -> cout << operation << endl;
void Operation::Print() {
  printf( "%llx :\t", (unsigned long long)_address);
  for(unsigned i=0;i<_instractionSet.size();++i) {
    printf("%02x ", _instractionSet[i]);
  }

  int spaceSize = 0;
  if(_instractionSet.size() <= 10) spaceSize = 32 - _instractionSet.size() * 3;
  else                             spaceSize = 47 - _instractionSet.size() * 3;

  for(int i=0;i<spaceSize;++i) printf(" ");
  printf("%s", _asmblyInstraction.c_str());
}

void Operation::PrintOnFile(FILE* outputFile) {
  fprintf(outputFile, "%llx :\t", (unsigned long long)_address);
  for(unsigned i=0;i<_instractionSet.size();++i) {
    fprintf(outputFile, "%02x ", _instractionSet[i]);
  }

  int spaceSize = 0;
  if(_instractionSet.size() <= 10) spaceSize = 32 - _instractionSet.size() * 3;
  else                             spaceSize = 47 - _instractionSet.size() * 3;

  for(int i=0;i<spaceSize;++i) fprintf(outputFile, " ");
  fprintf(outputFile, "%s", _asmblyInstraction.c_str());
}

ostream& operator<<(ostream& output, const Operation& operation) {
  output << hex << (unsigned long long)operation._address << " :\t";
  for(unsigned i=0;i<operation._instractionSet.size();++i) {
    output << hex << setw(2) << setfill('0') << unsigned(operation._instractionSet[i]) << " ";
  }

  int spaceSize = 0;
  if(operation._instractionSet.size() <= 10) spaceSize = 32 - operation._instractionSet.size() * 3;
  else                             spaceSize = 47 - operation._instractionSet.size() * 3;

  for(int i=0;i<spaceSize;++i) output << " ";
  output << operation._asmblyInstraction;
  return output;
}

void Operation::RemoveDuplicate(const Operation& startOperation, vector<Operation>* operations) {
  int i = 0;
  for(i=0;operations->size();++i){
    if(startOperation._asmblyInstraction != (*operations)[i]._asmblyInstraction)
      break;
  }

  operations->erase(operations->begin(), operations->begin() + i);
}
