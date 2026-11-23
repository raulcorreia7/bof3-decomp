#include "area082_13.h"

MATCH s32 func_801F2C9C(void) {
    u16 remaining;

    remaining           = TASK(Actor)->unk_2C - 1;
    TASK(Actor)->unk_2C = remaining;
    TASK(Actor)->angle_x += 4;
    TASK(Actor)->angle_y += 4;
    if (!(remaining & HALF_MASK)) {
        TASK(Actor)->unk_2C = 0x10;
        TASK(Actor)->header.mode += 1;
    }
}
