#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <udis86.h>
#include "Gadget.h"
#include "FileInputOutput.h"

using namespace std;

int main(int argc, char* argv[]) {

  vector<FileInfo> inputInfos = FileInfo::GetInputFilesFromArguments(argc, argv);
  FileInfo outputInfo = FileInfo::GetOutputFileFromArguments(argc, argv);

  for(unsigned i=0;i<inputInfos.size();++i) {

    vector<Gadget> gadgets = Gadget::FirstPassGadgetsRead(inputInfos[i]);
    fprintf(outputInfo.file, "First Pass\n");
    for(unsigned j=0;j<gadgets.size();++j) {
      gadgets[j].PrintOnFile(&outputInfo);
    }

    gadgets = Gadget::SecondPassGadgetsRead(inputInfos[i]);
    fprintf(outputInfo.file, "Second Pass\n");
    for(unsigned j=0;j<gadgets.size();++j) {
      gadgets[j].PrintOnFile(&outputInfo);
    }

    fclose(inputInfos[i].file);
  }
  fclose(outputInfo.file);
}
