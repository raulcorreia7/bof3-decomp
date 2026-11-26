#include "area077_14.h"

MATCH void func_801F4D20(void) {
    u16 tile;

    tile = COORD_INT(SELF(Actor)->pos.y);
    if (((FIELD(s32, g_SceneEventFlags, 0x0) >> 4) & ((tile >> 4) & 0xF)) == (tile & 0xF)) {
        SELF(Actor)->header.step = 3;
        Area_PaletteCopyRow(D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 9, D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 0);
    } else {
        SELF(Actor)->header.step += 1;
        Area_PaletteCopyRow(D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 1, D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 0);
    }
    Area_PaletteCopyRow(D_801F627D[COORD_INT(SELF(Actor)->pos.x)], 8, D_801F627D[COORD_INT(SELF(Actor)->pos.x)], 0);
}
