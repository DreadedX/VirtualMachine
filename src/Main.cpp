#include "Standard.h"

int main() {

    std::vector<byte> program;

    program.push_back(LDT);
    program.push_back(0);
    program.push_back(2);
    program.push_back(LDT);
    program.push_back(1);
    program.push_back(7);
    program.push_back(ADD);
    program.push_back(STT);
    program.push_back(0);
    program.push_back(0);

    VirtualMachine::execute(program);
}
