#include "boss034_16.h"

MATCH void func_800C1940(void) {
    if (func_8014D978() != 0) {
        TASK_BYTES[9]  = 0x40;
        TASK_BYTES[10] = 0x20;
        TASK_BYTES[3]  = 1;
    }
}
