#include "area119_13.h"

MATCH void func_801F2DC4(void) {
    u8* work;
    u8  value;

    work    = TASK(u8);
    value   = work[9];
    work[9] = value + 0xFF;
    if (value == 0) {
        TASK(Actor)->header.mode = 6;
    }
}
