#include "area120_13.h"

MATCH void func_801F3E7C(void) {
    s32 x;
    s32 y;

    if ((MEM(s32, SELF(Actor)->vx) & 0xFFFF00) == 0x30600) {
        SELF(Actor)->timer       = 0;
        SELF(Actor)->header.step = 5;
        func_801F3DF0();
    } else {
        SELF(Actor)->timer += 8;
        x = abs(64 - SELF(Actor)->timer) + 0x40;
        y = abs(0x20 - (SELF(Actor)->timer >> 1)) + 0x20;
        if (SELF(Actor)->timer >= 128) {
            SELF(Actor)->timer       = 0;
            SELF(Actor)->header.step = 2;
        }
        func_801F3F5C(x, y, 1, 0);
    }
}
