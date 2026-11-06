#include "area188_13.h"

MATCH void func_801F3368(void) {
    u16 screen_x;
    u8  mode;

    screen_x       = g_Task->unk_2E + 0x20;
    g_Task->unk_2E = screen_x;
    func_801F38E0(&g_Task->unk_64, (s16)screen_x, 6);
    mode           = g_Task->unk_09 - 1;
    g_Task->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_Task->unk_09 = 0x80;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(2, 0x14));
    }
}
