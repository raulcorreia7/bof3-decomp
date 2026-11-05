#include "area135_14.h"

MATCH void func_801F3700(void) {
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);
    s32 sample_w;
    s32 sample_h;
    s16 x;
    s16 y;
    u8  step;
    u8  next;

    if (g_SpadWork->unk_06 != 0) {
        step     = g_SpadWork->unk_09;
        sample_w = step * 0x19;
        x        = D_801F6210 + ((s32)(0xC8 - sample_w) / 2);
        sample_h = step * 6;
        y        = D_801F6212 + ((s32)(0x30 - sample_h) >> 1);
        func_80159FA0(x, y, sample_w, sample_h);
    }
    next = g_SpadWork->unk_09;
    if (next == 0) {
        func_80196070();
        return;
    }
    g_SpadWork->unk_09 = next - 1;
}
