#include "area134_13.h"

MATCH void func_801F3370(void) {
    u8* work;
    u8  step;

    work    = SELF(u8);
    step    = work[2];
    work[2] = step + 1;
    if (step >= 15) {
        SELF(Actor)->header.mode = 0xD;
    } else {
        SELF(Actor)->header.mode = 0x14;
    }
}
