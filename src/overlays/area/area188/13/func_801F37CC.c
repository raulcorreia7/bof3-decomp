#include "area188_13.h"

MATCH void func_801F37CC(void) {
    u8 mode;
    u8 count;

    count          = g_Task->unk_06;
    g_Task->unk_06 = count + 1;
    if (!(count & 0x3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F44B4();
    func_801F3ADC(&g_Task->unk_18, &g_Task->pos.x, 0x40);
    if (*g_ScriptVars == 3) {
        if (g_Task->timer == 16) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x16));
        }
        mode          = g_Task->timer - 1;
        g_Task->timer = mode;
        if (!(mode & BYTE_MASK)) {
            g_Task->unk_03 = 0x80;
            g_Task->header.mode += 1;
        }
    }
}
