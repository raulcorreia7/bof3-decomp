#include "area188_13.h"

MATCH void func_801F37CC(void) {
    u8 mode;
    u8 count;

    count = g_SpadWork->unk_06;
    g_SpadWork->unk_06 = count + 1;
    if (!(count & 3)) {
        Area_ClaimSpawnSlot();
    }
    Area_StepSpawnSlots();
    func_801F44B4();
    func_801F3ADC(&g_SpadWork->unk_18, &g_SpadWork->x, 0x40);
    if (*g_ScriptVars == 3) {
        if (g_SpadWork->unk_09 == 0x10) {
            SND_PlayCue(EMI_CUE_ID(2, 0x16));
        }
        mode = g_SpadWork->unk_09 - 1;
        g_SpadWork->unk_09 = mode;
        if (!(mode & 0xFF)) {
            g_SpadWork->unk_03 = 0x80;
            g_SpadWork->unk_01 += 1;
        }
    }
}
