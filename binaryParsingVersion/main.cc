#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Gadget.h"
#include <udis86.h>

using namespace std;

int main(int argc, char* argv[]) {

  if(argc != 2) {
    cout << "Please indicate one input file." << endl;
    exit(1);   
  }

  FILE* inputFile = fopen(argv[1], "r");
  if(inputFile == NULL) {
    cout << argv[1] << " cannot open." << endl;
    exit(1);
  }

  vector<Gadget> gadgets = Gadget::ReadGadgetsFromBinary(inputFile);
  for(int i=0;i<gadgets.size();++i) {
    gadgets[i].Print();
    getchar();
  }

  fclose(inputFile);
}
