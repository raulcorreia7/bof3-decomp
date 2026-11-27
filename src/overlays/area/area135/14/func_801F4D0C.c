#include "area135_14.h"

MATCH void func_801F4D0C(void) {
    SELF(Actor)->direction = FACING_DOWN;
    g_ScriptState->steps   = (TO_COORD(20) + COORD_HALF - SELF(Actor)->pos.y.fixed) >> 0xF;
    Area_MoveActorRoute(g_ScriptState, SELF(Actor)->direction);
    SELF(Actor)->vz     = 0;
    SELF(Actor)->unk_04 = 0;
}
