#include "area077_14.h"

MATCH void func_801F4D20(void) {
    u16 tile;

    tile = COORD_INT(g_Task->pos.y);
    if (((FIELD(s32, g_SceneEventFlags, 0x0) >> 4) & ((tile >> 4) & 0xF)) == (tile & 0xF)) {
        g_Task->header.step = 3;
        func_801F529C(D_801F6278[COORD_INT(g_Task->pos.x)], 9, D_801F6278[COORD_INT(g_Task->pos.x)], 0);
    } else {
        g_Task->header.step += 1;
        func_801F529C(D_801F6278[COORD_INT(g_Task->pos.x)], 1, D_801F6278[COORD_INT(g_Task->pos.x)], 0);
    }
    func_801F529C(D_801F627D[COORD_INT(g_Task->pos.x)], 8, D_801F627D[COORD_INT(g_Task->pos.x)], 0);
}
