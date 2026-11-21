#include "area172_13.h"

MATCH void func_801F31D0(void) {
    SpinEffect* spin;
    u8          i;

    if ((g_Task->unk_06++ & 3) == 0) {
        Area_ClaimSpawnSlot();
    }
    func_801F36C0(&g_Task->pos.x, (s16)g_Task->screen_x, 7);
    func_801F3FAC();
    Area_UpdateSpawnSlots();
    if (g_Task->tint.steps.delta.r < 64) {
        g_Task->tint.steps.delta.r++;
    }
    spin = MEM_PTR(SpinEffect, AREA_WORK + 0xC0);
    for (i = 0; i < 32; i++) {
        spin->fade = (s8)g_Task->tint.bytes.rgb.r >> 1;
        spin++;
    }
    if (--g_Task->timer == 0) {
        UI_ModeSet(8);
        g_Task->header.mode++;
    }
}
