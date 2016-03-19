#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <udis86.h>
#include "Gadget.h"
#include "FileInputOutput.h"

using namespace std;
int main(int argc, char* argv[]) {

  vector<FileInfo> inputInfos = GetInputFilesFromArguments(argc, argv);
  FileInfo outputInfo = GetOutputFileFromArguments(argc, argv);

  for(int i=0;i<inputInfos.size();++i) {

    vector<Gadget> gadgets = Gadget::ReadGadgetsFromBinary(inputInfos[i]);
    for(int j=0;j<gadgets.size();++j) {
      gadgets[j].PrintOnFile(outputInfo);
    }

    fclose(inputInfos[i].file);
  }
  fclose(outputInfo.file);
}
