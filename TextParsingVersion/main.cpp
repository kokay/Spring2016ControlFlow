#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Gadget.h"
#include "Sorting.h"


using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "Wrong!!" << endl;
		exit(1);
	}

	ifstream inputFile(argv[1]);
	if (!inputFile.is_open()) {
		cout << argv[1] << " cannot be opened." << endl;
		exit(1);
	}

	vector<Gadget> gadgets;
	string line;
	while (getline(inputFile, line)) {
		if (!Gadget::isStartOfGadget(line)) continue;

		string start(line);
		vector<Operation> operations;
		while (getline(inputFile, line)) {
			if (Gadget::isEndOfGadget(line)) break;

			operations.push_back(Operation(line));
		}
		gadgets.push_back(Gadget(start, line/*endLine*/, operations));
	}

	//start David stuff

	vector<Gadget> RetGadgets = GetRetGadgets(gadgets); //get gadgets that end in ret

	//vector of vectors to store each register
	//to make this faster, array of vectors should be used as we know how many vectors we have
	vector<vector<Gadget>> loadGadgets;
	vector<vector<Gadget>> addGadgets;
	vector<vector<Gadget>> storageGadgets;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (auto &reg : AllRegisters){

		//getting the load gadgets
		loadGadgets.push_back(LoadOperations(RetGadgets, reg));

		//getting the addution gadgets and removing the side effects
		addGadgets.push_back(RemoveMovSideEffect(GetAddGadgets(RetGadgets, reg), reg));

		//getting the storage gadgets
		storageGadgets.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, reg), reg));


	}

	//print results
	printFinalResults(loadGadgets, addGadgets, storageGadgets);


	

	//legacy stuff for only a single register

	//vector<Gadget> RaxRetGadgetsWithLoadOperation = LoadOperations(RetGadgets, "rax"); //get ret gadgets that perform a load operation on the register 'rax', this will need to be done for all registers
	//add gadgets
	//vector<Gadget> RaxAddGadgets = GetAddGadgets(RetGadgets, "rax"); //get gadgets that have addition
	//vector<Gadget> RaxRetAddNoSideEffect = RemoveMovSideEffect(RaxAddGadgets, "rax"); //remove add gadgets with mov side effect
	//storage gadgets
	//vector<Gadget> RaxStorageGadgets = GetStorageGadgets(RetGadgets, "rax"); //get gadgets that have storage
	//vector<Gadget> RaxStorageGadgetsNoSideEffects = RemoveMovSideEffectStorage(RaxStorageGadgets, "rax");

	//printResults(RaxRetGadgetsWithLoadOperation, RaxRetAddNoSideEffect, RaxStorageGadgetsNoSideEffects, "rax");



	inputFile.close();
}