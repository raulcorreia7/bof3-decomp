#include "boss055_16.h"

MATCH void func_800C19A4(void) {
    SPAD_WORK_BYTES[0xB] = 1;
    D_801463BE           = 0;
    func_801E2314(0);
    func_801E30F8();
    SPAD_WORK_BYTES[2]++;
}
