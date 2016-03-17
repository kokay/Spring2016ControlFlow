#include "Sorting.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>

/*
This function gets the gadgets that end in ret. 
It also fills the 'register1 & 2' and 'operation' variables in the
Operation object to hep us with parsing later.
*/
vector<Gadget> GetRetGadgets(vector<Gadget> gadgets) {

	vector<Gadget> RetGadgets;
	vector<string> line;

	int vectorSize = 0;
	for (auto &i : gadgets){ //get the gadgets that end with ret
		if (i.finalDestination == "ret"){
			for (auto &j : i.operations){

				line = splitstuff(j.instruction);	
				j.operation = line[0];
				vectorSize = line.size();

				//while we're here lets fill our operation register object
				if (vectorSize >= 2 && line[1].substr(line[1].length() - 1) == ",")
					line[1].erase(line[1].size() - 1);				
				if (vectorSize >= 2 && (isRegister(line[1])))			
					j.register1 = line[1];
				if (vectorSize >= 3 && (isRegister(line[2])))
					j.register2 = line[2];
				if (line[0] == "add")
					j.addOperation = line[2];			
							
			}	
			RetGadgets.push_back(i);
		}
	}

	return RetGadgets; 
}

/*
This function gets the gadgets have load operations, 
it accounts for the register itself being popped and a
another register being popped and then mov(ed) into our gadget

input: 
-vector<gadgets>: vector of gadgets we want to search (currently main is sending only ret gadgets)
-string reg: the register we are testing

output:
-vector<gadgets> : will be a vector of gadgets with a load operation

*/
vector<Gadget> LoadOperations(vector<Gadget> gadgets, string reg) {

	vector<Gadget> gadgetsThatLoad;
	vector<string> loadedGadgets;

	bool hasGadgetPop = false;
	bool hasPop = false;

	for (auto &i : gadgets){ 
		hasGadgetPop = false;
		hasPop = false;
		loadedGadgets.clear();
		for (auto &j : i.operations){ 

			if (j.operation == "pop"){
				hasPop = true;
				loadedGadgets.push_back(j.register1);

				if (j.register1 == reg) //we have loaded our gadget
				{
					hasGadgetPop = true;
				}
			}

			if (j.operation == "mov" && j.register2 == reg && hasPop){ //even if the gadget we are looking for wasnt popped, it still may have been loaded through another register's pop and mov operation to our gadget

				for (auto &k : loadedGadgets){ //loop through the registers that have been loaded already in this gadget
					if (k == j.register1){
						hasGadgetPop = true;
					}
				}	

			}

		}
		if (hasGadgetPop)
			gadgetsThatLoad.push_back(i);
	}
	return gadgetsThatLoad;
}
/*
This function gets the gadgets have add operations

input:
-vector<gadgets>: vector of gadgets we want to search (currently main is sending only ret gadgets)
-string reg: the register we are testing

output:
-vector<gadgets> : will be a vector of gadgets with an add operation for the given register

*/
vector<Gadget> GetAddGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> addGadgets;
	bool hasAdd = false;

	for (auto &i : gadgets){
		hasAdd = false;
		for (auto &j : i.operations){
			if ((j.operation == "add" && j.register1 == reg1) && ((j.addOperation.find("0") == 0) || isRegister(j.addOperation)))
				hasAdd = true;
		}
		if (hasAdd && i.operations.size() < 20)
			addGadgets.push_back(i);
	}

	return addGadgets;
}
vector<Gadget> GetSubGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> addGadgets;
	bool hasAdd = false;

	for (auto &i : gadgets){
		hasAdd = false;
		for (auto &j : i.operations){
			if ((j.operation == "sub" && j.register1 == reg1) && ((j.addOperation.find("0") == 0) || isRegister(j.addOperation)))
				hasAdd = true;
		}
		if (hasAdd && i.operations.size() < 20)
			addGadgets.push_back(i);
	}

	return addGadgets;
}
vector<Gadget> GetMulGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> addGadgets;
	bool hasAdd = false;

	for (auto &i : gadgets){
		hasAdd = false;
		for (auto &j : i.operations){
			if ((j.operation == "mul" || j.operation == "imul") && j.register1 == reg1)
				hasAdd = true;
		}
		if (hasAdd && i.operations.size() < 20)
			addGadgets.push_back(i);
	}

	return addGadgets;
}
vector<Gadget> GetDivGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> addGadgets;
	bool hasAdd = false;

	for (auto &i : gadgets){
		hasAdd = false;
		for (auto &j : i.operations){
			if ((j.operation == "div" || j.operation == "idiv") && j.register1 == reg1 )
				hasAdd = true;
		}
		if (hasAdd && i.operations.size() < 20)
			addGadgets.push_back(i);
	}

	return addGadgets;
}
vector<Gadget> GetNegGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> addGadgets;
	bool hasAdd = false;

	for (auto &i : gadgets){
		hasAdd = false;
		for (auto &j : i.operations){
			if (j.operation == "neg"  && j.register1 == reg1 )
				hasAdd = true;
		}
		if (hasAdd && i.operations.size() < 20)
			addGadgets.push_back(i);
	}

	return addGadgets;
}
vector<Gadget> GetXorGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> addGadgets;
	bool hasAdd = false;

	for (auto &i : gadgets){
		hasAdd = false;
		for (auto &j : i.operations){
			if ((j.operation == "xor" || j.operation == "xorl" || j.operation == "exorl")  && j.register1 == reg1)
				hasAdd = true;
		}
		if (hasAdd && i.operations.size() < 20)
			addGadgets.push_back(i);
	}

	return addGadgets;
}
/*
This function gets the gadgets have storage operations

input:
-vector<gadgets>: vector of gadgets we want to search (currently main is sending only ret gadgets)
-string reg: the register we are testing

output:
-vector<gadgets> : will be a vector of gadgets with an storage operation for the given register

*/
vector<Gadget> GetStorageGadgets(vector<Gadget> gadgets, string reg1, string reg2){
	vector<Gadget> storageGadgets;
	bool hasStorage = false;

	for (auto &i : gadgets){
		hasStorage = false;
		for (auto &j : i.operations){
			if (j.operation == "mov" && j.register1 == reg1 && isRegister(j.register2))
				hasStorage = true;
		}
		if (hasStorage && i.operations.size() < 5 )
			storageGadgets.push_back(i);
	}

	return storageGadgets;

}

/*
This function get removes generic gadget side effects.
Its currently only being used with addition gadgets, 
may need to be renamed to reflect that it is geared
toward trimming the addition side effects, I'm still
unsure as to how generic these rules are

input:
-vector<gadgets>: vector of gadgets we want to search (currently main is sending only ret gadgets)
-string reg: the register we are testing

output:
-vector<gadgets> : will be a vector of gadgets with generic gadget side effects removed

*/
vector<Gadget> RemoveMovSideEffect(vector<Gadget> gadgets, string reg1, string reg2, string addOrSub) {
	vector<Gadget> newGadgets;
	
	bool goodGadget = true;
	for (auto &i : gadgets){
		goodGadget = true;
		for (auto &j : i.operations){
			if ((j.operation == "mov" &&
				(j.register2.find(reg1) != std::string::npos || j.register2.find(reg2) != std::string::npos)) ||
				(j.operation == "movzx" &&
				(j.register2.find(reg1) != std::string::npos || j.register2.find(reg2) != std::string::npos)) ||
				(j.operation == "lea" &&  
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)) ||
				(j.operation == addOrSub &&
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)) ||
				(j.operation == "pop" && 
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)) ||
				(j.operation == "xor" && 
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)))//something wrote over our register before storage
				goodGadget = false;
		}
		if (goodGadget)
			newGadgets.push_back(i);
	}
	return newGadgets;
}

/*
This function get removes storage gadget side effects

note: this will be moved into the initial getStorageGadgets 
function as the following is redundant logic

input:
-vector<gadgets>: vector of gadgets we want to search (currently main is sending only ret gadgets)
-string reg: the register we are testing

output:
-vector<gadgets> : will be a vector of gadgets with storage gadget side effects removed

*/
vector<Gadget> RemoveMovSideEffectStorage(vector<Gadget> gadgets, string reg1, string reg2, string addOrSub) {
	vector<Gadget> newGadgets;

	bool goodGadget = true;
	for (auto &i : gadgets){
		goodGadget = true;
		for (auto &j : i.operations){
			if (j.operation == "mov" && j.register1.find(reg1) != std::string::npos)
				continue; //our storage has been done, side effects dont matter anymore
			if ((j.operation == "mov" &&
				(j.register2.find(reg1) != std::string::npos || j.register2.find(reg2) != std::string::npos)) ||
				(j.operation == "movzx" &&
				(j.register2.find(reg1) != std::string::npos || j.register2.find(reg2) != std::string::npos)) ||
				(j.operation == "lea" &&
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)) ||
				(j.operation == "sub" &&
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)) ||
				(j.operation == "pop" &&
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)) ||
				(j.operation == "xor" &&
				(j.register1.find(reg1) != std::string::npos || j.register1.find(reg2) != std::string::npos)))//something wrote over our register before storage
				goodGadget = false;
		}
		if (goodGadget)
			newGadgets.push_back(i);
	}
	return newGadgets;
}


//helper function to split a space separeted line into a vector
//used for the operation line, ie: "mov r12, r13"
vector<string> splitstuff(string line){

	stringstream ss(line);
	istream_iterator<std::string> begin(ss);
	istream_iterator<std::string> end;
	vector<string> vstrings(begin, end);
	return vstrings;

}

//helper function to test if a string is a register
bool isRegister(string reg){
	
	if (reg == "rax" ||
		reg == "eax" ||
		reg == "ax" ||
		reg == "al" ||
		reg == "rbx" ||
		reg == "ebx" ||
		reg == "bx" ||
		reg == "bl" ||
		reg == "rcx" ||
		reg == "ecx" ||
		reg == "cx" ||
		reg == "cl" ||
		reg == "rdx" ||
		reg == "edx" ||
		reg == "dx" ||
		reg == "dl" ||
		reg == "rsi" ||
		reg == "esi" ||
		reg == "si" ||
		reg == "sil" ||
		reg == "rdi" ||
		reg == "edi" ||
		reg == "di" ||
		reg == "dil" ||
		reg == "rbp" ||
		reg == "ebp" ||
		reg == "bp" ||
		reg == "bpl" ||
		reg == "rsp" ||
		reg == "esp" ||
		reg == "sp" ||
		reg == "spl" ||
		reg == "r8" ||
		reg == "r8d" ||
		reg == "r8w" ||
		reg == "r8b" ||
		reg == "r9" ||
		reg == "r9d" ||
		reg == "r9w" ||
		reg == "r9b" ||
		reg == "r10" ||
		reg == "r10d" ||
		reg == "r10w" ||
		reg == "r10b" ||
		reg == "r11" ||
		reg == "r11d" ||
		reg == "r11w" ||
		reg == "r11b" ||
		reg == "r12" ||
		reg == "r12d" ||
		reg == "r12w" ||
		reg == "r12b" ||
		reg == "r13" ||
		reg == "r13d" ||
		reg == "r13w" ||
		reg == "r13b" ||
		reg == "r14" ||
		reg == "r14d" ||
		reg == "r14w" ||
		reg == "r14b" ||
		reg == "r15" ||
		reg == "r15d" ||
		reg == "r15w" ||
		reg == "r15b")
		return true; 
	return false; 
}

//prints all results
void printFinalResults(vector<vector<Gadget>> load, vector<vector<Gadget>> add, vector<vector<Gadget>> store, string filename, string typeOfOp, bool is64){
	ofstream myfile;
	myfile.open(filename);
	int i = 0;
	myfile << "~~~~~~~   " << "Load Gadget Section   ~~~~~~~~~\n\n";
	for (auto &reg : load){

		myfile << "Results for register: " << (is64 == true ? _64Registers[i] : _32Registers[i]) << ": \n ";
		myfile << "Load Gadgets Found:  \n\n";

		for (auto &i : reg){
			myfile << setw(10) << i.typeLineNumber << "\t\t\t\t" << i.typeOpcode << "\t\t\t\t" << i.type << "\n";
			for (auto &j : i.operations){
				myfile << setw(10) << j.lineNumber << setw(25) << j.opcode << setw(40) << j.instruction << "\n";
			}

			myfile << setw(10) << i.finalDestinationLineNumber << setw(25) << i.fianlDestinationOpcode << setw(40) << i.finalDestination << "\n\n\n";
		}

		i++;
	}
	i = 0;

	myfile << "~~~~~~~   " << typeOfOp << " Gadget Section   ~~~~~~~~~  \n\n";
	for (auto &reg : add){

		myfile << "Results for register: " << (is64 == true ? _64Registers[i] : _32Registers[i]) << ": \n ";
		myfile <<  typeOfOp << " Found:  \n\n";

		for (auto &i : reg){
			myfile << setw(10) << i.typeLineNumber << "\t\t\t\t" << i.typeOpcode << "\t\t\t\t" << i.type << "\n";
			for (auto &j : i.operations){
				myfile << setw(10) << j.lineNumber << setw(25) << j.opcode << setw(40) << j.instruction << "\n";
			}

			myfile << setw(10) << i.finalDestinationLineNumber << setw(25) << i.fianlDestinationOpcode << setw(40) << i.finalDestination << "\n\n\n";
		}

		i++;
	}
	i = 0;
	myfile << "~~~~~~~   Storage Gadget Section   ~~~~~~~~~  \n\n";
	for (auto &reg : store){

		myfile << "Results for register: " << (is64 == true ? _64Registers[i] : _32Registers[i]) << ": \n ";
		myfile << "Storage Gadgets Found:  \n\n";

		for (auto &i : reg){
			myfile << setw(10) << i.typeLineNumber << "\t\t\t\t" << i.typeOpcode << "\t\t\t\t" << i.type << "\n";
			for (auto &j : i.operations){
				myfile << setw(10) << j.lineNumber << setw(25) << j.opcode << setw(40) << j.instruction << "\n";
			}

			myfile << setw(10) << i.finalDestinationLineNumber << setw(25) << i.fianlDestinationOpcode << setw(40) << i.finalDestination << "\n\n\n";
		}

		i++;
	}

	myfile.close();
}

