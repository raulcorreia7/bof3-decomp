#include "area077_14.h"

MATCH void func_801F4FFC(void) {
    u16 tile;

    if ((TASK(Actor)->timer & 3) == 0) {
        Area_PaletteCopyRow(D_801F627D[COORD_INT(TASK(Actor)->pos.x)], D_801F6298[(TASK(Actor)->timer >> 2) % 6], D_801F627D[COORD_INT(TASK(Actor)->pos.x)], 0);
    }
    Area_PaletteCopyRow(D_801F6278[COORD_INT(TASK(Actor)->pos.x)], 9, D_801F6278[COORD_INT(TASK(Actor)->pos.x)], 0);
    tile = COORD_INT(TASK(Actor)->pos.y);
    if (((LOW(g_SceneEventFlags) >> 4) & ((tile >> 4) & 0xF)) != (tile & 0xF)) {
        if (((TASK(Actor)->timer >> 2) % 6) == 0) {
            TASK(Actor)->timer  = 0;
            TASK(Actor)->unk_0A = 0;
            TASK(Actor)->header.step += 1;
        }
    }
    TASK(Actor)->timer++;
}
