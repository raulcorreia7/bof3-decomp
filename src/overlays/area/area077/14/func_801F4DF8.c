#include "area077_14.h"

MATCH void func_801F4DF8(void) {
    u16 tile;

    func_801F529C(D_801F6278[COORD_INT(g_Task->pos.x)], 1, D_801F6278[COORD_INT(g_Task->pos.x)], 0);
    func_801F529C(D_801F627D[COORD_INT(g_Task->pos.x)], 8, D_801F627D[COORD_INT(g_Task->pos.x)], 0);
    tile = COORD_INT(g_Task->pos.y);
    if (((FIELD(s32, g_SceneEventFlags, 0x0) >> 4) & ((tile >> 4) & 0xF)) == (tile & 0xF)) {
        g_Task->timer  = 0;
        g_Task->unk_0A = 0;
        g_Task->header.step += 1;
    }
}
