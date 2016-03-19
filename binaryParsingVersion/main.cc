#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <udis86.h>
#include "Gadget.h"
#include "FileInputOutput.h"

using namespace std;

int main(int argc, char* argv[]) {

  vector<FILE*> inputFiles = GetInputFilesFromArguments(argc, argv);
  FILE* outputFile = GetOutputFileFromArguments(argc, argv);

  for(int i=0;i<inputFiles.size();++i) {

    vector<Gadget> gadgets = Gadget::ReadGadgetsFromBinary(inputFiles[i]);
    for(int j=0;j<gadgets.size();++j) {
      gadgets[j].PrintOnFile(outputFile);
    }

    fclose(inputFiles[i]);
  }
  fclose(outputFile);
}
