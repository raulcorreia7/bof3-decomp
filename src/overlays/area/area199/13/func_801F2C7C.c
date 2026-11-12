#include "area199_13.h"

MATCH void func_801F2C7C(void) {
    s32 x;

    x                   = g_Task->pos.x.fixed - ((g_FrameCount & 0x3) < 1);
    g_Task->pos.x.fixed = x;
    func_801F2E80(x);
}
