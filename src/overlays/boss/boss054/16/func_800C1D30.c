#include "boss054_16.h"

MATCH void func_800C1D30(void) {
    Callback handlers[1];

    handlers[0] = func_800C1D7C;
    handlers[SPAD_WORK_BYTES[1]]();
}
