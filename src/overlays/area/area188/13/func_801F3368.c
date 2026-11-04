#include "area188_13.h"

MATCH void func_801F3368(void) {
    u16 screen_x;
    u8  mode;

    screen_x = g_SpadWork->unk_2E + 0x20;
    g_SpadWork->unk_2E = screen_x;
    func_801F38E0(&g_SpadWork->unk_64, (s16)screen_x, 6);
    mode = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_SpadWork->unk_09 = 0x80;
        g_SpadWork->unk_01 += 1;
        SND_PlayCue(EMI_CUE_ID(2, 0x14));
    }
}
