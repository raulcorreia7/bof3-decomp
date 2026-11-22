#include "area077_14.h"

MATCH void func_801F4EC4(void) {
    u8  ticks;
    u8  count;
    s32 row;

    ticks = g_Task->timer;
    if ((ticks % 5) == 0) {
        count = ticks / 5;
        row   = D_801F627D[COORD_INT(g_Task->pos.x)];
        Area_PaletteCopyRow(row, 8 - count, row, 0);
    }
    g_Task->timer++;
    if (g_Task->unk_0A < 9) {
        Area_PaletteCopyRow(D_801F6278[COORD_INT(g_Task->pos.x)], g_Task->unk_0A + 1, D_801F6278[COORD_INT(g_Task->pos.x)], 0);
    }
    g_Task->unk_0A++;
    if (g_Task->timer >= 31) {
        g_Task->timer  = 0;
        g_Task->unk_0A = 0;
        g_Task->header.step += 1;
    }
}
