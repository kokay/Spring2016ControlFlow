#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Gadget.h"
#include "Sorting.h"


using namespace std;


void Subtraction(vector<Gadget> RetGadgets){

	vector<vector<Gadget>> loadGadgets64;
	vector<vector<Gadget>> loadGadgets32;

	vector<vector<Gadget>> subGadgets64;	
	vector<vector<Gadget>> subGadgets32;

	vector<vector<Gadget>> storageGadgets32;
	vector<vector<Gadget>> storageGadgets64;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (int i = 0; i < 16; i++){

		//getting the load gadgets for 64 bit
		loadGadgets64.push_back(LoadOperations(RetGadgets, _64Registers[i]));
		//getting the load gadgets for 32 bit
		loadGadgets32.push_back(LoadOperations(RetGadgets, _32Registers[i]));

		//getting the addition gadgets and removing the side effects for 64 bit
		subGadgets64.push_back(RemoveMovSideEffect(GetSubGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "add"));

		//getting the addition gadgets and removing the side effects for 32 bit
		subGadgets32.push_back(RemoveMovSideEffect(GetSubGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "add"));


		//getting the storage gadgets for 64 bit
		storageGadgets64.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "add"));

		//getting the storage gadgets for 32 bit
		storageGadgets32.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "add"));

	}

	//print results
	printFinalResults(loadGadgets64, subGadgets64, storageGadgets64, "_64BitSub.txt","Sub",true);
	printFinalResults(loadGadgets32, subGadgets32, storageGadgets32, "_32BitSub.txt","Sub",false);

}

void Addition(vector<Gadget> RetGadgets){

	vector<vector<Gadget>> loadGadgets64;
	vector<vector<Gadget>> loadGadgets32;

	vector<vector<Gadget>> subGadgets64;
	vector<vector<Gadget>> subGadgets32;

	vector<vector<Gadget>> storageGadgets32;
	vector<vector<Gadget>> storageGadgets64;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (int i = 0; i < 16; i++){

		//getting the load gadgets for 64 bit
		loadGadgets64.push_back(LoadOperations(RetGadgets, _64Registers[i]));
		//getting the load gadgets for 32 bit
		loadGadgets32.push_back(LoadOperations(RetGadgets, _32Registers[i]));

		//getting the addition gadgets and removing the side effects for 64 bit
		subGadgets64.push_back(RemoveMovSideEffect(GetAddGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the addition gadgets and removing the side effects for 32 bit
		subGadgets32.push_back(RemoveMovSideEffect(GetAddGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));


		//getting the storage gadgets for 64 bit
		storageGadgets64.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the storage gadgets for 32 bit
		storageGadgets32.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));

	}

	//print results
	printFinalResults(loadGadgets64, subGadgets64, storageGadgets64, "_64BitAdd.txt", "Add", true);
	printFinalResults(loadGadgets32, subGadgets32, storageGadgets32, "_32BitAdd.txt", "Add", false);

}
void Multiply(vector<Gadget> RetGadgets){

	vector<vector<Gadget>> loadGadgets64;
	vector<vector<Gadget>> loadGadgets32;

	vector<vector<Gadget>> subGadgets64;
	vector<vector<Gadget>> subGadgets32;

	vector<vector<Gadget>> storageGadgets32;
	vector<vector<Gadget>> storageGadgets64;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (int i = 0; i < 16; i++){

		//getting the load gadgets for 64 bit
		loadGadgets64.push_back(LoadOperations(RetGadgets, _64Registers[i]));
		//getting the load gadgets for 32 bit
		loadGadgets32.push_back(LoadOperations(RetGadgets, _32Registers[i]));

		//getting the multiply gadgets and removing the side effects for 64 bit
		subGadgets64.push_back(RemoveMovSideEffect(GetMulGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the multiply gadgets and removing the side effects for 32 bit
		subGadgets32.push_back(RemoveMovSideEffect(GetMulGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));


		//getting the storage gadgets for 64 bit
		storageGadgets64.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the storage gadgets for 32 bit
		storageGadgets32.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));

	}

	//print results
	printFinalResults(loadGadgets64, subGadgets64, storageGadgets64, "_64BitMultiply.txt", "Multiply", true);
	printFinalResults(loadGadgets32, subGadgets32, storageGadgets32, "_32BitMultiply.txt", "Multiply", false);

}
void Divide(vector<Gadget> RetGadgets){

	vector<vector<Gadget>> loadGadgets64;
	vector<vector<Gadget>> loadGadgets32;

	vector<vector<Gadget>> subGadgets64;
	vector<vector<Gadget>> subGadgets32;

	vector<vector<Gadget>> storageGadgets32;
	vector<vector<Gadget>> storageGadgets64;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (int i = 0; i < 16; i++){

		//getting the load gadgets for 64 bit
		loadGadgets64.push_back(LoadOperations(RetGadgets, _64Registers[i]));
		//getting the load gadgets for 32 bit
		loadGadgets32.push_back(LoadOperations(RetGadgets, _32Registers[i]));

		//getting the divide gadgets and removing the side effects for 64 bit
		subGadgets64.push_back(RemoveMovSideEffect(GetDivGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the divide gadgets and removing the side effects for 32 bit
		subGadgets32.push_back(RemoveMovSideEffect(GetDivGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));


		//getting the storage gadgets for 64 bit
		storageGadgets64.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the storage gadgets for 32 bit
		storageGadgets32.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));

	}

	//print results
	printFinalResults(loadGadgets64, subGadgets64, storageGadgets64, "_64BitDivide.txt", "Divide", true);
	printFinalResults(loadGadgets32, subGadgets32, storageGadgets32, "_32BitDivide.txt", "Divide", false);

}
void neg(vector<Gadget> RetGadgets){

	vector<vector<Gadget>> loadGadgets64;
	vector<vector<Gadget>> loadGadgets32;

	vector<vector<Gadget>> negGadgets64;
	vector<vector<Gadget>> negGadgets32;

	vector<vector<Gadget>> storageGadgets32;
	vector<vector<Gadget>> storageGadgets64;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (int i = 0; i < 16; i++){

		//getting the load gadgets for 64 bit
		loadGadgets64.push_back(LoadOperations(RetGadgets, _64Registers[i]));
		//getting the load gadgets for 32 bit
		loadGadgets32.push_back(LoadOperations(RetGadgets, _32Registers[i]));

		//getting the divide gadgets and removing the side effects for 64 bit
		negGadgets64.push_back(RemoveMovSideEffect(GetNegGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the divide gadgets and removing the side effects for 32 bit
		negGadgets32.push_back(RemoveMovSideEffect(GetNegGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));


		//getting the storage gadgets for 64 bit
		storageGadgets64.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the storage gadgets for 32 bit
		storageGadgets32.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));

	}

	//print results
	printFinalResults(loadGadgets64, negGadgets64, storageGadgets64, "_64BitNeg.txt", "Neg", true);
	printFinalResults(loadGadgets32, negGadgets32, storageGadgets32, "_32BitNeg.txt", "Neg", false);

}

void ExclusiveOr(vector<Gadget> RetGadgets){

	vector<vector<Gadget>> loadGadgets64;
	vector<vector<Gadget>> loadGadgets32;

	vector<vector<Gadget>> xorGadgets64;
	vector<vector<Gadget>> xorGadgets32;

	vector<vector<Gadget>> storageGadgets32;
	vector<vector<Gadget>> storageGadgets64;

	//all the functions used in this loop can be found in 'sorting.cpp'
	for (int i = 0; i < 16; i++){

		//getting the load gadgets for 64 bit
		loadGadgets64.push_back(LoadOperations(RetGadgets, _64Registers[i]));
		//getting the load gadgets for 32 bit
		loadGadgets32.push_back(LoadOperations(RetGadgets, _32Registers[i]));

		//getting the divide gadgets and removing the side effects for 64 bit
		xorGadgets64.push_back(RemoveMovSideEffect(GetXorGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the divide gadgets and removing the side effects for 32 bit
		xorGadgets32.push_back(RemoveMovSideEffect(GetXorGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));


		//getting the storage gadgets for 64 bit
		storageGadgets64.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _64Registers[i], _32Registers[i]), _64Registers[i], _32Registers[i], "sub"));

		//getting the storage gadgets for 32 bit
		storageGadgets32.push_back(RemoveMovSideEffectStorage(GetStorageGadgets(RetGadgets, _32Registers[i], _64Registers[i]), _32Registers[i], _64Registers[i], "sub"));

	}

	//print results
	printFinalResults(loadGadgets64, xorGadgets64, storageGadgets64, "_64BitXor.txt", "Xor", true);
	printFinalResults(loadGadgets32, xorGadgets32, storageGadgets32, "_32BitXor.txt", "Xor", false);

}



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


	Addition(RetGadgets);
	Subtraction(RetGadgets);
	Multiply(RetGadgets);
	Divide(RetGadgets);
	neg(RetGadgets);
	ExclusiveOr(RetGadgets);

	inputFile.close();
}