#include "area098_13.h"

MATCH void func_801F3CDC(void) {
    u8 value;

    value          = g_Task->unk_06;
    g_Task->unk_06 = value + 1;
    if (!(value & 0x3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F5940();
    func_801F48E8(&g_Task->unk_18, &g_Task->pos.x, 0x40);
    if (*g_ScriptVars == 0x18) {
        g_Task->unk_03 = 0x80;
        g_Task->timer  = 8;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x08));
    }
}
