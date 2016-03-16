#ifndef SORTING_H_ 
#define SORTING_H_

#include <string>
#include <vector>
#include "Gadget.h"

using namespace std;

vector<Gadget> GetRetGadgets(vector<Gadget> gadgets);
vector<Gadget> LoadOperations(vector<Gadget> gadgets, string reg);
vector<Gadget> RemoveMovSideEffect(vector<Gadget> gadgets, string reg);
vector<Gadget> RemoveMovSideEffectStorage(vector<Gadget> gadgets, string reg);
vector<Gadget> GetAddGadgets(vector<Gadget> gadgets, string reg); 
vector<Gadget> GetStorageGadgets(vector<Gadget> gadgets, string reg);
vector<string> splitstuff(string line);

void printResults(vector<Gadget> load, vector<Gadget> addition, vector<Gadget> store, string reg);
void printFinalResults(vector<vector<Gadget>> load, vector<vector<Gadget>> add, vector<vector<Gadget>> store );

bool isRegister(string reg);

#endif  // SORTING_H_ 