#include "area077_14.h"

MATCH void func_801F515C(void) {
    s32 row;
    u32 block;
    u32 count;
    u8  ticks;

    ticks = SELF(Actor)->timer;
    if ((u8)(ticks % 5) == 0) {
        row = D_801F627D[COORD_INT(SELF(Actor)->pos.x)];
        Area_PaletteCopyRow(row, (u8)(ticks / 5) + 2, row, 0);
    }
    SELF(Actor)->timer++;
    block = SELF(Actor)->unk_0A;
    if ((block & 1) == 0) {
        count = (u8)block;
        if (count < 9) {
            Area_PaletteCopyRow(D_801F6278[COORD_INT(SELF(Actor)->pos.x)], D_801F62A0[count >> 1], D_801F6278[COORD_INT(SELF(Actor)->pos.x)], 0);
        }
    }
    SELF(Actor)->unk_0A++;
    if (SELF(Actor)->timer >= 0x1F) {
        SELF(Actor)->timer       = 0;
        SELF(Actor)->unk_0A      = 0;
        SELF(Actor)->header.step = 1;
    }
}
