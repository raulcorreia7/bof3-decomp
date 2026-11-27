#include "area047_13.h"

MATCH void func_801F2D44(void) {
    s32 val;

    val = SELF(Actor)->vx;
    if (val > 0) {
        SELF(Actor)->vx = val - 1;
    }
    func_801F31F4((SELF(Actor)->vx << 19) >> 16);
    if ((u8)func_801F330C() == 0) {
        Actor_Clear();
    }
}
