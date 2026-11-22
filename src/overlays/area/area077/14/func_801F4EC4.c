#include "area077_14.h"

MATCH void func_801F4EC4(void) {
    u8  ticks;
    u8  count;
    s32 row;

    ticks = TASK(Actor)->timer;
    if ((ticks % 5) == 0) {
        count = ticks / 5;
        row   = D_801F627D[COORD_INT(TASK(Actor)->pos.x)];
        Area_PaletteCopyRow(row, 8 - count, row, 0);
    }
    TASK(Actor)->timer++;
    if (TASK(Actor)->unk_0A < 9) {
        Area_PaletteCopyRow(D_801F6278[COORD_INT(TASK(Actor)->pos.x)], TASK(Actor)->unk_0A + 1, D_801F6278[COORD_INT(TASK(Actor)->pos.x)], 0);
    }
    TASK(Actor)->unk_0A++;
    if (TASK(Actor)->timer >= 31) {
        TASK(Actor)->timer  = 0;
        TASK(Actor)->unk_0A = 0;
        TASK(Actor)->header.step += 1;
    }
}
