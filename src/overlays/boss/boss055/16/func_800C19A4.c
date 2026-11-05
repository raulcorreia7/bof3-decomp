#include "boss055_16.h"

MATCH void func_800C19A4(void) {
    TASK_BYTES[0xB] = 1;
    D_801463BE      = 0;
    func_801E2314(0);
    func_801E30F8();
    TASK_BYTES[2]++;
}
