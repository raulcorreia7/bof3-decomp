#include "area098_13.h"

MATCH void func_801F3D98(void) {
    u8 temp_v0;

    g_SpadWork->unk_2E -= 0x10;
    g_SpadWork->unk_03 -= 8;
    Area_StepSpawnSlots();
    func_801F48E8(&g_SpadWork->unk_18, &g_SpadWork->x, g_SpadWork->unk_03);
    temp_v0            = g_SpadWork->unk_09 - 1;
    g_SpadWork->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_80196070();
    }
}
