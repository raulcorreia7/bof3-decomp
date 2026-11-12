#include "area098_13.h"

MATCH void func_801F3878(void) {
    u16 scroll;
    u8  remaining;

    scroll           = g_Task->screen_x + 0x20;
    g_Task->screen_x = scroll;
    func_801F46EC(&g_Task->unk_64, (s16)scroll, 6);
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        g_Task->timer = 128;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x09));
    }
}
