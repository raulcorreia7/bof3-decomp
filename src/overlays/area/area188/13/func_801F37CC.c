#include "area188_13.h"

MATCH void func_801F37CC(void) {
    u8 mode;
    u8 count;

    count          = g_Task->unk_06;
    g_Task->unk_06 = count + 1;
    if (!(count & 3)) {
        Area_ClaimSpawnSlot();
    }
    Area_StepSpawnSlots();
    func_801F44B4();
    func_801F3ADC(&g_Task->unk_18, &g_Task->x, 0x40);
    if (*g_ScriptVars == 3) {
        if (g_Task->unk_09 == 0x10) {
            SND_PlayCue(EMI_CUE_ID(2, 0x16));
        }
        mode           = g_Task->unk_09 - 1;
        g_Task->unk_09 = mode;
        if (!(mode & 0xFF)) {
            g_Task->unk_03 = 0x80;
            g_Task->header.mode += 1;
        }
    }
}
