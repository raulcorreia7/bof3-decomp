#include "area068_13.h"

MATCH void func_801F32CC(void) {
    u8* work;
    u8  value;

    work    = SELF(u8);
    value   = work[9];
    work[9] = value + 0xFF;
    if (value == 0) {
        SELF(Actor)->header.mode = WELL_MODE_SWISH_STEP;
    }
}
