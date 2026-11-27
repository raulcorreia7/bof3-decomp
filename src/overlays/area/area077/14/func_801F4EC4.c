#include "area077_14.h"

MATCH void func_801F4EC4(void) {
    u8  ticks;
    u8  count;
    s32 row;

    ticks = SELF(Actor)->timer;
    if ((ticks % 5) == 0) {
        count = ticks / 5;
        row   = D_801F627D[COORD_INT(SELF(Actor)->pos.x)];
        Area_PaletteCopyRow(row, 8 - count, row, 0);
    }
    SELF(Actor)->timer++;
    if (SELF(Actor)->unk_0A < 9) {
        Area_PaletteCopyRow(D_801F6278[COORD_INT(SELF(Actor)->pos.x)], SELF(Actor)->unk_0A + 1, D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 0);
    }
    SELF(Actor)->unk_0A++;
    if (SELF(Actor)->timer >= 31) {
        SELF(Actor)->timer  = 0;
        SELF(Actor)->unk_0A = 0;
        SELF(Actor)->header.step += 1;
    }
}
