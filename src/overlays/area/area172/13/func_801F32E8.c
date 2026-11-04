#include "area172_13.h"

MATCH void func_801F32E8(void) {
    u8 phase = g_SpadWork->unk_06;

    g_SpadWork->unk_06 = phase + 1;
    if ((phase & 3) == 0) {
        func_801F38E8();
    }
    func_801F3FAC();
    Area_StepSpawnSlots();
    if (g_UiWindowEffectBusy == 0) {
        UI_SetMode(9);
        g_AreaDrawFlags = 0;
        g_SpadWork->unk_01++;
    }
}
