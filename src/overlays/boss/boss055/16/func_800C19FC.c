#include "boss055_16.h"

MATCH void func_800C19FC(void) {
    TASK_BYTES[0xB] = 0;
    func_801E30F8();
    TASK_BYTES[1]++;
    TASK_BYTES[2] = 0;
}
