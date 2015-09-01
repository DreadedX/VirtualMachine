#include "Standard.h"

byte mRegister0;
byte mRegister1;

bool mStatus;
bool mOverflow;
bool mUnderflow;

byte mProgramCounter;
byte mInstructionRegister;

int mTemp;


void reset() {

    mRegister0 = 0x00;
    mRegister1 = 0x00;

    mStatus = true;
    mOverflow = false;
    mUnderflow = false;

    mProgramCounter = 0x00;
    mInstructionRegister = 0x00;

    mTemp = 0;
}

void dumpRegisters() {

    std::cout << "Registers:" << std::endl
	<< "register0 [" << +mRegister0 << "]" << std::endl
	<< "register1 [" << +mRegister1 << "]" << std::endl
	<< "status [" << mStatus << "]" << std::endl
	<< "overflow [" << mOverflow << "]" << std::endl
	<< "underflow [" << mUnderflow << "]" << std::endl
	<< "programCounter [" << +mProgramCounter << "]" << std::endl
	<< "instructionRegister [" << +mInstructionRegister << "]" << std::endl
	<< "temp [" << mTemp << "]" << std::endl;
}

void fault() {

    mStatus = false;

    std::cout << "Instruction fault at: " << +mProgramCounter << std::endl;
    dumpRegisters();
}

void doLoad0(std::vector<byte> &mProgram) {

    mRegister0 = mProgram[mProgramCounter];
    mProgramCounter++;
}

void doLoad1(std::vector<byte> &mProgram) {

    mRegister1 = mProgram[mProgramCounter];
    mProgramCounter++;
}

void doAdd() {

    mTemp = mRegister0 + mRegister1;

    if (mTemp > 255) {

	mOverflow = true;
	mTemp = 255;
    }

    mRegister0 = mTemp;
}

void doSub() {

    mTemp = mRegister0 - mRegister1;

    if (mTemp < 0) {

	mUnderflow = true;
	mTemp = 0;
    }

    mRegister0 = mTemp;
}

void doStore0(std::vector<byte> &mProgram) {

    mProgram[mProgramCounter] = mRegister0;
    mProgramCounter++;
}

void doStore1(std::vector<byte> &mProgram) {

    mProgram[mProgramCounter] = mRegister1;
    mProgramCounter++;
}

void VirtualMachine::execute(std::vector<byte> &mProgram) {

    reset();

    std::cout << "Program: " << std::endl;
    for (uint i = 0; i < mProgram.size(); i++) {

	std::cout << i << " [" << +mProgram[i] << "]" << std::endl;
    }

    while (mProgramCounter < mProgram.size()) {

	mInstructionRegister = mProgram[mProgramCounter];
	mProgramCounter++;

	switch (mInstructionRegister) {
	    case LD0:
		doLoad0(mProgram);
		break;

	    case LD1:
		doLoad1(mProgram);
		break;

	    case ADD:
		doAdd();
		break;

	    case SUB:
		doSub();
		break;

	    case ST0:
		doStore0(mProgram);
		break;

	    default:
		fault();
		return;
	}
    }

    std::cout << std::endl;
    dumpRegisters();
}
