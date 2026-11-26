#include "area173_14.h"

MATCH void func_801F2D28(void) {
    u8 mode;

    mode = SELF(Actor)->timer;
    func_801F3060(mode >> 3, (mode >> 2) & 0x1);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 208U) {
        SELF(Actor)->header.step += 1;
    }
}
