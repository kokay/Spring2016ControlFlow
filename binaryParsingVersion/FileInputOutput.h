#ifndef FILEINPUTOUTPUT_H_
#define FILEINPUTOUTPUT_H_

#include <vector>
#include <stdio.h>

using namespace std;

struct FileInfo {
  FileInfo(FILE* fileArg, const string& fileNameArg)
    : file(fileArg)
    , fileName(fileNameArg)
  {}

  FILE* file;
  string fileName;
};

vector<FileInfo> GetInputFilesFromArguments(int argc, char* argv[]);
FileInfo GetOutputFileFromArguments(int argc, char* argv[]);


#endif // FILEINPUTOUTPUT_H
