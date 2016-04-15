#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <udis86.h>
#include "gadget.h"
#include "fileInputOutput.h"

int main(int argc, char* argv[]) {
  
  vector<FileInfo> inputInfos = FileInfo::GetInputFilesFromArguments(argc, argv);
  FileInfo outputInfo = FileInfo::GetOutputFileFromArguments(argc, argv);

  vector<int> gadgetCounts(7, 0);
  vector<Gadget> jlpClpRlpGadgets, abcdGadgets;
  for(unsigned i=0;i<inputInfos.size();++i) {

    fprintf(outputInfo.file, "%s:\n", inputInfos[i].fileName.c_str());

    jlpClpRlpGadgets = Gadget::FirstPassGadgetsRead(inputInfos[i]);
    fprintf(outputInfo.file, " Number of the jlpClpRlpGadgets:%d\n",int(jlpClpRlpGadgets.size()));
    for(auto& gadget:jlpClpRlpGadgets) {
      ++gadgetCounts[gadget.getType()]; //getType() returns a number corresponding to type of Gadget. For example, JLP for 0.
//      gadget.PrintOnFile(&outputInfo);
    }

    abcdGadgets = Gadget::SecondPassGadgetsRead(inputInfos[i]);
    fprintf(outputInfo.file, " Number of the abcdGadgets:%d\n",int(abcdGadgets.size()));
    for(auto& gadget:abcdGadgets) {
      ++gadgetCounts[gadget.getType()]; //getType() returns a number corresponding to type of Gadget. For example, JLP for 0.
//     gadget.PrintOnFile(&outputInfo);
    }
    fprintf(outputInfo.file, "\n");
  }

  Gadget::PrintGadgetCountsOnFile(gadgetCounts, inputInfos, &outputInfo);
  fclose(outputInfo.file);
  for(int i=0;i<inputInfos.size();++i) fclose(inputInfos[i].file);

  /*
  //theGadgets has all gadgets that call a register that only do a single add or subtract on the register.
  int operationsMaxLength = 100;
  vector<Gadget> theGadgets = Gadget::GetCallEndGadgetsWithSingleAddOrSub(jlpClpRlpGadgets, operationsMaxLength);
  fprintf(outputInfo.file, "Call end gadgets with single add or sub - Number of the gadgets:%d\n",int(theGadgets.size()));
  for(unsigned i=0;i<theGadgets.size();++i) {
    theGadgets[i].PrintOnFile(&outputInfo);
  }

  vector<Gadget> retGadgets = Gadget::GetGadgetsEndWith("ret", gadgets);
  while(true) {
    cout << "Which ROP turing complete case would you like to test for?" << endl;
    string input;
    cin >> input;

    if(input == "add") {
     // Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "sub") {
      //Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "mul") {
      //Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "div") {
      //Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "exit") {
      break;
    }
    else {
      cout << "Incorrect input" << endl;
    }
  }

  vector<Gadget> jmpGadgets = Gadget::GetGadgetsEndWith("jmp", gadgets);
  while(true) {
    cout << "Which JMP turing complete case would you like to test for?" << endl;
    string input;
    cin >> input;

    if(input == "add") {
     // Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "sub") {
      //Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "mul") {
      //Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "div") {
      //Gadget::GenerateAddProofs(retGadgets);
    }
    else if(input == "exit") {
      break;
    }
    else {
      cout << "Incorrect input" << endl;
    }
  }
*/
}
