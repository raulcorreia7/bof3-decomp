#include "boss028_16.h"

MATCH void func_800C1C30(void) {
    D_800C21AC[SPAD_WORK_BYTES[2]]();
    if (SPAD_WORK_BYTES[0] & 1) {
        func_8014D290();
    }
}
