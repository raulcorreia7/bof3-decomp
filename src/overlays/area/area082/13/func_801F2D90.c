#include "area082_13.h"

MATCH void func_801F2D90(void) {
    u16 remaining;

    remaining           = SELF(Actor)->unk_2C - 1;
    SELF(Actor)->unk_2C = remaining;
    SELF(Actor)->angle_x += 3;
    SELF(Actor)->angle_y -= 3;
    if (!(remaining & HALF_MASK)) {
        SELF(Actor)->unk_2C = 0x10;
        SELF(Actor)->header.mode += 1;
    }
}
