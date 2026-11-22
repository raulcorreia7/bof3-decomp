#include "area173_14.h"

MATCH void func_801F2D28(void) {
    u8 mode;

    mode = TASK(Actor)->timer;
    func_801F3060(mode >> 3, (mode >> 2) & 0x1);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 208U) {
        TASK(Actor)->header.step += 1;
    }
}
