#include "area172_13.h"

MATCH void func_801F32E8(void) {
    u8 phase = g_Task->unk_06;

    g_Task->unk_06 = phase + 1;
    if ((phase & 0x3) == 0) {
        Area_ClaimSpawnSlot();
    }
    func_801F3FAC();
    Area_UpdateSpawnSlots();
    if (g_UiWindowEffectBusy == 0) {
        UI_SetMode(9);
        g_AreaDrawFlags = 0;
        g_Task->header.mode++;
    }
}
