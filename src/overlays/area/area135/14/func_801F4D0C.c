#include "area135_14.h"

MATCH void func_801F4D0C(void) {
    TASK(Actor)->direction = FACING_DOWN;
    g_ScriptState->steps   = (TO_COORD(20) + COORD_HALF - TASK(Actor)->pos.y.fixed) >> 0xF;
    Area_MoveActorRoute(g_ScriptState, TASK(Actor)->direction);
    TASK(Actor)->vz     = 0;
    TASK(Actor)->unk_04 = 0;
}
