#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

namespace VirtualMachine {

    void execute(std::vector<byte> &mProgram);
};

enum InstructionSet {

    LDT = 0,
    ADD,
    SUB,
    STT
};

#endif

