#include "area082_13.h"

MATCH s32 func_801F2C9C(void) {
    u16 remaining;

    remaining           = SELF(Actor)->unk_2C - 1;
    SELF(Actor)->unk_2C = remaining;
    SELF(Actor)->angle_x += 4;
    SELF(Actor)->angle_y += 4;
    if (!(remaining & HALF_MASK)) {
        SELF(Actor)->unk_2C = 0x10;
        SELF(Actor)->header.mode += 1;
    }
}
