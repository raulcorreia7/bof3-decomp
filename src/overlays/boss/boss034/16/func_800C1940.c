#include "boss034_16.h"

MATCH void func_800C1940(void) {
    if (func_8014D978() != 0) {
        SPAD_WORK_BYTES[9]  = 0x40;
        SPAD_WORK_BYTES[10] = 0x20;
        SPAD_WORK_BYTES[3]  = 1;
    }
}
