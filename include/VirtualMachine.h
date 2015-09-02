#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

namespace VirtualMachine {

    void execute(std::vector<word> &mProgram);
};

enum InstructionSet {

    LDT = 0,
    ADD,
    SUB,
    STT,
    JMP,
    IFE,
    IFN
};

#endif

