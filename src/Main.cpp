#include "Standard.h"

int main() {

    std::vector<byte> program;

    program.push_back(LD0);
    program.push_back(2);
    program.push_back(LD1);
    program.push_back(7);
    program.push_back(ADD);
    program.push_back(ST0);
    program.push_back(0);

    VirtualMachine::execute(program);
}
