#include "area077_14.h"

MATCH void func_801F4FFC(void) {
    u16 tile;

    if ((SELF(Actor)->timer & 3) == 0) {
        Area_PaletteCopyRow(D_801F627D[COORD_INT(SELF(Actor)->pos.x)], D_801F6298[(SELF(Actor)->timer >> 2) % 6], D_801F627D[COORD_INT(SELF(Actor)->pos.x)], 0);
    }
    Area_PaletteCopyRow(D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 9, D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 0);
    tile = COORD_INT(SELF(Actor)->pos.y);
    if (((LOW(g_SceneEventFlags) >> 4) & ((tile >> 4) & 0xF)) != (tile & 0xF)) {
        if (((SELF(Actor)->timer >> 2) % 6) == 0) {
            SELF(Actor)->timer  = 0;
            SELF(Actor)->unk_0A = 0;
            SELF(Actor)->header.step += 1;
        }
    }
    SELF(Actor)->timer++;
}
