#include "area152_13.h"

MATCH void func_801F2DB0(void) {
    s32 x;
    s32 y;
    s32 scaled;
    u8* scratch;

    scaled = g_Game.members[0].unk_0C * g_Game.members[0].unk_09;
    x      = FIX_INT(g_Game.members[0].pos.x.fixed + scaled);
    y      = FIX_INT(g_Game.members[0].pos.y.fixed + g_Game.members[0].unk_10 * g_Game.members[0].unk_09);

    scratch                 = SELF(u8);
    *(s32*)(scratch + 0x0C) = x;
    *(s32*)(scratch + 0x10) = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xA1) {
        SELF(Actor)->param.unk_0B = 1;
    } else if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xA0) {
        SELF(Actor)->param.unk_0B = 2;
    } else if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xAE) {
        SELF(Actor)->param.unk_0B = 3;
    } else if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        SELF(Actor)->param.unk_0B = 4;
    } else {
        SELF(Actor)->param.unk_0B = 0;
    }

    ((void (**)(void))(D_801F4C48 + 0x110))[SELF(Actor)->header.mode]();
}
