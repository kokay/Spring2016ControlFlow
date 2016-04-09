#ifndef FILEINPUTOUTPUT_H_
#define FILEINPUTOUTPUT_H_

#include <vector>
#include <stdio.h>

using namespace std;

struct FileInfo {
  FileInfo(FILE* fileArg, const string& fileNameArg, const int depthArg);
  static vector<FileInfo> GetInputFilesFromArguments(int argc, char* argv[]);
  static FileInfo GetOutputFileFromArguments(int argc, char* argv[]);
  static void PrintUsage();
  void ResetFile();

  FILE* file;
  string fileName;
  int depth;
};

#endif // FILEINPUTOUTPUT_H
