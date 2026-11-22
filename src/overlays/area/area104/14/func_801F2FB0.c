#include "area104_14.h"

MATCH void func_801F2FB0(void) {
    s32    x;
    s32    y;
    s32    scaled;
    Actor* scratch;

    scaled = g_Game.members[0].unk_0C * g_Game.members[0].unk_09;
    x      = FIX_INT(g_Game.members[0].pos.x.fixed + scaled);
    y      = FIX_INT(g_Game.members[0].pos.y.fixed + g_Game.members[0].unk_10 * g_Game.members[0].unk_09);

    scratch     = TASK(Actor);
    scratch->vx = x;
    scratch->vy = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xA1) {
        TASK(Actor)->param.unk_0B = 1;
    } else if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xA0) {
        TASK(Actor)->param.unk_0B = 2;
    } else if ((Area_CellGetCode(x, y) & BYTE_MASK) == 0xAE) {
        TASK(Actor)->param.unk_0B = 3;
    } else if (g_Game.walk_flags & AREA_WALK_TRANSITION) {
        TASK(Actor)->param.unk_0B = 4;
    } else {
        TASK(Actor)->param.unk_0B = 0;
    }

    D_801F6A64[TASK(Actor)->header.mode]();
}
