#ifndef GADGET_H_ 
#define GADGET_H_

#include <string>
#include <vector>

using namespace std;

class Operation {
public:
	Operation(const string& inputLine);
	void PrintOperation();
	void setLineNumber(const string& line);

	string opcode;
	string instruction;

	string lineNumber;
	string operation;
	string register1;
	string register2;
	string addOperation;

private:
	void SetOperation(const string& inputLine);

};


class Gadget {
public:
	Gadget(const string& startInputLine, const string& endInputLine, const vector<Operation>& operations);
	void PrintGadget();
	static bool isStartOfGadget(const string& inputLine);
	static bool isEndOfGadget(const string& inputLine);
	void SetTypeInformation(const string& startInputLine);
	void SetFinalDestinationInformation(const string& endInputLine);

	string type;
	string typeOpcode;
	string typeLineNumber;
	string finalDestination;
	string fianlDestinationOpcode;
	string finalDestinationLineNumber;
	string popLocation;

	vector<Operation> operations;
private:

};

//static vector<string> AllRegisters{ "rax", "eax", "ax", "al","rbx" };

const string _64Registers[] = { "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15" };


const string _32Registers[] = { "eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp", "r8d", "r9d", "r10d", "r11d", "r12d", "r13d", "r14d", "r15d" };


//reg == "rax" ||
//reg == "eax" ||
//reg == "ax" || 
//reg == "al" ||
//reg == "rbx" ||
//
//reg == "ebx" ||
//reg == "bx" ||
//reg == "bl" ||
//reg == "rcx" ||
//reg == "ecx" ||
//reg == "cx" ||
//reg == "cl" ||
//reg == "rdx" ||
//reg == "edx" ||
//reg == "dx" ||
//reg == "dl" ||
//reg == "rsi" ||
//reg == "esi" ||
//reg == "si" ||
//reg == "sil" ||
//reg == "rdi" ||
//reg == "edi" ||
//reg == "di" ||
//reg == "dil" ||
//reg == "rbp" ||
//reg == "ebp" ||
//reg == "bp" ||
//reg == "bpl" ||
//reg == "rsp" ||
//reg == "esp" ||
//reg == "sp" ||
//reg == "spl" ||
//reg == "r8" ||
//reg == "r8d" ||
//reg == "r8w" ||
//reg == "r8b" ||
//reg == "r9" ||
//reg == "r9d" ||
//reg == "r9w" ||
//reg == "r9b" ||
//reg == "r10" ||
//reg == "r10d" ||
//reg == "r10w" ||
//reg == "r10b" ||
//reg == "r11" ||
//reg == "r11d" ||
//reg == "r11w" ||
//reg == "r11b" ||
//reg == "r12" ||
//reg == "r12d" ||
//reg == "r12w" ||
//reg == "r12b" ||
//reg == "r13" ||
//reg == "r13d" ||
//reg == "r13w" ||
//reg == "r13b" ||
//reg == "r14" ||
//reg == "r14d" ||
//reg == "r14w" ||
//reg == "r14b" ||
//reg == "r15" ||
//reg == "r15d" ||
//reg == "r15w" ||
//reg == "r15b")

#endif  // GADGET_H_ 
