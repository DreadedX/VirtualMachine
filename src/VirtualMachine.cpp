#include "Standard.h"

#define REGISTER_COUNT 2

word mRegisters[REGISTER_COUNT];

bool mStatus;
bool mOverflow;
bool mUnderflow;

byte mProgramCounter;
byte mInstructionRegister;

int mTemp;


void reset() {

    for (int i = 0; i < REGISTER_COUNT; i++) {
    	
	mRegisters[i] = 0x00;
    }


    mStatus = true;
    mOverflow = false;
    mUnderflow = false;

    mProgramCounter = 0x00;
    mInstructionRegister = 0x00;

    mTemp = 0;
}

void dumpRegisters() {

    std::cout << "Registers:" << std::endl;
	for (int i = 0; i < REGISTER_COUNT; i++) {

	    std::cout << "register" << i << " [" << mRegisters[i] << "]" << std::endl;
	}
	std::cout << "status [" << mStatus << "]" << std::endl
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

void doLoad(std::vector<byte> &mProgram) {

    mRegisters[mProgram[mProgramCounter]] = mProgram[mProgramCounter+1];

    mProgramCounter += 2;
}

void doAdd() {

    mTemp = mRegisters[0] + mRegisters[1];

    if (mTemp > 255) {

	mOverflow = true;
	mTemp = 255;
    }

    mRegisters[0] = mTemp;
}

void doSub() {

    mTemp = mRegisters[0] - mRegisters[1];

    if (mTemp < 0) {

	mUnderflow = true;
	mTemp = 0;
    }

    mRegisters[0] = mTemp;
}

void doStore(std::vector<byte> &mProgram) {

    mProgram[mProgramCounter+1] = mRegisters[mProgram[mProgramCounter]];

    mProgramCounter += 2;
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
	    case LDT:
		doLoad(mProgram);
		break;

	    case ADD:
		doAdd();
		break;

	    case SUB:
		doSub();
		break;

	    case STT:
		doStore(mProgram);
		break;

	    default:
		fault();
		return;
	}
    }

    dumpRegisters();

    std::cout << "Program: " << std::endl;
    for (uint i = 0; i < mProgram.size(); i++) {

	std::cout << i << " [" << +mProgram[i] << "]" << std::endl;
    }
}
