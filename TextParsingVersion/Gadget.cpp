#include <string>
#include <vector>
#include "Gadget.h"
#include <iostream>

using namespace std;

Operation::Operation(const string& inputLine) {
	SetOperation(inputLine);
}

void Operation::PrintOperation() {
	//cout << "                      MemoryAddressLocation : " << memoryAddressLocation << endl;
	//cout << "                      InstructionSet        : " << instructionSet << endl;
}

void Operation::SetOperation(const string& inputLine) {
	size_t colonIdx = inputLine.find(":");
	size_t memoryAddressLocationIdx = inputLine.substr(colonIdx + 1).find_first_not_of(" \t") + colonIdx + 1;
	size_t lineNumberIdx = inputLine.find_first_not_of(" \t");
	
	lineNumber = inputLine.substr(lineNumberIdx, colonIdx - lineNumberIdx);



	size_t lastIdx = memoryAddressLocationIdx;
	while (inputLine[lastIdx] != ' ' || inputLine[lastIdx + 1] != ' ') {
		++lastIdx;
	}

	opcode = inputLine.substr(memoryAddressLocationIdx, lastIdx - memoryAddressLocationIdx);

	string tmp = inputLine.substr(lastIdx);
	size_t instructionSetIdx = tmp.find_first_not_of(" \t");
	instruction = tmp.substr(instructionSetIdx);
}
void Operation::setLineNumber(const string& line) {

	//size_t lineNumberIdx = line.find_first_not_of(" \t");
	//size_t colonIdx = line.find(":");
	//lineNumber = line.substr(lineNumberIdx, colonIdx - lineNumberIdx);
}



Gadget::Gadget(const string& startInputLine, const string& endInputLine, const vector<Operation>& operationsArg) {
	SetTypeInformation(startInputLine);
	SetFinalDestinationInformation(endInputLine);
	operations = operationsArg;
	PrintGadget();
	cout << endl;
}

void Gadget::PrintGadget() {
	//cout << "Type                           : " << type << endl;
	//cout << "TypeMemoryLocation             : " << typeMemoryLocation << endl;
	//cout << "TypeLineNumber                 : " << typeLineNumber << endl;
	//cout << "FinalDestination               : " << finalDestination << endl;
	//cout << "FianlDestinationMemoryLocation : " << fianlDestinationMemoryLocation << endl;
	//cout << "FinalDestinationLineNumber     : " << finalDestinationLineNumber << endl;
	//cout << "Operations                     : " << endl;
	for (unsigned int i = 0; i < operations.size(); ++i) {
		operations[i].PrintOperation();
	}
}
bool Gadget::isStartOfGadget(const string& inputLine) {
	static vector<string> rlpJlpClp{ "rlp", "jlp", "clp" };

	for (string& startType : rlpJlpClp) {
		if (inputLine.rfind(startType) != string::npos)
			return true;
	}
	return false;
}
//allRegisters{"s","d"};
bool Gadget::isEndOfGadget(const string& inputLine) {
	static vector<string> retCallJmp{ "ret", "call", "jmp" };

	for (string& endType : retCallJmp) {
		if (inputLine.rfind(endType) != string::npos)
			return true;
	}
	return false;
}

void Gadget::SetTypeInformation(const string& startInputLine) {
	size_t typeIdx = startInputLine.find_last_of("rcj");
	type = startInputLine.substr(typeIdx, 3);

	size_t lineNumberIdx = startInputLine.find_first_not_of(" \t");
	size_t colonIdx = startInputLine.find(":");
	typeLineNumber = startInputLine.substr(lineNumberIdx, colonIdx - lineNumberIdx);


	string middle = startInputLine.substr(colonIdx + 1, typeIdx - colonIdx);
	size_t start = middle.find_first_not_of(" \t");
	size_t end = middle.find_last_not_of(" \t");
	typeOpcode = middle.substr(start, end - start);
}

void Gadget::SetFinalDestinationInformation(const string& endInputLine) {
	size_t lineNumberIdx = endInputLine.find_first_not_of(" ");
	size_t colonIdx = endInputLine.find(":");
	finalDestinationLineNumber = endInputLine.substr(lineNumberIdx, colonIdx - lineNumberIdx);

	size_t finalDestinaionMemoryLocationIdx = endInputLine.substr(colonIdx + 1).find_first_not_of(" \t") + colonIdx + 1;
	size_t lastIdx = finalDestinaionMemoryLocationIdx;
	while (endInputLine[lastIdx] != ' ' || endInputLine[lastIdx + 1] != ' ') {
		++lastIdx;
	}
	fianlDestinationOpcode = endInputLine.substr(finalDestinaionMemoryLocationIdx, lastIdx - finalDestinaionMemoryLocationIdx);

	string tmp = endInputLine.substr(lastIdx);
	size_t finalDestinationIdx = tmp.find_first_not_of(" \t");
	finalDestination = tmp.substr(finalDestinationIdx);
}