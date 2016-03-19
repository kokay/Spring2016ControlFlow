#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Gadget.h"
#include <udis86.h>

using namespace std;

vector<FILE*> GetInputFilesFromArguments(int argc, char* argv[]) {
  if(argc < 2 || string(argv[1]) == "-o") {
    cout << "usage: test input_file1 [input_file2 ...] [-o output_file]" << endl;
    exit(1);
  }

  vector<FILE*> inputFiles;
  for(int i=1;i<argc;++i) {
    if(string(argv[i]) == "-o") return inputFiles;

    FILE* inputFile = fopen(argv[i], "r");
    if(inputFile == NULL) {
      cout << argv[i] << " cannot open." << endl;
      exit(1);
    }
    inputFiles.push_back(inputFile);
  }
  return inputFiles;
}

FILE* GetOutputFileFromArguments(int argc, char* argv[]) {
  FILE* outputFile;
  for(int i=2;i<argc;++i) {
    if(string(argv[i]) == "-o") {
      if(argc == i + 2) {
        outputFile = fopen(argv[i+1], "w");
        return outputFile;
      }
      else {
        cout << "usage: test input_file1 [input_file2 ...] [-o output_file]" << endl;
        exit(1);
      }
    }
  }

  outputFile = fopen("output.txt", "w");
  return outputFile;
}


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
