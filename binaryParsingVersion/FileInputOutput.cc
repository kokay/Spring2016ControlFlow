#include <vector>
#include <string>
#include <iostream>
#include "FileInputOutput.h"

using namespace std;

FileInfo::FileInfo(FILE* fileArg, const string& fileNameArg, const int depthArg)
  : file(fileArg)
  , fileName(fileNameArg)
  , depth(depthArg)
  {}

void FileInfo::PrintUsage() {
  cout << "Usage: test input_file1 [input_file2 ...] [-d max_gadget_length] [-o output_file]" << endl;
}

vector<FileInfo> FileInfo::GetInputFilesFromArguments(int argc, char* argv[]) {
  vector<FileInfo> inputFiles;
  int depth = 10;

  for(int i=1;i<argc;++i) {
    if(argv[i][0] == '-') {
      if(string(argv[i]).size() != 2) {
        PrintUsage();
        exit(1);
      }

      switch(argv[i][1]) {
      case 'h':
        PrintUsage();
        exit(1);
      case 'd':
        ++i;
        if(i == argc) {
          cout << "Depth parameter is missed." << endl;
          PrintUsage();
          exit(1);
        }
        depth = atoi(argv[i]);
        if(depth < 2) {
          cout << "Depth has to be greater than 2." << endl;
          exit(1);
        }
        break;
      case 'o':
        i = argc;
        break;
      }
    }
    else {
      FILE* inputFile = fopen(argv[i], "r");
      if(inputFile == NULL) {
        cout << argv[i] << " cannot open." << endl;
        exit(1);
      }
      inputFiles.push_back(FileInfo(inputFile, string(argv[i]), depth));
    }
  }

  if(inputFiles.size() == 0){
    cout << "Input file is needed." << endl;
    PrintUsage();
    exit(1);
  }
  return inputFiles;
}

FileInfo FileInfo::GetOutputFileFromArguments(int argc, char* argv[]) {
  FILE* outputFile;
  for(int i=2;i<argc;++i) {
    if(string(argv[i]) == "-o") {
      if(argc == i + 2) {
        outputFile = fopen(argv[i+1], "w");
        return FileInfo(outputFile, string(argv[i+1]), 0);
      }
      else {
        PrintUsage();
        exit(1);
      }
    }
  }

  outputFile = fopen("output.txt", "w");
  return FileInfo(outputFile, "output.txt", 0);
}

void FileInfo::ResetFile() {
  rewind(file);
}
