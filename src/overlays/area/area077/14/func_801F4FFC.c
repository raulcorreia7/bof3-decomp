#include "area077_14.h"

MATCH void func_801F4FFC(void) {
    u16 tile;

    if ((g_Task->timer & 3) == 0) {
        Area_PaletteCopyRow(D_801F627D[COORD_INT(g_Task->pos.x)], D_801F6298[(g_Task->timer >> 2) % 6], D_801F627D[COORD_INT(g_Task->pos.x)], 0);
    }
    Area_PaletteCopyRow(D_801F6278[COORD_INT(g_Task->pos.x)], 9, D_801F6278[COORD_INT(g_Task->pos.x)], 0);
    tile = COORD_INT(g_Task->pos.y);
    if (((LOW(g_SceneEventFlags) >> 4) & ((tile >> 4) & 0xF)) != (tile & 0xF)) {
        if (((g_Task->timer >> 2) % 6) == 0) {
            g_Task->timer  = 0;
            g_Task->unk_0A = 0;
            g_Task->header.step += 1;
        }
    }
    g_Task->timer++;
}
