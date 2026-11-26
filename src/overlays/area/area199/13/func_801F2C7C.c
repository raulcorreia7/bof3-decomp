#include "area199_13.h"

MATCH void func_801F2C7C(void) {
    s32 x;

    x                        = SELF(Actor)->pos.x.fixed - ((g_FrameCount & 0x3) < 1);
    SELF(Actor)->pos.x.fixed = x;
    func_801F2E80(x);
}
