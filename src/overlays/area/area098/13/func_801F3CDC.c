#include "area098_13.h"

MATCH void func_801F3CDC(void) {
    u8 value;

    value              = g_SpadWork->unk_06;
    g_SpadWork->unk_06 = value + 1;
    if (!(value & 3)) {
        Area_ClaimSpawnSlot();
    }
    func_801F5308();
    func_801F5940();
    func_801F48E8(&g_SpadWork->unk_18, &g_SpadWork->x, 0x40);
    if (*g_ScriptVars == 0x18) {
        g_SpadWork->unk_03 = 0x80;
        g_SpadWork->unk_09 = 8;
        g_SpadWork->unk_01 += 1;
        SND_PlayCue(0x208U);
    }
}
