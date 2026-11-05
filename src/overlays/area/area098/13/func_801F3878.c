#include "area098_13.h"

MATCH void func_801F3878(void) {
    u16 scroll;
    u8  remaining;

    scroll            = g_SpadWork->unk_2E + 0x20;
    g_SpadWork->unk_2E = scroll;
    func_801F46EC(&g_SpadWork->unk_64, (s16)scroll, 6);
    remaining            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = remaining;
    if (!(remaining & 0xFF)) {
        g_SpadWork->unk_09 = 0x80;
        g_SpadWork->unk_01 += 1;
        SND_PlayCue(0x209U);
    }
}
