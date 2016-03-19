#ifndef FILEINPUTOUTPUT_H_
#define FILEINPUTOUTPUT_H_

#include <vector>
#include <stdio.h>

using namespace std;

vector<FILE*> GetInputFilesFromArguments(int argc, char* argv[]);
FILE* GetOutputFileFromArguments(int argc, char* argv[]);


#endif // FILEINPUTOUTPUT_H
