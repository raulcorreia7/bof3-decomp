#include "area173_14.h"

MATCH void func_801F38AC(void) {
    s16* slot;
    u8   x;
    u8   mode;

    slot       = &D_1F800038;
    x          = TASK(Actor)->timer;
    D_1F80003A = 0;
    *slot      = -(x * 4);
    func_801F3954(0);
    *slot = TASK(Actor)->timer * 4;
    func_801F3954(1);
    *slot      = 0;
    D_1F80003A = 0x180;
    func_801F3954(2);
    mode = TASK(Actor)->timer;
    if (mode != 0) {
        TASK(Actor)->timer = mode - 1;
    }
}
