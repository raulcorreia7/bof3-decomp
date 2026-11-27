#include "area052_13.h"

MATCH void func_801F43B0(void) {
    Coord x;
    Coord y;

    Area_GetCursor(&x.fixed, &y.fixed);
    Area_HeightSet(--COORD_INT(x), COORD_INT(y), 0x10);
    SELF(Actor)->unk_18 |= (u8)Area_CellGetCode(COORD_INT(x), COORD_INT(y));
    func_801A4BC0(COORD_INT(x), COORD_INT(y), 0x11);
    Area_HeightSet(COORD_INT(x), ++COORD_INT(y), 0x10);
    SELF(Actor)->unk_1C |= (u8)Area_CellGetCode(COORD_INT(x), COORD_INT(y));
    func_801A4BC0(COORD_INT(x), COORD_INT(y), 0x11);
    SELF(Actor)->direction = FACING_LEFT;
    Area_MoveActorRoute(g_ScriptState, 7);
    g_ScriptState->steps = 2;
}
