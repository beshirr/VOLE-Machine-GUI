#include "cpu.h"

cpu::cpu() {}


void cpu::execute() {
    return;
}


void load() {

}

vector<QChar> cpu::decode(const QString& instruction) {
    vector<QChar> decoded;
    // index 0 = o-p code
    // index 1 = Register
    // index 2 = Memory X
    // index 3 = Memory Y
    decoded[0] = instruction[0];

    return decoded;
}