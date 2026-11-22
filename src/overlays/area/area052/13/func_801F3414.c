#include "area052_13.h"

MATCH void func_801F3414(void) {
    Coord x;
    Coord y;

    if ((u8)Area_GetCursor(&x.fixed, &y.fixed) != 0) {
        Area_HeightSet(COORD_INT(x), COORD_INT(y), 0);
        Area_CellSetCode(COORD_INT(x), COORD_INT(y), (u8)TASK(Actor)->unk_18);
        Area_HeightSet(COORD_INT(x) + 1, COORD_INT(y), 0);
        Area_CellSetCode(COORD_INT(x) + 1, COORD_INT(y), (u8)(TASK(Actor)->unk_18 >> 8));
        TASK(Actor)->unk_18 = TASK(Actor)->unk_1C;
        TASK(Actor)->unk_1C = 0;
        Area_HeightSet(COORD_INT(x), COORD_INT(y) += 2, 0x10);
        TASK(Actor)->unk_1C |= (u8)Area_CellGetCode(COORD_INT(x), COORD_INT(y));
        Area_CellSetCode(COORD_INT(x), COORD_INT(y), 0x11);
        Area_HeightSet(++COORD_INT(x), COORD_INT(y), 0x10);
        TASK(Actor)->unk_1C |= (u8)Area_CellGetCode(COORD_INT(x), COORD_INT(y)) << 8;
        Area_CellSetCode(COORD_INT(x), COORD_INT(y), 0x11);
        TASK(Actor)->direction = FACING_DOWN;
        Area_MoveActorRoute(g_ScriptState, 5);
        g_ScriptState->steps = 2;
    }
}
