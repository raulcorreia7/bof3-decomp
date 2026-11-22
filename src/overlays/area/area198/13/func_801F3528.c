#include "area198_13.h"

MATCH void func_801F3528(void) {
    s32 diff;

    diff = (TO_COORD(25) - TASK(Actor)->pos.x.fixed) >> 15;
    if (diff != 0) {
        g_ScriptState->steps   = abs(diff);
        TASK(Actor)->direction = FACING_RIGHT;
        Area_MoveActorRoute(g_ScriptState, TASK(Actor)->direction);
    }
}
