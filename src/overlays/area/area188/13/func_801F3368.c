#include "area188_13.h"

MATCH void func_801F3368(void) {
    u16 screen_x;
    u8  mode;

    screen_x         = g_Task->screen_x + 0x20;
    g_Task->screen_x = screen_x;
    func_801F38E0(&g_Task->unk_64, (s16)screen_x, 6);
    mode          = g_Task->timer - 1;
    g_Task->timer = mode;
    if (!(mode & BYTE_MASK)) {
        g_Task->timer = 128;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x14));
    }
}
