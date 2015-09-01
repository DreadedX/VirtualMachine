#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

namespace VirtualMachine {

    void execute(std::vector<byte> &mProgram);
};

enum InstructionSet {

    LD0 = 0,
    LD1,
    ADD,
    SUB,
    ST0,
    ST1
};

#endif

