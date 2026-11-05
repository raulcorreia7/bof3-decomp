#include "area103_13.h"

MATCH void func_801F507C(void) {
    s32 delta;
    s32 steps;

    delta = 0x1F - g_SpadWork->unk_09;
    steps = delta;
    if (delta < 0) {
        steps = delta + 3;
    }
    func_801F5174(steps >> 2, delta * 4);
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0x19U) {
        g_SpadWork->unk_09 = 0;
        g_SpadWork->state_02 += 1;
    }
}
