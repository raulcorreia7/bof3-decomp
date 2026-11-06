#include "area098_13.h"

MATCH void func_801F3D98(void) {
    u8 remaining;

    g_Task->unk_2E -= 0x10;
    g_Task->unk_03 -= 8;
    Area_StepSpawnSlots();
    func_801F48E8(&g_Task->unk_18, &g_Task->x, g_Task->unk_03);
    remaining      = g_Task->unk_09 - 1;
    g_Task->unk_09 = remaining;
    if (!(remaining & 0xFF)) {
        Actor_Clear();
    }
}
