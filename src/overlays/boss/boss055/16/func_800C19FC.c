#include "boss055_16.h"

MATCH void func_800C19FC(void) {
    SPAD_WORK_BYTES[0xB] = 0;
    func_801E30F8();
    SPAD_WORK_BYTES[1]++;
    SPAD_WORK_BYTES[2] = 0;
}
