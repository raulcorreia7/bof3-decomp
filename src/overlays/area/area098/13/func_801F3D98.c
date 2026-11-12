#include "area098_13.h"

MATCH void func_801F3D98(void) {
    u8 remaining;

    g_Task->screen_x -= 0x10;
    g_Task->unk_03 -= 8;
    Area_UpdateSpawnSlots();
    func_801F48E8(&g_Task->unk_18, &g_Task->pos.x, g_Task->unk_03);
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        Actor_Clear();
    }
}
