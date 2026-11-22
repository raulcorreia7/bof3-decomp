#include "area135_14.h"

MATCH void func_801F460C(void) {
    if (COORD_INT(TASK(Actor)->pos.x) >= 6 && (g_PadStates[0].held & PADRdown)) {
        TASK(Actor)->direction = FACING_LEFT;
        g_ScriptState->steps   = 2;
        Area_MoveActorRoute(g_ScriptState, TASK(Actor)->direction);
        TASK(Actor)->vz = 0;
        g_ScriptState->cursor -= 2;
    }
}
