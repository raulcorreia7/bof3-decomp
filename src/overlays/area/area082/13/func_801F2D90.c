#include "area082_13.h"

MATCH void func_801F2D90(void) {
    u16 remaining;

    remaining           = TASK(Actor)->unk_2C - 1;
    TASK(Actor)->unk_2C = remaining;
    TASK(Actor)->angle_x += 3;
    TASK(Actor)->angle_y -= 3;
    if (!(remaining & HALF_MASK)) {
        TASK(Actor)->unk_2C = 0x10;
        TASK(Actor)->header.mode += 1;
    }
}
