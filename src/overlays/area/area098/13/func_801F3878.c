#include "area098_13.h"

MATCH void func_801F3878(void) {
    u16 temp_a1;
    u8  temp_v0;

    temp_a1            = g_SpadWork->unk_2E + 0x20;
    g_SpadWork->unk_2E = temp_a1;
    func_801F46EC(&g_SpadWork->unk_64, (s16)temp_a1, 6);
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_SpadWork->unk_09 = 0x80;
        g_SpadWork->unk_01 += 1;
        SND_PlayCue(0x209U);
    }
}
