#include "boss028_16.h"

MATCH void func_800C1FB8(void) {
    D_800C21BC[SPAD_WORK_BYTES[2]]();
    if (SPAD_WORK_BYTES[0] & 1) {
        func_8014D290();
    }
}
